#include "Worker.h"

#include <memory>
#include <string>
#include <stdexcept>

#include <iostream>
#include <signal.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/signalfd.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "../../protocol/Parser.h"
#include <afina/execute/Command.h>
#include "Utils.h"

namespace Afina {
namespace Network {
namespace NonBlocking {

// See Worker.h
Worker::Worker(std::shared_ptr<Afina::Storage> ps): pStorage(ps) {}

// See Worker.h
Worker::~Worker() {}

void* Worker::OnRunProxy(void* _args) {
    auto args = reinterpret_cast<std::pair<Worker*, int>*>(_args);
    Worker* worker = args->first;
    int server_socket = args->second;
    worker->OnRun(server_socket);
    return NULL;
}

// See Worker.h
void Worker::Start(int _server_socket) {
    std::cout << "network debug: " << __PRETTY_FUNCTION__ << std::endl;
    server_socket = _server_socket;
    running.store(true);
    auto args = new OnRunProxyArgs(this, server_socket);
    if (pthread_create(&thread, NULL, Afina::Network::NonBlocking::Worker::OnRunProxy, args) < 0) {
        throw std::runtime_error("Could not create worker thread");
    }
}

// See Worker.h
void Worker::Stop() {
    std::cout << "network debug: " << __PRETTY_FUNCTION__ << std::endl;
    running.store(false);
    shutdown(server_socket, SHUT_RDWR);
}

// See Worker.h
void Worker::Join() {
    std::cout << "network debug: " << __PRETTY_FUNCTION__ << std::endl;
    pthread_join(thread, NULL);
}

bool Worker::read(int client_socket)
{
    char buf[BUF_SIZE];
    Protocol::Parser parser;
    std::string str_buf;
    int buf_readed;

    while(true) {
        buf_readed = recv(client_socket, buf, BUF_SIZE, 0);
        if (buf_readed > 0)
        {
            str_buf.append(buf, buf_readed);
        } else {
            break;
        }
    }

    if (buf_readed < 0)
    {
        if (!((errno == EWOULDBLOCK || errno == EAGAIN) && running.load())) {
            return false;
        }
    }

    size_t parsed = 0;
    uint32_t body_size = 0;
    if (parser.Parse(str_buf, parsed))
    {
        auto command = parser.Build(body_size);
        std::string str_command(str_buf, parsed, body_size);
        std::string out;

        try {
            command->Execute(*pStorage, str_command, out);
            out += "\r\n";
        } catch (std::runtime_error &ex) {
            out = std::string("WORKER_CONNECTION_ERROR ") + ex.what() + "\r\n";
        }

        if (send(client_socket, out.c_str(), out.size(), 0) <= 0) {
            throw std::runtime_error("Socket send() failed");
        }
        parser.Reset();
    }

    return true;
}

void Worker::EraseConnection(int client_socket)
{
    for (auto it = connections.begin(); it != connections.end(); it++)
    {
        if ((*it)->fd == client_socket)
        {
            connections.erase(it);
            break;
        }
    }
}

// See Worker.h
void Worker::OnRun(int server_socket)
{
    std::cout << "network debug: " << __PRETTY_FUNCTION__ << std::endl;

    // TODO: implementation here
    // 1. Create epoll_context here
    // 2. Add server_socket to context
    // 3. Accept new connections, don't forget to call make_socket_nonblocking on
    //    the client socket descriptor
    // 4. Add connections to the local context
    // 5. Process connection events
    //
    // Do not forget to use EPOLLEXCLUSIVE flag when register socket
    // for events to avoid thundering herd type behavior.

    server_socket = server_socket;

    if ((epfd = epoll_create(EPOLL_MAX_EVENTS)) < 0)
    {
        throw std::runtime_error("Worker failed to create epoll file descriptor");
    }

    epoll_event event, events_buffer[EPOLL_MAX_EVENTS];

    Connection* server_con = new Connection(server_socket);

    event.events = /*EPOLLEXCLUSIVE |*/ EPOLLIN | EPOLLHUP | EPOLLERR;
    event.data.ptr = server_con;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, server_socket, &event) == -1)
    {
        throw std::runtime_error("Server epoll_ctl() failed");
    }

    while (running.load())
    {
        int n = epoll_wait(epfd, events_buffer, EPOLL_MAX_EVENTS, -1);
        if (n == -1)
        {
            throw std::runtime_error("Worker epoll_wait() failed");
        }

        for (int i = 0; i < n; ++i)
        {
            Connection* connection = reinterpret_cast<Connection*>(events_buffer[i].data.ptr);
            int client_socket = 0;
            if (connection->fd == server_socket)
            {
                client_socket = accept(server_socket, NULL, NULL);
                if (client_socket == -1) {
                    if ((errno != EWOULDBLOCK) && (errno != EAGAIN)) {
                        close(server_socket);
                        if (running.load()) {
                            throw std::runtime_error("Worker failed to accept");
                        }
                    }
                } else {
                    make_socket_non_blocking(client_socket);
                    event.events = EPOLLIN | EPOLLHUP | EPOLLERR;
                    auto connection = new Connection(client_socket);
                    connections.emplace_back(std::move(connection));
                    event.data.ptr = connections.back().get();
                    if (epoll_ctl(epfd, EPOLL_CTL_ADD, client_socket, &event) == -1) {
                        throw std::runtime_error("Worker failed to assign client socket to epoll");
                    }
                }
            } else {
                client_socket = connection->fd;
                if (events_buffer[i].events & (EPOLLERR | EPOLLHUP))
                {
                    epoll_ctl(epfd, EPOLL_CTL_DEL, client_socket, NULL);
                    EraseConnection(client_socket);
                } else if (events_buffer[i].events & EPOLLIN) {
                    if (read(client_socket))
                    {
                        close(client_socket);
                        epoll_ctl(epfd, EPOLL_CTL_DEL, client_socket, NULL);
                        EraseConnection(client_socket);
                    }
                } else {
                    EraseConnection(client_socket);
                    throw std::runtime_error("Epoll event incorrect");
                }
            }
        }
    }
    for (auto it = connections.begin(); it != connections.end(); it++)
    {
        epoll_ctl(epfd, EPOLL_CTL_DEL, (*it)->fd, NULL);
    }
    connections.clear();
    close(epfd);
}

} // namespace NonBlocking
} // namespace Network
} // namespace Afina

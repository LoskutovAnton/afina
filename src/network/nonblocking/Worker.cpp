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

#include <afina/execute/Command.h>
#include "Utils.h"

namespace Afina {
namespace Network {
namespace NonBlocking {

// See Worker.h
Worker::Worker(std::shared_ptr<Afina::Storage> ps): pStorage(ps) {}

// See Worker.h
Worker::~Worker() {
    if (rfifo_name.size() != 0) {
        close(rfifo_fd);
        unlink(rfifo_name.c_str());
    }
}

void* Worker::OnRunProxy(void* _args) {
    std::cout << "network debug: " << __PRETTY_FUNCTION__ << std::endl;
    auto args = reinterpret_cast<std::pair<Worker*, int>*>(_args);
    Worker* worker = args->first;
    int server_socket = args->second;
    worker->OnRun(server_socket);
    return 0;
}

// See Worker.h
void Worker::Start(int _server_socket) {
    std::cout << "network debug: " << __PRETTY_FUNCTION__ << std::endl;
    server_socket = _server_socket;
    running.store(true);
    auto args = new OnRunProxyArgs(this, server_socket);
    pthread_t buffer;
    if (pthread_create(&buffer, NULL, Afina::Network::NonBlocking::Worker::OnRunProxy, args) < 0) {
        throw std::runtime_error("Could not create worker thread");
    }
}

// See Worker.h
void Worker::Stop() {
    std::cout << "network debug: " << __PRETTY_FUNCTION__ << std::endl;
    running.store(false); //memory barier
    shutdown(server_socket, SHUT_RDWR);
}

// See Worker.h
void Worker::Join() {
    std::cout << "network debug: " << __PRETTY_FUNCTION__ << std::endl;
    pthread_join(thread, NULL);
}

bool Worker::Read(Connection* conn, bool fifo)
{
    std::cout << "network debug: " << __PRETTY_FUNCTION__ << std::endl;
    char buf[BUF_SIZE];
    bool err = false;
    int write_socket, read_socket;

    if (!fifo) {
        read_socket = write_socket = conn->fd;
    } else {
        read_socket = rfifo_fd;
    }

    bool fl = true;
    while (fl)
    {
        fl = false;
        if (conn->state == State::kReading)
        {
            int buf_readed = read(read_socket, buf, BUF_SIZE);
            if (buf_readed == 0)
            {
                if (conn->offset >= conn->read_str.size())
                {
                    return true;
                }
            }
            if (buf_readed > 0)
            {
                conn->read_str.append(buf, buf_readed);
            } else if (buf_readed < 0) {
                if ((errno != EWOULDBLOCK && errno != EAGAIN) && running.load()) {
                    return false;
                } else {
                    return true;
                }
            }

            try
            {
                size_t parsed = 0;
                if (conn->parser.Parse(&conn->read_str[conn->offset], parsed))
                {
                    conn->state = State::kBuilding;
                } else {
                    std::cout << "parsed: " << parsed << '\n';
                }
                conn->offset += parsed;
            } catch (std::runtime_error &ex) {
                conn->write.push_back(std::string("WORKER_CONNECTION_ERROR ") + ex.what() + "\r\n");
                conn->read_str.clear();
                conn->offset = 0;
                conn->state = State::kWriting;
                err = true;
            }
        }

        if (conn->state == State::kBuilding)
        {
            uint32_t body_size = 0;
            auto command = conn->parser.Build(body_size);
            if (conn->read_str.size() >= body_size)
            {
                std::string str_command(&conn->read_str[conn->offset], body_size);
                conn->offset += body_size;
                if (conn->read_str[conn->offset] == '\r')
                {
                    conn->offset += 2;
                }
                try {
                    std::string res;
                    command->Execute(*pStorage, str_command, res);
                    conn->write.push_back(res + "\r\n");
                } catch (std::runtime_error &ex) {
                    conn->write.push_back(std::string("WORKER_CONNECTION_ERROR ") + ex.what() + "\r\n");
                    conn->read_str.clear();
                    conn->offset = 0;
                    err = true;
                }
                conn->parser.Reset();
                conn->state = State::kWriting;
            } else {
                conn->state = State::kReading;
            }
        }

        if (conn->state == State::kWriting)
        {
            int writed = 1;
            while (conn->write.size() > 0)
            {
                if (!fifo) {
                    std::string tmp = conn->write.front();
                    writed = write(write_socket, tmp.c_str() + conn->head_writed, tmp.size() - conn->head_writed);
                } else {
                    writed = 0;
                    conn->write.clear();
                }
                if (writed > 0) {
                    if (conn->write.front().size() < writed) {
                        conn->head_writed += writed;
                    } else {
                        conn->write.pop_front();
                        conn->head_writed = 0;
                    }
                } else {
                    break;
                }
            }

            if (writed < 0)
            {
                if (!((errno == EWOULDBLOCK || errno == EAGAIN) && running.load())) {
                    return true;
                }
            }

            if (conn->write.size() == 0)
            {
                conn->state = State::kReading;
                if (!(running.load()) || (conn->offset >= conn->read_str.size()))
                {
                    conn->read_str.clear();
                    conn->offset = 0;
                    return false;
                } else {
                    fl = true;
                }
            }
        }
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
void Worker::OnRun(int _server_socket)
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

    server_socket = _server_socket;

    if ((epfd = epoll_create(EPOLL_MAX_EVENTS)) < 0)
    {
        throw std::runtime_error("Worker failed to create epoll file descriptor");
    }

    epoll_event event, events_buffer[EPOLL_MAX_EVENTS];

    Connection* server_con = new Connection(server_socket);
    event.events = EPOLLEXCLUSIVE | EPOLLIN | EPOLLHUP | EPOLLERR;
    event.data.ptr = server_con;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, server_socket, &event) == -1)
    {
        throw std::runtime_error("Server epoll_ctl() failed");
    }

    if (rfifo_name.size() != 0)
    {
        if (mkfifo(rfifo_name.c_str(), 0765) == -1) {
            std::cout << rfifo_name << '\n';
            throw std::runtime_error("mkfifo wfifo");
        }
        rfifo_fd = open(rfifo_name.c_str(), O_RDONLY | O_NONBLOCK);
        if (rfifo_fd == -1) {
            throw std::runtime_error("open wfifo");
        }
        event.events = /*EPOLLEXCLUSIVE | */EPOLLHUP | EPOLLIN | EPOLLERR;// | EPOLLET;
        Connection* connection = new Connection(rfifo_fd);
        connections.emplace_back(std::move(connection));
        event.data.ptr = connections.back().get();
        if (epoll_ctl(epfd, EPOLL_CTL_ADD, rfifo_fd, &event) == -1) {
            throw std::runtime_error("Worker failed to assign fifo_read to epoll");
        }
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
            if ((connection->fd == server_socket) && running.load())
            {
                client_socket = accept(server_socket, NULL, NULL);
                if (client_socket == -1) {
                    if ((errno != EWOULDBLOCK) && (errno != EAGAIN)) {
                        close(server_socket);
                        epoll_ctl(epfd, EPOLL_CTL_DEL, server_socket, NULL);
                        if (running.load())
                        {
                            throw std::runtime_error("Worker failed to accept()");
                        }
                    }
                } else if (running.load()) {
                    make_socket_non_blocking(client_socket);
                    event.events = EPOLLIN | EPOLLOUT | EPOLLHUP | EPOLLERR;
                    auto connection = new Connection(client_socket);
                    connections.emplace_back(std::move(connection));
                    event.data.ptr = connections.back().get();
                    if (epoll_ctl(epfd, EPOLL_CTL_ADD, client_socket, &event) == -1) {
                        throw std::runtime_error("Worker failed to assign client socket to epoll");
                    }
                } else {
                    break;
                }
            } else if (connection->fd == rfifo_fd) {
                if (!Read(connection, true))
                {
                    epoll_ctl(epfd, EPOLL_CTL_DEL, client_socket, NULL);
                    EraseConnection(client_socket);
                }
            } else {
                client_socket = connection->fd;
                if (events_buffer[i].events & (EPOLLERR | EPOLLHUP))
                {
                    epoll_ctl(epfd, EPOLL_CTL_DEL, client_socket, NULL);
                    EraseConnection(client_socket);
                } else if (events_buffer[i].events & (EPOLLIN | EPOLLOUT)) {
                    if (!Read(connection, false))
                    {
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

void Worker::enableFIFO(const std::string& rfifo) {
    rfifo_name = rfifo;
}

} // namespace NonBlocking
} // namespace Network
} // namespace Afina

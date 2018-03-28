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
Worker::~Worker() {
    if (rfifo_name.size() != 0) {
        close(rfifo_fd);
        unlink(rfifo_name.c_str());
    }

    if (wfifo_name.size() != 0) {
        close(wfifo_fd);
        unlink(wfifo_name.c_str());
    }
}

void* Worker::OnRunProxy(void* _args) {
    std::cout << "network debug: " << __PRETTY_FUNCTION__ << std::endl;
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

bool Worker::Read(Connection* conn, bool fifo)
{
    std::cout << "network debug: " << __PRETTY_FUNCTION__ << std::endl;
    char buf[BUF_SIZE];
    Protocol::Parser parser;
    int client_socket = conn->fd;
    int buf_readed;

    while(true) {
        if (fifo)
        {
            buf_readed = read(rfifo_fd, buf, BUF_SIZE);
        } else {
            buf_readed = read(client_socket, buf, BUF_SIZE);
        }
        if (buf_readed > 0)
        {
            conn->str_buf.append(buf, buf_readed);
        } else {
            break;
        }
    }

    if (buf_readed < 0)
    {
        if (!((errno == EWOULDBLOCK || errno == EAGAIN) && running.load())) {
            return true;
        }
    }

    bool isParsed = false;
    size_t parsed = 0;
    uint32_t body_size = 0;
    try {
        while (parser.Parse(conn->str_buf, parsed))
        {
            isParsed = true;
            auto command = parser.Build(body_size);
            std::string str_command(conn->str_buf, parsed, body_size);
            conn->str_buf.erase(0, parsed+body_size);
            if (conn->str_buf[0] == '\r')
            {
                conn->str_buf.erase(0, 2);
            }
            std::string out;

            try {
                command->Execute(*pStorage, str_command, out);
                out += "\r\n";
            } catch (std::runtime_error &ex) {
                out = std::string("WORKER_CONNECTION_ERROR ") + ex.what() + "\r\n";
            }
            size_t writed = 0;
            if (fifo)
            {
                //while (writed = write(wfifo_fd, out.c_str(), out.size()) > 0)
                writed = write(wfifo_fd, out.c_str(), out.size());
            } else {
                writed = write(client_socket, out.c_str(), out.size());
                //{
                //    out.erase(0, writed);
                //}
                ///if (write(client_socket, out.c_str(), out.size()) <= 0) {
                ///    throw std::runtime_error("Socket send() failed");
                ///}
            }
            if (writed <= 0)
            {
                throw std::runtime_error("Socket send() failed");
            }
            parser.Reset();
        }
    } catch (std::runtime_error &ex) {
        std::string out = std::string("WORKER_CONNECTION_ERROR ") + ex.what() + "\r\n";
        conn->str_buf.clear();
        isParsed = true;
        if (send(client_socket, out.c_str(), out.size(), 0) <= 0) {
            throw std::runtime_error("Socket send() failed");
        }
    }

    return isParsed;
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
            throw std::runtime_error("mkfifo wfifo");
        }
        rfifo_fd = open(rfifo_name.c_str(), O_RDWR | O_NONBLOCK);
        if (rfifo_fd == -1) {
            throw std::runtime_error("open wfifo");
        }
        event.events = EPOLLEXCLUSIVE | EPOLLHUP | EPOLLIN | EPOLLERR | EPOLLET;
        Connection* connection = new Connection(rfifo_fd);
        connections.emplace_back(std::move(connection));
        event.data.ptr = connections.back().get();
        //auto connection = new FifoConnection(fd, worker.fifo_read, worker.pStorage, worker.running);
        //event.data.ptr = connection;
        //connections.emplace_back(rfifo_fd, connection);
        if (epoll_ctl(epfd, EPOLL_CTL_ADD, rfifo_fd, &event) == -1) {
            throw std::runtime_error("Worker failed to assign fifo_read to epoll");
        }
    }

    if (wfifo_name.size() != 0)
    {
        if (mkfifo(wfifo_name.c_str(), 0765) == -1) {
            throw std::runtime_error("mkfifo wfifo");
        }
        wfifo_fd = open(wfifo_name.c_str(), O_RDWR | O_NONBLOCK);
        if (wfifo_fd == -1) {
            throw std::runtime_error("open wfifo");
        }
        event.events = EPOLLEXCLUSIVE | EPOLLHUP | EPOLLIN | EPOLLERR | EPOLLOUT | EPOLLET;
        //Connection* connection = new Connection(rfifo_fd);
        //auto connection = new FifoConnection(fd, worker.fifo_read, worker.pStorage, worker.running);
        //event.data.ptr = connection;
        //connections.emplace_back(rfifo_fd, connection);
        Connection* connection = new Connection(wfifo_fd);
        connections.emplace_back(std::move(connection));
        event.data.ptr = connections.back().get();
        if (epoll_ctl(epfd, EPOLL_CTL_ADD, wfifo_fd, &event) == -1) {
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
            if (connection->fd == server_socket)
            {
                client_socket = accept(server_socket, NULL, NULL);
                if (client_socket == -1) {
                    if ((errno != EWOULDBLOCK) && (errno != EAGAIN)) {
                        close(server_socket);
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
            //////////////////

            } else if (connection->fd == rfifo_fd) {
                if (Read(connection, true))
                {
                    if (rfifo_name.size() !=  0) {
                        close(rfifo_fd);
                        unlink(rfifo_name.c_str());
                    }
                    //epoll_ctl(epfd, EPOLL_CTL_DEL, client_socket, NULL);
                    //close(client_socket);
                    //EraseConnection(client_socket);
                }
            /*} else if (connection->fd == wfifo_fd) {
                if ((events[i].events & EPOLLIN) == EPOLLIN) {
                    char buf[BUF_SIZE];
                    while((read(rfifo_fd, buf, SENDBUFLEN)) > 0) {}
                } else {
                    writeFIFO(*con_data);
                }
            }*/

            /////////
            } else {
                client_socket = connection->fd;
                if (events_buffer[i].events & (EPOLLERR | EPOLLHUP))
                {
                    epoll_ctl(epfd, EPOLL_CTL_DEL, client_socket, NULL);
                    EraseConnection(client_socket);
                } else if (events_buffer[i].events & EPOLLIN) {
                    if (Read(connection, false))
                    {
                        epoll_ctl(epfd, EPOLL_CTL_DEL, client_socket, NULL);
                        close(client_socket);
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

void Worker::enableFIFO(const std::string& rfifo, const std::string& wfifo) {
  rfifo_name = rfifo;
  wfifo_name = wfifo;
}
/*
void Worker::readFIFO(Connection& con) {
    char buf[SENDBUFLEN];
    int len;
    while((len = read(this->rfifo_fd, buf, SENDBUFLEN)) > 0) {
        processConnection(con, buf, len, &Worker::writeFIFO);
    }
    if (len < 0) {
        con.parser.Reset();
        con.body_size = 0;
        con.offset = 0;
    }
}

void Worker::writeFIFO(Connection& con) {
  if (this->wfifo_fd == -1) {
    con.out.clear();
    return;
  }
  int c = 1;
  while (c > 0) {
    if (con.out.size() == 0) {
      break;
    }
    if (con.out[0].length() == 0) {
      break;
    }
    c = write(this->wfifo_fd, con.out[0].data(), con.out[0].length());
    if (c < 0) {
      con.out.clear();
      break;
    }
    con.out[0].erase(0, c);
    if (con.out[0].length() == 0) {
      con.out.erase(con.out.begin());
    }
  }
}

void Worker::freeFIFO(Connection& con) {
  char buf[SENDBUFLEN];
  int len;
  while((len = read(this->rfifo_fd, buf, SENDBUFLEN)) > 0) {}
}

void Worker::enableFIFO(const std::string& rfifo, const std::string& wfifo) {
  this->rfifo_name = rfifo;
  this->wfifo_name = wfifo;
  if (rfifo != "") {
    if (mkfifo(rfifo.c_str(), 0666) == -1) {
      throw std::runtime_error("mkfifo rfifo");
    }
    this->rfifo_fd = open(rfifo.c_str(), O_RDONLY | O_NONBLOCK);
    if (this->rfifo_fd == -1) {
      throw std::runtime_error("open rfifo");
    }
    this->addConnection(this->rfifo_fd, true, true);
  }
  std::cout << "here2" << std::endl;
  if (wfifo != "") {
    if (mkfifo(wfifo.c_str(), 0666) == -1) {
      throw std::runtime_error("mkfifo wfifo");
    }
    this->wfifo_fd = open(wfifo.c_str(), O_RDWR | O_NONBLOCK);
    if (this->wfifo_fd == -1) {
      throw std::runtime_error("open wfifo");
    }

    this->addConnection(this->wfifo_fd, false, true);
  }

}

void Worker::disableFIFO(void) {
  if (rfifo_name != "") {
    close(this->rfifo_fd);
    unlink(this->rfifo_name.c_str());
  }
  if (wfifo_name != "") {
    close(this->wfifo_fd);
    unlink(this->rfifo_name.c_str());
  }
}*/

} // namespace NonBlocking
} // namespace Network
} // namespace Afina

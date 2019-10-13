#ifndef TCP_LOGGER_H
#define TCP_LOGGER_H

#include <threaded_logger.hpp>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include <stdexcept>
#include <unistd.h>

template<typename Data>
class TcpLogger : public ThreadedLogger<Data>
{
private:
    int socket_d, server_port;
    std::string server_host;
public:

    TcpLogger(std::string host, int port) :
        server_host(host), server_port(port)
    {
        while(!reconnect()) {
            printf("connection to server failed, trying to reconnect\n");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    virtual ~TcpLogger() {
        disconnect();
    }

    void disconnect() {
        if (socket_d != -1)
        {
            close(socket_d);
            socket_d = -1;
        }
    }
    bool reconnect() {
        int ret;
        struct sockaddr_in server;
        struct in_addr ipv4addr;
        struct hostent *hp;

        socket_d = socket(AF_INET,SOCK_STREAM,0);
        server.sin_family = AF_INET;

        inet_pton(AF_INET, server_host.c_str(), &ipv4addr);
        hp = gethostbyaddr(&ipv4addr, sizeof ipv4addr, AF_INET);
        //hp = gethostbyname(HOST);

        bcopy(hp->h_addr, &(server.sin_addr.s_addr), hp->h_length);
        server.sin_port = htons(server_port);

        int result = connect(socket_d, (const sockaddr *)&server, sizeof(server));
        return (result != -1);
    }

    virtual void run() {

        Data line;
        do {
            while(ThreadedLogger<Data>::getQueue().try_pop(line)) {

                std::string message = line.formatLog();

                while(socket_d!=-1) {

                    int result = send(socket_d, (char *)message.c_str(), strlen((char *)message.c_str()), MSG_NOSIGNAL);

                    //const char* msg = "GET / HTTP/1.1\r\nHost: 127.0.0.1\r\nConnection: close\r\n\r\n";
                    //int msg_len = strlen(msg);
                    //int result = send(socket_d, msg, msg_len, 0);

                    if(result!=-1) {
                        //printf("%s\n", line.formatLog().c_str());
                        //emulate latency
                        //std::this_thread::sleep_for(std::chrono::milliseconds(30));
                        break;
                    } else {
                        printf("socket send error\n");
                        disconnect();
                        while(!reconnect()) {
                            printf("connection to server failed, trying to reconnect\n");
                            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                        }
                    }

                    //std::this_thread::sleep_for(std::chrono::milliseconds(300));
                }
            }

        } while (!ThreadedLogger<Data>::getQueue().empty() || !ThreadedLogger<Data>::shouldTerminate());

    }
};

#endif

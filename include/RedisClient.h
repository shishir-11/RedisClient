#ifndef REDIS_CLIENT_H
#define REDIS_CLIENT_H

#include<string>
#include<iostream>
#include<sys/socket.h>
#include<netdb.h>
#include<unistd.h>
#include<cstring>

class RedisClient{
public:
    RedisClient(const std::string &host,int port);
    ~RedisClient();
    bool connectToServer();
    void disconnect();
    int getSocketFd() ;
private:
    std::string host;
    int port;
    int sockfd;
};

#endif
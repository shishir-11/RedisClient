#include "../include/RedisClient.h"

RedisClient::RedisClient(const std::string &host, int port): host{host}, port{port}, sockfd{-1}{};

RedisClient::~RedisClient(){
    disconnect(); 
}

bool RedisClient::connectToServer(){
    struct addrinfo hints={}, *res = nullptr;
    // std::memset(&hints,0,sizeof(hints));
    hints.ai_family = AF_UNSPEC; //handles both ipv4 and ipv6
    hints.ai_socktype = SOCK_STREAM; //tcp

    std::string portStr = std::to_string(port);
    int err = getaddrinfo(host.c_str(),portStr.c_str(),&hints,&res);
    if(err!=0){
        std::cerr<<"getaddrinfo: "<<gai_strerror(err)<<"\n";
        return false;
    }

    for(auto p = res; p!=nullptr; p = p->ai_next){
        sockfd = socket(p->ai_family,p->ai_socktype,p->ai_protocol);
        if(sockfd==-1) continue;
        if(connect(sockfd,p->ai_addr,p->ai_addrlen)==0){
            break;
        }
        close(sockfd);
        sockfd = -1;
    }
    freeaddrinfo(res);
    if(sockfd==-1){
        std::cerr<<"Could not connect to :"<<host<<":"<<port<<"\n";
        return false;
    }
    return true;
}

void RedisClient::disconnect(){
    if(sockfd!=-1){
        close(sockfd);
        sockfd = -1;
    }
}

int RedisClient::getSocketFd(){
    return sockfd;
}

bool RedisClient::sendCommand(const std::string &command){
    if(sockfd==-1) return false;
    ssize_t sent = send(sockfd,command.c_str(),command.size(),0);
    return (sent==(ssize_t)command.size());
}
#ifndef CLI_H
#define CLI_H

#include<string>
#include<vector>
#include "RedisClient.h"
 
class CLI{
public:
    CLI(const std::string &host, int port);
    void run();
private:
    RedisClient redisClient;
    int port;
    std::string host;
};

#endif
#ifndef RESPONSE_PARSER_H
#define RESPONSE_PARSER_H

#include<string>
#include<sstream>
class ResponseParser{
public:
    // Read from 
    static std::string parseResponse(int sockfd);
private:
    static std::string parseSimpleString(int sockfd);
    static std::string parseSimpleError(int sockfd);
    static std::string parseInteger(int sockfd);
    static std::string parseBulkString(int sockfd);
    static std::string parseArray(int sockfd);
};  

#endif
#include "../include/ResponseParser.h"
#include<unistd.h>
#include<sys/socket.h>

static bool readChar(int sockfd,char &c){
    ssize_t r = recv(sockfd,&c,1,0);
    return (r==1);
}

static std::string readLine(int sockfd){
    std::string line;
    char c;
    while(readChar(sockfd,c)){
        if(c=='\r'){
            readChar(sockfd,c);
            break;
        }
        line.push_back(c);
    }
    return line;
}

std::string ResponseParser::parseResponse(int sockfd){
    char pref;
    if(!readChar(sockfd,pref)){
        return("Error No response or connection closed.");
    }
    switch(pref){
        case '+': return parseSimpleString(sockfd);
        case '-': return parseSimpleError(sockfd);
        case ':': return parseInteger(sockfd);
        case '$': return parseBulkString(sockfd);
        case '*': return parseArray(sockfd);
        default:
            return ("cannot parse");
    }
}

std::string ResponseParser::parseSimpleString(int sockfd){
    return readLine(sockfd);
}

std::string ResponseParser::parseSimpleError(int sockfd){
    return "(Error) "+readLine(sockfd);
}

std::string ResponseParser::parseInteger(int sockfd){
    return readLine(sockfd);   
}

std::string ResponseParser::parseBulkString(int sockfd){
    int len = std::stoi(readLine(sockfd));
    if(len==-1) return "(nil)";
    std::string bulk;
    bulk.resize(len);
    int tot_read = 0;
    while(tot_read<len){
        int rv = recv(sockfd,&bulk[tot_read],len-tot_read,0);
        if(rv<=0){
            return ("Error: Incomplete data");
        }
        tot_read+=rv;
    }
    // int rv = recv(sockfd,bulk.c_str(),len,0)
    char dummy;
    readChar(sockfd,dummy);
    readChar(sockfd,dummy);
    return bulk;
}

std::string ResponseParser::parseArray(int sockfd){
    int ct = std::stoi(readLine(sockfd));
    if(ct==0 or ct==-1){
        return "(nil)";
    }
    std::ostringstream oss;
    for(int i=0;i<ct;i++){
        oss<<parseResponse(sockfd);
        if(i!=ct-1){
            oss<<"\n";
        }
    }
    return oss.str();
}


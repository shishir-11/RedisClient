#include "../include/CLI.h"
#include "../include/CommandHandler.h"
#include "../include/ResponseParser.h"

static std::string trim(const std::string &s){
    size_t st = s.find_first_not_of("\t\b\r\f\v");
    if(st==std::string::npos) return "";
    size_t end= s.find_last_not_of("\t\n\r\f\v");
    return s.substr(st,end-st+1);
}

CLI::CLI(const std::string &host,int port):redisClient(host,port), port{port},host{host}{

}

void CLI::run(){
    if(!redisClient.connectToServer()){
        return ;
    }

    std::cout<<"Connected to redis at "<<redisClient.getSocketFd()<<"\n";

    while(true){
        std::cout<<host<<":"<<port<<"> ";
        std::cout.flush();
        std::string line;
        if(!std::getline(std::cin,line)) break;
        line = trim(line);
        if(line.empty()) continue;
        if(line=="quit"){
            std::cout<<"CLI closing\n";
            break;
        }
        if(line=="help"){
            std::cout<<"Displaying help\n";
            continue;
        }
        //tokenization
        std::vector<std::string> args = CommandHandler::splitArgs(line);
        if(args.empty()) continue;

        // for(const auto &arg: args){
        //     std::cout<<arg<<"\n";
        // }
        std::string com = CommandHandler::buildRespCommand(args);
        if(!redisClient.sendCommand(com)){
            std::cerr<<"Error. Failed to send command\n";
            break;
        }
        //parse response
        std::string resp = ResponseParser::parseResponse(redisClient.getSocketFd());
        std::cout<<resp<<"\n";
    }
    redisClient.disconnect();
}
#include "../include/CommandHandler.h"

std::vector<std::string> CommandHandler::splitArgs(const std::string  &input){
    std::vector<std::string> tokens;
    std::regex rgx(R"((\"[^\"]+\"|\S+))"); 
    auto wbegin = std::sregex_iterator(input.begin(),input.end(),rgx);
    auto wend = std::sregex_iterator();

    for(auto it = wbegin; it!=wend;it++){
        std::string token = it->str();
        if(token.size()>=2 and token[0]=='\"' and token.back()=='\"'){
            token = token.substr(1,token.size()-2);
        } 
        tokens.push_back(token);
    }
    return tokens;
}

std::string CommandHandler::buildRespCommand(const std::vector<std::string> &args){
    std::ostringstream oss;
    oss<<"*"<<args.size()<<"\r\n";
    for(const auto&arg:args){
        oss<<"$"<<arg.size()<<"\r\n"<<arg<<"\r\n";
    }
    return oss.str();
}
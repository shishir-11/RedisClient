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
}
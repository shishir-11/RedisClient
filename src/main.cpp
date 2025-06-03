#include"../include/CLI.h"
#include<iostream>
#include<string>

int main(int argc, char *argv[]){
    std::string host = "127.0.0.1";
    int port = 6379;
    int i = 1;
    while(i<argc){
        std::string arg = argv[i];
        if(arg=="-h" and i+1<argc){
            host = argv[i+1];
            i++;
        }else if(arg=="p" and i+1<argc){
            port = std::stoi(argv[i+1]);
            i++;
        }else break;
        i++;
    }
    CLI cli(host,port);
    cli.run();
    return 0;
}
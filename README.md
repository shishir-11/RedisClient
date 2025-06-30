# Introduction 
---
This Project aims to build a RESP compliant Redis Command Line Interface that can communicate with redis servers. At the moment only things till RESP2 work, plan to include RESP3 communication in the future. Follow the steps to use the project:-

- Install the official redis-server or download my custom redis server binary file [Download](https://github.com/shishir-11/RedisServer/blob/ffcf300ab05950a7e6f6f7d029ceb23ede43c503/bin/server)

- Start the redis server using `redis-server` for official or `./redis-server` for the downloaded one. 
- Clone this repository. open root of repo in terminal and run `make` to build the binary and run it.
```bash
$ git clone https://github.com/shishir-11/RedisClient.git
$ cd RedisClient
$ make
$ ./bin/my_redis_cli # use -h to specify host name and -p to give port
```
This would start up the CLI and you would see something like 

![alt text](image.png)

Now run a few commands like `info` or `ping` to confirm connection.
It is ready to run all redis commands.

# Table of Content
---
- Command Line Interface
- Connecting to Server
- Response Parser
- Command Handler
  
## Command Line Interface
Tries to connect to the server, if succeeds a message diplaying so is displayed.
While CLI is running `getline` waits for a endline which is given when enter is pressed. Then it trims the input and sends it to Command Handler to tokenize the input and then the tokenized input is sent to response construct a RESP Command to send to the server
```
*{number of tokens}\r\n
${length of token}\r\n{token}\r\n...
```
Then Disconnects (closes the socket) for the client.

## Connecting to Server
Things are interesting here.
``` Cpp
    struct addrinfo hints={}, *res = nullptr;
    hints.ai_family = AF_UNSPEC; //handles both ipv4 and ipv6
    hints.ai_socktype = SOCK_STREAM; //tcp
    // if we used AF_INET6 or AF_INET it would only look for those particular type
    int err = getaddrinfo(host.c_str(),portStr.c_str(),&hints,&res);
    // Now we have a linked list of pointers to the usable address structures.
    // Now we can iterate through them and connect to the server.
```
Something to note about sockets, they are not some physical entity, sockets are just file descriptors or integers that are used to communicate with the OS like a API, when `socket()` is called it does not create a socket but rather based on the parameters given in the function it returns a file descriptor which in this case allows it to access the information/network stream.

(Rest will be updated soon)
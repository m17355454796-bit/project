#ifndef UDP_ECHOSERVER_HPP
#define UDP_ECHOSERVER_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstdlib>

class UDPEchoServer
{
public:
    UDPEchoServer(const std::string &ip, const uint16_t port)
        : _ip(ip), _port(port), _sockfd(-1)
    {
    }

    ~UDPEchoServer()
    {
        if (_sockfd >= 0)
            close(_sockfd);
    }

    void Init()
    {
        _sockfd = socket(AF_INET, SOCK_DGRAM, 0);
        if (_sockfd < 0)
        {
            std::cerr << "socket fail" << std::endl;
            exit(1);
        }
        std::cout << "socket success!" << std::endl;

        struct sockaddr_in local;
        bzero(&local, sizeof(local));
        local.sin_family = AF_INET;
        local.sin_port = htons(_port);
        local.sin_addr.s_addr = inet_addr(_ip.c_str());

        int bind_ret = bind(_sockfd, (struct sockaddr *)&local, sizeof(local));
        if (bind_ret < 0)
        {
            std::cerr << "bind fail" << std::endl;
            exit(2);
        }
        std::cout << "bind success" << std::endl;   
    }

    void Start()
    {
        char buffer[2048];
        sockaddr_in peer;
        socklen_t len=sizeof(peer);
        while(1)
        {
            ssize_t ret=recvfrom(_sockfd,buffer,sizeof(buffer)-1,0,(sockaddr*)&peer,&len);
            if(ret<0)
            {
                std::cerr<<"接收发生失败"<<std::endl;
                continue;
            }
            buffer[ret]='\0';
            ssize_t ret1=sendto(_sockfd,buffer,ret,0,(sockaddr*)&peer,len);
            if(ret1<0)
            {
                std::cerr<<"发送失败\n";
                continue;
            }
        }
    }


private:
    std::string _ip;
    uint16_t _port;
    int _sockfd;
};

#endif

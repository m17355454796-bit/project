#ifndef UDP_DICTSERVER_HPP
#define UDP_DICTSERVER_HPP

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
#include<functional>
using namespace std;
using callback_t=function<string(string&)>;
class UDPDictServer{
  public:
    UDPDictServer(const string& ip,uint16_t port,callback_t cb):
    _ip(ip),
    _port(port),
    _cb(cb)
    {_sockfd=-1;}
    void Init()
    {
        int sockfd=socket(AF_INET,SOCK_DGRAM,0);
        if(sockfd<0)
        {
            cerr<<"创建套接字失败！"<<endl;
            exit(1);
        }
        cout<<"创建套接字成功，sockfd="<<sockfd;
        _sockfd=sockfd;
        struct sockaddr_in local;
        bzero(&local,sizeof(local));
        local.sin_family=AF_INET;
        local.sin_port=htons(_port);
        local.sin_addr.s_addr=inet_addr(_ip.c_str());
        int bind_ret=bind(_sockfd,(sockaddr*)&local,sizeof(local));
        if(bind_ret<0)
        {
            cerr<<"绑定套接字失败"<<endl;
            exit(1);
        }
        cout<<"绑定套接字成功"<<endl;
    }
    void Start()
    {
        char inbuffer[1024];
        while(1)
        {
            sockaddr_in peer;
            socklen_t len=sizeof(peer);
            ssize_t n=recvfrom(_sockfd,inbuffer,sizeof(inbuffer)-1,0,(sockaddr*)&peer,&len);
            if(n<0)
            {
                cerr<<"接受消息失败"<<endl;
                continue;
            }
            inbuffer[n]='\0';
            cout<<"服务器接受一条消息"<<inbuffer<<"客户端ip:"<<inet_ntoa(peer.sin_addr)<<" port:"<<ntohs(peer.sin_port)<<endl;
            string result;
            string tem=inbuffer;
            //处理数据
            if(_cb)
            {
                result=_cb(tem);
            }else{
                result=tem;
            }
            //发送数据
            ssize_t m=sendto(_sockfd,result.c_str(),result.size(),0,(sockaddr*)&peer,len);
            if(m<0)
            {
                cerr<<"发送消息失败"<<endl;
                continue;
            }
        }
    }
    ~UDPDictServer()
    {
        if(_sockfd>=0)
        {
            close(_sockfd);
        }
    }
  private:
    int _sockfd;
    string _ip;
    uint16_t _port;  
    callback_t _cb;
};

#endif

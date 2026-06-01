#include <iostream>
#include <string>
#include <cstring>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
using namespace std;
int main(int argc,char* argv[])
{
    if(argc!=3)
    {
        cerr<<"输入参数错误，请输入./UdpEchoClient ip port";
        return 1;
    }
    int sockfd=socket(AF_INET,SOCK_DGRAM,0);//创建udp套接字
    if(sockfd<0)
    {
        cerr<<"创建udp套接字失败"<<endl;
        return 2;
    }
    struct sockaddr_in server;
    memset(&server,0,sizeof(server));
    string ip=argv[1];
    uint32_t port=atoi(argv[2]);
    server.sin_family=AF_INET;
    server.sin_addr.s_addr=inet_addr(ip.c_str());
    server.sin_port=htons(port);
    char buffer[1024];
    while(1)
    {
        string message;
        cout<<"请输入一段文字#";
        getline(cin,message);
        ssize_t send_size=sendto(sockfd,message.c_str(),message.size(),0,(sockaddr*)&server,sizeof(server));
        if(send_size<0)
        {
            cerr<<"发送失败";
            continue;
        }
        struct sockaddr_in peer;
        socklen_t peer_len=sizeof(peer);
        ssize_t recv_size=recvfrom(sockfd,buffer,sizeof(buffer)-1,0,(sockaddr*)&peer,&peer_len);
        if(recv_size>0)
        {
            buffer[recv_size] = '\0';
            cout<<"服务器说:"<<buffer<<endl;
        }else{
            cout<<"接受失败"<<endl;
        }
    }
}

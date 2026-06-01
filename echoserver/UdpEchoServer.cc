#include"UdpEchoServer.hpp"
#include<string>
using namespace std;
void usage()
{
    cerr<<"输入参数错误，正确格式为 ./Udeechoserver ip port";
    exit(1);
}
int main(int argc, char *argv[])
{
    if(argc!=3)
    {
        usage();
    }
    string ip=argv[1];
    uint16_t port=stoi(argv[2]);
    UDPEchoServer server(ip,port);
    server.Init();
    server.Start();
    return 0;
}

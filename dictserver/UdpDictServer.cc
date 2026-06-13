#include"UdpDictServer.hpp"
#include"dictionary.hpp"
#include<string>
#include<functional>
#include<memory>
using namespace std;
void usage()
{
    cerr<<"输入参数错误，正确格式为 ./UdpDictServer ip port";
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
    //创建一个在线的字典
    unique_ptr<dictionary> dict=make_unique<dictionary>();
    //创建一个网络服务器
    unique_ptr<UDPDictServer> udpserver=make_unique<UDPDictServer>(ip,port,[&dict](string& word){return dict->translation(word);});
    //启动服务器
    udpserver->Init();
    udpserver->Start();
    return 0;
}

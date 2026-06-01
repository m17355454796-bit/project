.PHONY:all
all:UdpEchoServer UdpEchoClient

UdpEchoServer:UdpEchoServer.cc
	g++ -o $@ $^ -std=c++11

UdpEchoClient:UdpEchoClient.cc
	g++ -o $@ $^ -std=c++11

.PHONY:clean
clean:
	rm -f UdpEchoServer UdpEchoClient

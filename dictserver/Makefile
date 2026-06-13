.PHONY:all
all:UdpDictServer UdpDictClient

UdpDictServer:UdpDictServer.cc
	g++ -o $@ $^ -std=c++14

UdpDictClient:UdpDictClient.cc
	g++ -o $@ $^ -std=c++14

.PHONY:clean
clean:
	rm -f UdpDictServer UdpDictClient

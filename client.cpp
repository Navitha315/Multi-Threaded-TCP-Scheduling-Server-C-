#include <iostream>
#include <winsock2.h>

#pragma comment(lib,"ws2_32.lib")

int main() {

    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock,(sockaddr*)&server,sizeof(server));

    char buffer[1024];

    while(true) {

        std::string msg;

        std::getline(std::cin,msg);

        send(sock,msg.c_str(),msg.size(),0);

        int bytes = recv(sock,buffer,sizeof(buffer),0);

        std::string reply(buffer,bytes);

        std::cout<<"Server: "<<reply<<std::endl;
    }
}
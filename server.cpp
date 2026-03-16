#include <iostream>
#include <winsock2.h>
#include <thread>
#include "protocol.h"

#pragma comment(lib,"ws2_32.lib")

void handleClient(SOCKET clientSocket) {

    char buffer[1024];

    while(true) {

        int bytes = recv(clientSocket, buffer, sizeof(buffer), 0);

        if(bytes <= 0) {
            std::cout << "Client disconnected\n";
            break;
        }

        std::string request(buffer, bytes);

        std::cout << "Request: " << request << std::endl;

        std::string response = processRequest(request);

        send(clientSocket, response.c_str(), response.size(), 0);
    }

    closesocket(clientSocket);
}

int main() {

    WSADATA wsaData;

    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0) {
        std::cout << "WSAStartup failed\n";
        return 1;
    }

    SOCKET serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

    listen(serverSocket, SOMAXCONN);

    std::cout << "Server running on port 8080\n";

    while(true) {

        SOCKET clientSocket = accept(serverSocket, NULL, NULL);

        std::cout << "Client connected\n";

        std::thread t(handleClient, clientSocket);

        t.detach();
    }

    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
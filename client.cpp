#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class TCPClient {
private:
    int sock;
    sockaddr_in server_addr{};

public:
    TCPClient(const std::string& ip, int port) {
        // 1. Create socket
        sock = socket(AF_INET, SOCK_STREAM, 0);

        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);

        inet_pton(AF_INET, ip.c_str(), &server_addr.sin_addr);
    }

    void connectToServer() {
        connect(sock, (sockaddr*)&server_addr, sizeof(server_addr));
        std::cout << "Connected to server!\n";
    }

    void sendMessage(const std::string& msg) {
        send(sock, msg.c_str(), msg.size(), 0);
    }

    std::string receiveMessage() {
        char buffer[1024] = {0};
        read(sock, buffer, 1024);
        return std::string(buffer);
    }

    ~TCPClient() {
        close(sock);
    }
};

int main() {
    TCPClient client("127.0.0.1", 8080);

    client.connectToServer();

    client.sendMessage("Hello from C++ Client!");

    std::cout << "Server says: " 
              << client.receiveMessage() 
              << std::endl;

    return 0;
}

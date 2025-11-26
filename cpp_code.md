# 🖥️ **C++ TCP SERVER (OOP Implementation)**

```cpp
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

class TCPServer {
private:
    int server_fd, client_fd;
    sockaddr_in server_addr{}, client_addr{};

public:
    TCPServer(int port) {
        // 1. Create socket
        server_fd = socket(AF_INET, SOCK_STREAM, 0);

        server_addr.sin_family = AF_INET;
        server_addr.sin_addr.s_addr = INADDR_ANY;
        server_addr.sin_port = htons(port);

        // 2. Bind socket
        bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr));

        // 3. Listen
        listen(server_fd, 3);

        std::cout << "Server listening on port " << port << "...\n";
    }

    void acceptClient() {
        socklen_t client_len = sizeof(client_addr);
        client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_len);

        if (client_fd < 0) {
            std::cerr << "Accept failed!\n";
        } else {
            std::cout << "Client connected!\n";
        }
    }

    void sendMessage(const std::string& msg) {
        send(client_fd, msg.c_str(), msg.size(), 0);
    }

    std::string receiveMessage() {
        char buffer[1024] = {0};
        read(client_fd, buffer, 1024);
        return std::string(buffer);
    }

    ~TCPServer() {
        close(client_fd);
        close(server_fd);
    }
};

int main() {
    TCPServer server(8080);

    server.acceptClient();

    std::string msg = server.receiveMessage();
    std::cout << "Client says: " << msg << std::endl;

    server.sendMessage("Hello from C++ Server!");

    return 0;
}
```

---

# 🖥️ **C++ TCP CLIENT (OOP Implementation)**

```cpp
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
```

---

# 📌 How to Compile & Run

### **Compile server**

```bash
g++ server.cpp -o server
```

### **Compile client**

```bash
g++ client.cpp -o client
```

### **Run**

1. Start the server:

```bash
./server
```

2. In another terminal:

```bash
./client
```

---
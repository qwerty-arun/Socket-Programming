# 🚀 **Socket Programming — Quick Introduction**

## ✅ **What is a Socket?**

A **socket** is an endpoint for communication between two machines.
Think of it as a *virtual plug* that lets two programs talk over a network.

---

# 🧱 **Types of Sockets**

### 1. **TCP Socket** (Stream socket)

* Connection-oriented
* Reliable (no data loss)
* Used for: browsing, emails, file transfer

### 2. **UDP Socket** (Datagram socket)

* Connectionless
* Faster but no guarantee of delivery
* Used for: games, voice/video streaming

---

# 🌍 **Socket Programming Model**

A typical **TCP client-server** flow:

### **Server**

1. `socket()`
2. `bind()`
3. `listen()`
4. `accept()`
5. `recv()` / `send()`
6. `close()`

### **Client**

1. `socket()`
2. `connect()`
3. `send()` / `recv()`
4. `close()`

---

# 🖥 **TCP Server in C (Simple Example)**

```c
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server, client;
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr*)&server, sizeof(server));
    listen(server_fd, 3);

    int addrlen = sizeof(client);
    client_fd = accept(server_fd, (struct sockaddr*)&client, (socklen_t*)&addrlen);

    read(client_fd, buffer, 1024);
    printf("Client says: %s\n", buffer);

    char *msg = "Hello from server!";
    send(client_fd, msg, strlen(msg), 0);

    close(client_fd);
    close(server_fd);

    return 0;
}
```

---

# 🖥 **TCP Client in C**

```c
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    connect(sock, (struct sockaddr*)&server, sizeof(server));

    char *msg = "Hello Server!";
    send(sock, msg, strlen(msg), 0);

    char buffer[1024] = {0};
    read(sock, buffer, 1024);

    printf("Server says: %s\n", buffer);

    close(sock);
    return 0;
}
```

---

# 🐍 **Socket Programming in Python (Much Simpler)**

## **TCP Server (Python)**

```python
import socket

server = socket.socket()
server.bind(("0.0.0.0", 8080))
server.listen(1)

print("Waiting for client...")
client, addr = server.accept()

data = client.recv(1024).decode()
print("Client:", data)

client.send(b"Hello from server")
client.close()
server.close()
```

## **TCP Client (Python)**

```python
import socket

client = socket.socket()
client.connect(("127.0.0.1", 8080))

client.send(b"Hello Server")
print(client.recv(1024).decode())

client.close()
```

---

# 📡 **UDP Example (Python)**

### UDP Server

```python
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind(("0.0.0.0", 8080))

while True:
    data, addr = sock.recvfrom(1024)
    print("Message:", data.decode())
    sock.sendto(b"Got it!", addr)
```

### UDP Client

```python
import socket

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(b"Hello UDP", ("127.0.0.1", 8080))
print(sock.recvfrom(1024)[0].decode())
```

---

# 🎯 **Where Socket Programming Is Used**

* Chat applications
* Multiplayer gaming
* File transfer systems
* IoT devices
* Embedded systems
* Robotics communication
* Web servers / proxies

---
# 🖥 **TCP SERVER CODE — Line-by-Line Explanation**

```c
int server_fd, client_fd;
struct sockaddr_in server, client;
char buffer[1024] = {0};
```

* `server_fd` → File descriptor for the server’s socket
* `client_fd` → File descriptor for the accepted client
* `sockaddr_in` → Structure holding address info (IP + port)
* `buffer` → Used for storing client’s message

---

```c
server_fd = socket(AF_INET, SOCK_STREAM, 0);
```

* Creates a **TCP socket**

  * `AF_INET` → IPv4
  * `SOCK_STREAM` → TCP
* Returns a socket descriptor → stored in `server_fd`

---

```c
server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons(8080);
```

Set server properties:

1. `sin_family = AF_INET` → IPv4
2. `INADDR_ANY` → Bind to all network interfaces
3. `htons(8080)` → Convert port 8080 to network byte order

---

```c
bind(server_fd, (struct sockaddr*)&server, sizeof(server));
```

* Binds the created socket to the provided **IP + port**
* This means: “This socket will receive data on port 8080.”

---

```c
listen(server_fd, 3);
```

* Puts the socket into **listening mode**
* `3` → Maximum number of pending connections allowed in queue

---

```c
int addrlen = sizeof(client);
client_fd = accept(server_fd, (struct sockaddr*)&client, (socklen_t*)&addrlen);
```

* `accept()` waits until a client connects
* When a client connects:

  * A **new socket** (`client_fd`) is created for that client
  * The old socket (`server_fd`) continues listening

---

```c
read(client_fd, buffer, 1024);
printf("Client says: %s\n", buffer);
```

* Reads up to 1024 bytes sent by the client
* Prints the client message

---

```c
char *msg = "Hello from server!";
send(client_fd, msg, strlen(msg), 0);
```

* Sends a string response to the client
* `send()` transmits data over TCP

---

```c
close(client_fd);
close(server_fd);
```

* Closes the client connection
* Closes the server socket
* Frees resources

---

# 🖥 **TCP CLIENT CODE — Line-by-Line Explanation**

```c
int sock = socket(AF_INET, SOCK_STREAM, 0);
```

* Creates a **TCP socket** for the client

---

```c
struct sockaddr_in server;
```

* Stores the server’s IP + port

---

```c
server.sin_family = AF_INET;
server.sin_port = htons(8080);
inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);
```

1. IPv4
2. Port = 8080
3. `inet_pton` converts string `"127.0.0.1"` to binary form (network format)

---

```c
connect(sock, (struct sockaddr*)&server, sizeof(server));
```

* Attempts connection to server
* If server is listening → connection established

---

```c
char *msg = "Hello Server!";
send(sock, msg, strlen(msg), 0);
```

* Sends message to server

---

```c
char buffer[1024] = {0};
read(sock, buffer, 1024);
printf("Server says: %s\n", buffer);
```

* Reads up to 1024 bytes from the server
* Prints server response

---

```c
close(sock);
```

* Closes the client socket

---
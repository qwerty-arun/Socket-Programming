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

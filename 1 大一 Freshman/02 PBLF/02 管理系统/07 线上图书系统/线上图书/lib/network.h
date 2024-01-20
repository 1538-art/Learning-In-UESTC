#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#ifndef NETWORK_H
#define NETWORK_H

typedef struct
{
    int listenfd;
    int clientfd;
    char clientIP[INET_ADDRSTRLEN];
} Connection;

Connection buildConnection(char *port)
{
    Connection network;

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        fprintf(stderr, "Failed to initialize Winsock.\n");
        exit(1);
    }

    network.listenfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(atoi(port));

    if (bind(network.listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        perror("bind");
        exit(1);
    }
    printf("Server listening on port %s\n", port);
    Sleep(100);

    if (listen(network.listenfd, 5) == -1)
    {
        perror("listen");
        exit(1);
    }
    printf("Server waiting for incoming connections...\n");

    int socklen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;
    network.clientfd = accept(network.listenfd, (struct sockaddr *)&clientaddr, (int *)&socklen);
    if (network.clientfd == -1)
    {
        perror("accept");
        exit(1);
    }

    getpeername(network.clientfd, (struct sockaddr *)&clientaddr, &socklen);
    inet_ntop(AF_INET, &clientaddr.sin_addr, network.clientIP, sizeof(network.clientIP));

    // 输出连接方的IP地址
    printf("Connection established from IP: %s\n", network.clientIP);
    return network;
}
void sendShortMessage(int sockfd, char *buffer)
{
    if (send(sockfd, buffer, strlen(buffer), 0) == -1)
    {
        perror("send");
    }
}
void sendLongMessage(int sockfd, char *buffer)
{
    if (send(sockfd, buffer, strlen(buffer), 0) == -1)
    {
        perror("send");
    }
    memset(buffer, 0, sizeof(buffer));
}
void recvMessage(int sockfd, char *buffer)
{
    int Nrecv = recv(sockfd, buffer, 4096, 0);
    if (Nrecv > 0)
    {
        // 确保字符串以 null 结尾
        buffer[Nrecv] = '\0';
    }
    else if (Nrecv == 0)
    {
        perror("disconnect");
    }
    else
    {
        perror("recv");
    }
    printf("Receive: %s\n", buffer);
}
int recvInt(int sockfd, char *buffer)
{
    recvMessage(sockfd, buffer);
    int num = atoi(buffer);
    memset(buffer, 0, sizeof(buffer));

    return num;
}
void closeConnect(Connection network)
{
    printf("Closing connection from client IP: %s\n", network.clientIP);

    printf("Closing client socket (fd: %d)\n", network.clientfd);
    closesocket(network.clientfd);

    printf("Closing server socket (fd: %d)\n\n", network.listenfd);
    closesocket(network.listenfd);

    WSACleanup();
    Sleep(1000);
}

#endif
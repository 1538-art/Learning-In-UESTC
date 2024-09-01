#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
    char addr[20];
    int port;
    printf("请输入服务器地址(ipv4):");
    scanf("%s", addr);
    printf("请输入服务器端口:");
    scanf("%d", &port);

    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        fprintf(stderr, "Failed to initialize Winsock.\n");
        return 1;
    }

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    int flag = 1;
    setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(int));

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));

    servaddr.sin_addr.s_addr = inet_addr(addr);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1)
    {
        perror("connect");
        exit(1);
    }

    char buffer[4096];
    while (1)
    {
        memset(buffer, 0, sizeof(buffer));
        int Nrecv = recv(sockfd, buffer, sizeof(buffer), 0);
        if (Nrecv == 0)
        {
            printf("连接关闭");
            break;
        }
        else if (Nrecv == -1)
        {
            perror("recv");
            break;
        }
        printf("%s", buffer);

        memset(buffer, 0, sizeof(buffer));
        scanf("%s", buffer);
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
            ;
        if (send(sockfd, buffer, strlen(buffer), 0) == -1)
        {
            perror("send");
            break;
        }
    }
    closesocket(sockfd);
    WSACleanup();
}

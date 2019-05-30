#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include "error_codes.h"
#include "udp_class.h"

int client()
{
    udpBaseClass u;
    u.init(8080);
    u.configClientAddr(INADDR_ANY, 5000);
    char *hello = "Hello from client"; 
    uint8_t buffer[1400];
    socklen_t len = 0;
    int n;
    u.sendTo((uint8_t *)hello, strlen(hello));
    printf("Hello message sent.\n"); 
   n = u.recvFrom((uint8_t *)buffer, 1400);

    buffer[n] = '\0';
    printf("Server : %s\n", buffer); 
    u.deinit();
        return 0;
}

int server()
{
    udpBaseClass u;
    u.init(5000);
    socklen_t len, n;
    struct sockaddr cliaddr;
    uint8_t buffer[1400];
    char *hello = "Hello from server";
    n = u.recvFrom((uint8_t *)buffer, 1400);

    buffer[n] = '\0';
    printf("Client : %s\n", buffer);
    len = 0;

    u.sendTo((uint8_t *)hello, strlen(hello));
    printf("Hello message sent.\n");
    u.deinit();
    return 0;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("usage: %s <c/s>\nc for client and s for server\n", argv[0]);
        return -1;
    }

    if (argv[1][0] == 'c')
    {
        client();
    }
    else
    {
        server();
    }

    return 0;
}
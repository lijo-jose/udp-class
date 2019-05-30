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

int udpBaseClass::init(int port)
{
    // Creating socket file descriptor
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        perror("socket creation failed");
        return APP_FAILURE;
    }

    memset(&servaddr, 0, sizeof(servaddr));

    // Filling server information
    servaddr.sin_family = AF_INET; // IPv4
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    // Bind the socket with the server address
    if (bind(sockfd, (const struct sockaddr *)&servaddr,
             sizeof(servaddr)) < 0)
    {
        perror("bind failed");
        return APP_FAILURE;
    }
    return APP_SUCCESS;
}

ssize_t udpBaseClass::sendTo(uint8_t *data, uint32_t len)
{
    return sendto(sockfd, (const char *)data, len,
                  MSG_CONFIRM, (const struct sockaddr *)&cliaddr,
                  sizeof(cliaddr));
}

ssize_t udpBaseClass::recvFrom(uint8_t *data, uint32_t maxlen)
{
    socklen_t len;
    return recvfrom(sockfd, (char *)data, maxlen,
                    MSG_WAITALL, (struct sockaddr *)&cliaddr,
                    &len);
}
int udpBaseClass::configClientAddr(in_addr_t addr, int port)
{
    // Filling server information
    cliaddr.sin_family = AF_INET;
    cliaddr.sin_port = htons(port);
    cliaddr.sin_addr.s_addr = addr;

    return 0;
}

int udpBaseClass::setClientAddr(struct sockaddr_in *addr)
{
    cliaddr.sin_family = addr->sin_family;
    cliaddr.sin_port = addr->sin_port;
    cliaddr.sin_addr.s_addr = addr->sin_addr.s_addr;
    return 0;
}

int udpBaseClass::deinit()
{
    close(sockfd);
    return 0;
}
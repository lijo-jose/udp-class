#ifndef __UDP_CLASS_H__
#define __UDP_CLASS_H__


class udpBaseClass{
    public:
    int init(int port);

    ssize_t sendTo(uint8_t * data, uint32_t len);

    ssize_t recvFrom(uint8_t * data, uint32_t maxlen);

    int configClientAddr(in_addr_t addr, int port);
    int setClientAddr(struct sockaddr_in *addr);
    int deinit();


    private:
    int sockfd; 
    struct sockaddr_in servaddr;
    struct sockaddr_in cliaddr;
};

#endif
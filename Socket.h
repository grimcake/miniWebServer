#pragma once
#include <arpa/inet.h>
#include "InetAddress.h"

class Socket
{
public:
    Socket(int sockfd);

    int fd() const { return sockfd_; }

    static int createNonBlockfd(sa_family_t family);
    void Close(int fd);
    void Bind(int fd, const InetAddress& addr);
    int Accept(int fd, InetAddress* peeraddr);
private:
    int sockfd_;
};


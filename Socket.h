#pragma once
#include <arpa/inet.h>
#include "InetAddress.h"

namespace socketops
{
    int createNonBlockfd(sa_family_t family);
    void Close(int fd);
    void Bind(int fd, const InetAddress& addr);
    int Accept(int fd, const InetAddress& peeraddr);
    void Listen(int fd);
}

class Socket
{
public:
    Socket(int sockfd);

    int fd() const { return sockfd_; }

private:
    int sockfd_;
};




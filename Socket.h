#pragma once
#include <arpa/inet.h>
#include "InetAddress.h"

namespace socketops
{
    int createNonBlockfd(sa_family_t family);
    int createBlockfd(sa_family_t family);
    void Close(int fd);
    void Bind(int fd, const InetAddress& addr);
    int Accept(int fd, const InetAddress& peeraddr);
    void Listen(int fd);
    struct sockaddr_in getLocalAddr(int fd); //获取已绑定或已连接的fd的地址信息
}

class Socket
{
public:
    Socket(int sockfd);

    int fd() const { return sockfd_; }

private:
    int sockfd_;
};




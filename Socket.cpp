#include <iostream>
#include <unistd.h>
#include "Socket.h"


Socket::Socket(int sockfd) :
    sockfd_(sockfd)
{

}

int Socket::createNonBlockfd(sa_family_t family)
{
    int sockfd = socket(family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if(sockfd < 0) 
    {
        std::cout << "socket create error" << std::endl;
    }
    return sockfd;
}

void Socket::Close(int fd)
{
    int ret = close(fd);
    if(ret < 0)
    {
        std::cout << "socket close error" << std::endl;
    }
}

void Socket::Bind(int fd, const InetAddress& addr)
{
    int ret = bind(fd, (sockaddr*)addr.family, sizeof(struct sockaddr));
    if(ret < 0)
    {
        std::cout << "socket bind error" << std::endl;
    }
}

int Socket::Accept(int fd, InetAddress* peeraddr)
{
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    int connfd = accept(fd, (sockaddr*)peeraddr->family, &addrlen);
    if(connfd < 0)
    {
        std::cout << "socket accept error" << std::endl;
    }
}
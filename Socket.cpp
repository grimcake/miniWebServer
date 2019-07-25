#include <iostream>
#include <unistd.h>
#include <string.h>
#include "Socket.h"

using namespace socketops;

Socket::Socket(int sockfd) :
    sockfd_(sockfd)
{

}

int socketops::createNonBlockfd(sa_family_t family)
{
    int sockfd = socket(family, SOCK_STREAM | SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    if(sockfd < 0) 
    {
        std::cout << "socket create error" << std::endl;
    }
    return sockfd;
}

int socketops::createBlockfd(sa_family_t family)
{
    int sockfd = socket(family, SOCK_STREAM | SOCK_CLOEXEC, IPPROTO_TCP);
    if(sockfd < 0) 
    {
        std::cout << "socket create error" << std::endl;
    }
    return sockfd;
}

void socketops::Close(int fd)
{
    int ret = close(fd);
    if(ret < 0)
    {
        std::cout << "socket close error" << std::endl;
    }
}

void socketops::Bind(int fd, const InetAddress& addr)
{
    int ret = bind(fd, addr.addr(), sizeof(struct sockaddr));
    if(ret < 0)
    {
        std::cout << "socket bind error" << std::endl;
    }
}

int socketops::Accept(int fd, const InetAddress& peeraddr)
{
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(struct sockaddr_in);
    int connfd = accept(fd, peeraddr.addr(), &addrlen);
    if(connfd < 0)
    {
        std::cout << "socket accept error" << std::endl;
    }
    else
    {
        std::cout << "socket accept success" << std::endl;
        char sendbuf[] = "111";
        send(connfd, sendbuf, sizeof(sendbuf), 0);
    }
    return connfd;
}

void socketops::Listen(int fd)
{
    int ret = listen(fd, SOMAXCONN);
    if(ret < 0)
    {
        std::cout << "listen error" << std::endl;
    }
}

struct sockaddr_in socketops::getLocalAddr(int fd)
{
    struct sockaddr_in peeraddr;
    memset(&peeraddr, 0, sizeof(peeraddr));
    socklen_t addrlen = static_cast<socklen_t>(sizeof peeraddr);
    if (::getpeername(fd, (struct sockaddr*)&peeraddr, &addrlen) < 0)
    {
        std::cout << "sockets::getPeerAddr error" << std::endl;
    }
    return peeraddr;
}
#include "Acceptor.h"
#include "Socket.h"

Acceptor::Acceptor(EventLoop* loop, const InetAddress& listenAddr) :
    loop_(loop),
    acceptSocket_(Socket::createNonBlockfd(listenAddr.family)),
    acceptChannel_(loop, acceptSocket_.fd()),
    listening_(false)
{
    acceptSocket_.Bind(acceptSocket_.fd(), listenAddr);
    acceptChannel_.setReadCallback(std::bind(&Acceptor::handleRead, this));
}

void Acceptor::handleRead()
{
    loop_->assertInLoopThread();
    InetAddress peerAddr;
    int connfd = acceptSocket_.Accept()

}

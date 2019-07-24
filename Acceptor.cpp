#include "Acceptor.h"
#include "Socket.h"

using namespace socketops;

Acceptor::Acceptor(EventLoop* loop, const InetAddress& listenAddr) :
    loop_(loop),
    acceptSocket_(socketops::createNonBlockfd(listenAddr.family())),
    acceptChannel_(loop, acceptSocket_.fd()),
    listening_(false)
{
    socketops::Bind(acceptSocket_.fd(), listenAddr);
    acceptChannel_.setReadCallback(std::bind(&Acceptor::handleRead, this));
}

void Acceptor::handleRead()
{
    loop_->assertInLoopThread();
    InetAddress peerAddr;
    int connfd = socketops::Accept(acceptSocket_.fd(), peerAddr);
}

void Acceptor::listen()
{
    listening_ = true;
    socketops::Listen(acceptSocket_.fd());
}
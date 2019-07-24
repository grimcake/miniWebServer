#include "Acceptor.h"
#include "Socket.h"

using namespace socketops;

Acceptor::Acceptor(EventLoop* loop, const InetAddress& listenAddr) :
    loop_(loop),
    acceptSocket_(socketops::createBlockfd(listenAddr.family())),
    acceptChannel_(loop, acceptSocket_.fd()),
    listening_(false)
{
    socketops::Bind(acceptSocket_.fd(), listenAddr);
    acceptChannel_.setReadCallback(std::bind(&Acceptor::handleRead, this));
    
    //listen();
    //handleRead();
}

void Acceptor::handleRead()
{
    loop_->assertInLoopThread();
    InetAddress peerAddr;
    int connfd = socketops::Accept(acceptSocket_.fd(), peerAddr);
    if(NewConnecCallback_) 
    {
        NewConnecCallback_(connfd, peerAddr);
    }
}

void Acceptor::listen()
{
    listening_ = true;
    socketops::Listen(acceptSocket_.fd());
    std::cout << "listen finish" << std::endl;
}
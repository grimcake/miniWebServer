#pragma once

#include <functional>
#include "InetAddress.h"
#include "Channel.h"
#include "Socket.h"


class Acceptor
{
public:
    typedef std::function<void(int sockfd, const InetAddress&)> NewConnectCallback;
    Acceptor(EventLoop* loop, const InetAddress& listenAddr);
    void setNewConnectCallback(const NewConnectCallback& cb) { NewConnecCallback_ = cb; }
    bool listening() const { return listening_; }
    void listen();
    void handleRead();

private:
    EventLoop* loop_;
    Socket acceptSocket_;
    Channel acceptChannel_;
    NewConnectCallback NewConnecCallback_;
    bool listening_;
};
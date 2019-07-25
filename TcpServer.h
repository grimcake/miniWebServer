#pragma once
#include <functional>
#include <memory>
#include <map>
#include "InetAddress.h"
#include "EventLoop.h"
#include "TcpConnection.h"
#include "Acceptor.h"

typedef std::shared_ptr<TcpConnection> TcpConnectionPtr;
typedef std::function<void (const TcpConnectionPtr&)> ConnectionCallback;

class TcpServer
{
public:
    TcpServer(EventLoop* loop, const InetAddress& listenAddr);
    ~TcpServer();
    void start();
    void setConnectionCallback(const ConnectionCallback& cb)
    {
        connectionCallback_ = cb;
    }
private:
    void newConnection(int sockfd, const InetAddress& peerAddr);
    typedef std::map<std::string, TcpConnectionPtr> ConnectionMap;
    EventLoop* loop_;
    const std::string name_;
    std::unique_ptr<Acceptor> acceptor_;
    ConnectionCallback connectionCallback_;
    bool started_;
    int nextConnId_;
    // 每个TcpConnection对象有一个名字，由TcpServer创建时生成，作为key
    // 新连接到来时，Acceptor回调newConnection()，用来创建TcpConnection对象conn
    // 把它加入ConnectionMap，设置好callback，再调用conn->connectEstablished()
    // 其中会回调用户提供的ConnectCallback
    ConnectionMap connections_;
};
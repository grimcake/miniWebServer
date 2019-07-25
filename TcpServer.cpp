#include <string>
#include "TcpServer.h"

using namespace socketops;

void TcpServer::newConnection(int sockfd, const InetAddress& peerAddr)
{
    loop_->assertInLoopThread();
    char buf[32];
    snprintf(buf, sizeof(buf), "#%d", nextConnId_);
    ++nextConnId_;
    std::string connName = name_+buf;
    std::cout << "new connection: " << connName << std::endl;
    InetAddress localAddr(socketops::getLocalAddr(sockfd));
    TcpConnectionPtr conn;
    connections_[connName] = conn;
    conn->setConnectionCallback(connectionCallback_);
    conn->connectEstablished();
}
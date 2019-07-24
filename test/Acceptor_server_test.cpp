#include <iostream>
#include "../EventLoop.h"
#include "../InetAddress.h"
#include "../Acceptor.h"
#include "../Socket.h"

void newConnection(int sockfd, const InetAddress& peerAddr)
{
    printf("a new connection\n");
    write(sockfd, "how are you?\n", 13);
    close(sockfd);
}

int main()
{
    printf("main(): pid = %d\n", getpid());
    InetAddress listenAddr(9981);
    EventLoop loop;
   
    Acceptor acceptor(&loop, listenAddr);

    acceptor.setNewConnectCallback(newConnection);
    acceptor.listen();
    acceptor.handleRead();
    //loop.loop();
}
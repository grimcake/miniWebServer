#include <iostream>
#include "../EventLoop.h"
#include "../InetAddress.h"

int main()
{
    printf("main(): pid = %d\n", getpid());
    InetAddress listenaddr(9981);
    
}
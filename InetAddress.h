#pragma once

#include <netinet/in.h>
#include <memory>

class InetAddress
{
public:
    InetAddress(){};
    InetAddress(int port)
    {
        addr_.sin_port = port;
        addr_.sin_family = AF_INET;
        addr_.sin_addr.s_addr = htons(INADDR_ANY);
    }
    InetAddress(const sockaddr_in& addr) :
        addr_(addr)
    {}

    sa_family_t family() const { return addr_.sin_family; }
    struct sockaddr* addr() const 
    { 
        return static_cast<struct sockaddr*>((void*)&addr_); 
    } 

private:
    
    struct sockaddr_in addr_;
};
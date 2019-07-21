#pragma once

#include <netinet/in.h>

class InetAddress
{
public:
    InetAddress(){};
    InetAddress(int port);
    InetAddress(const sockaddr_in& addr) :
        addr_(addr)
    {}

    sa_family_t family() const { return addr_.sin_family; }

private:
    struct sockaddr_in addr_;
};
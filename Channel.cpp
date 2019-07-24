#include <poll.h>
#include "Channel.h"

const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;

Channel::Channel(EventLoop* loop, int fd) :
    loop_(loop),
    fd_(fd),
    events_(0),
    revents_(0),
    state_(-1)
{

}

Channel::~Channel()
{}

void Channel::update() 
{

}

void Channel::handleEvent()
{
    // 描述字不是一个打开的文件
    if(revents_ & POLLNVAL)
    {
        std::cout << "revents is POLLNVAL" << std::endl;
    }
    if(revents_ & POLLIN)
    {
        if(readCallback_) readCallback_();
    }
    if(revents_ & POLLOUT)
    {
        if(writeCallback_) writeCallback_();
    }
}
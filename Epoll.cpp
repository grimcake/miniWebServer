#include <assert.h>
#include "Epoll.h"

Epoll::Epoll(EventLoop* loop) :
    ownerLoop_(loop),
    // 创建一个epoll描述符，进程替换映像时会关闭该描述符
    epollfd_(::epoll_create1(EPOLL_CLOEXEC)), 
    // 初始化vector
    events_(initEventListSize)
{

}

Epoll::~Epoll()
{}

void Epoll::updateChannel(Channel* channel)
{
    int state = channel->state();
    if(state == C_SNEW || state == C_SDELETED)
    {
        // 只有没在负责某个fd的channel能拿来负责新的fd
        if(state == C_SNEW)
        {
            int fd = channel->fd();
            // 没找到返回end
            assert(channels_.find(fd) == channels_.end());
            channels_[fd] = channel;
        }
        else
        {
            int fd = channel->fd();
            assert(channels_.find(fd) != channels_.end());
            assert(channels_[fd] == channel);
        }
        channel->setState(C_SADDED);
        update(EPOLL_CTL_ADD, channel);
    }
    else
    {
        int fd = channel->fd();
        assert(channels_.find(fd) != channels_.end());
        assert(channels_[fd] == channel);
        update(EPOLL_CTL_MOD, channel);
    }
}

void Epoll::update(int op, Channel* channel)
{
    struct epoll_event event;
    event.events = channel->events();
    event.data.ptr = channel; // 可以通过ptr来得到该event对应的channel
    int fd = channel->fd();
    if(epoll_ctl(epollfd_, op, fd, &event) < 0)
    {
        std::cout << "Epoll::update epoll_ctl error" << std::endl;
    }

}

void Epoll::poll(int timeout, ChannelList* activeChannels)
{
    int eventsNum = epoll_wait(epollfd_, &*events_.begin(), events_.size(), timeout);
    if(eventsNum > 0)
    {
        fillActiveChannels(eventsNum, activeChannels);
        // events_满了，扩容
        if(events_.size() == eventsNum)
        {
            events_.resize(2*events_.size());
        }
    }
    else if(eventsNum == 0)
    {
        std::cout << "epoll_wait gets 0 fd" << std::endl;
    }
    else 
    {
        std::cout << "epoll_wait error" << std::endl;
    }
}

void Epoll::fillActiveChannels(int eventsNum, ChannelList* activeChannels)
{
    assert(eventsNum <= events_.size());
    for(int i = 0; i<eventsNum; i++)
    {
        Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
        channel->setRevents(events_[i].events);
        activeChannels->push_back(channel);
    }

}
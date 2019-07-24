#pragma once
#include <sys/epoll.h>
#include <vector>
#include <map>
#include "EventLoop.h"
#include "Channel.h"

// channel的状态
const int C_SNEW = -1;
const int C_SADDED = 1;
const int C_SDELETED = 2;

class EventLoop;
class Channel;

namespace epollops
{
    
}

class Epoll
{
public:
    typedef std::vector<Channel*> ChannelList;
    Epoll(EventLoop* loop);
    ~Epoll();
    void updateChannel(Channel* channel);
    void update(int op, Channel* channel);
    void assertInLoopThread() 
    {
        //ownerLoop_->assertInLoopThread();
    }
    void poll(int timeout, ChannelList* activeChannels);
    void fillActiveChannels(int eventsNum, ChannelList* activeChannels);
    static Epoll* newPoller(EventLoop* loop);

private:
    static const int initEventListSize = 16;
    static const int newfd = 1;


    // 拥有该epoll的loop
    EventLoop* ownerLoop_;
    int epollfd_;
    // epoll事件列表
    typedef std::vector<struct epoll_event> EventList;
    EventList events_;
    // 每个文件描述符对应一个channel
    std::map<int, Channel*> channels_;
};
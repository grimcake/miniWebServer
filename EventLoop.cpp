#include <assert.h>
#include "EventLoop.h"
#include "./tools/Thread.h"

EventLoop::EventLoop():
    looping_(false),
    threadId_(CurrentThread::getCurrentTid()),
    poller_(new Epoll(this))
{

}

EventLoop::~EventLoop()
{}

void EventLoop::loop()
{
    assert(!looping_);
    assertInLoopThread();
    looping_ = true;
    quit_ = false;
    while(!quit_)
    {
        // 先清空活跃事件列表
        activeChannels_.clear();
        // 再往活跃列表中添加事件
        poller_->poll(1000000, &activeChannels_);
        // 遍历活跃事件列表，交由各Channel去处理事件
        for(ChannelList::iterator it = activeChannels_.begin(); it!=activeChannels_.end(); it++)
        {
            (*it)->handleEvent();
        }
    }
    std::cout << "stop looping" << std::endl;
    looping_ = false;
}


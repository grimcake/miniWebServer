#pragma once
#include <iostream>
#include <unistd.h>
#include <memory>
#include "Epoll.h"
#include "tools/Thread.h"
#include "Channel.h"

class Epoll;
class Channel;

class EventLoop
{
public:
    EventLoop();
    ~EventLoop();
    void loop();

    // 判断EventLoop对象是否在当前线程中
    bool isInCurrentThread() const {
        return threadId_ == CurrentThread::getCurrentTid();
    }

    // 确保一个线程只有一个EventLoop对象
    void assertInLoopThread() const {
        if(!isInCurrentThread()) {
            std::cout << "one loop per thread!" << std::endl;
        }
    }

private:
    typedef std::vector<Channel*> ChannelList;
    bool quit_;
    bool looping_;
    const pid_t threadId_;
    // 因为一个loop只会有一个poller，所以用独占型智能指针
    std::unique_ptr<Epoll> poller_;
    ChannelList activeChannels_;
};
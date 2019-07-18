#pragma once
#include <iostream>
#include <unistd.h>
#include "tools/Thread.h"

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
    bool looping_;
    const pid_t threadId_;
};
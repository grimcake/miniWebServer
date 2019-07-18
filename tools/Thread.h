#pragma once
#include <unistd.h>
#include <functional>
#include <sys/syscall.h>
#include <iostream>

class CurrentThread
{
public:
    static pid_t getCurrentTid() {
        return syscall(SYS_gettid);
    }
};


class Thread
{
public:
    typedef std::function<void()> ThreadCallBack;
    Thread(ThreadCallBack func);
    ~Thread();
    void start();
    void join();
    static void* runInThread(void *);

private:
    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    ThreadCallBack func_;
    
};
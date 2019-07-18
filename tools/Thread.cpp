#include "Thread.h"

Thread::Thread(ThreadCallBack func):
    func_(std::move(func)),
    started_(false),
    joined_(false)
{
    
}

Thread::~Thread() 
{
}

void Thread::start() 
{
    if(pthread_create(&pthreadId_, NULL, runInThread, this))
    {
        std::cout << "pthread_create error" << std::endl;
    }
    else {
        started_ = true;
    }
}

void *Thread::runInThread(void *arg) 
{
    Thread *pt = static_cast<Thread*>(arg);
    pt->func_();
    return NULL;
}
#include <assert.h>
#include "EventLoop.h"
#include "./tools/Thread.h"

EventLoop::EventLoop():
    looping_(false),
    threadId_(CurrentThread::getCurrentTid())
{

}

EventLoop::~EventLoop()
{}

void EventLoop::loop()
{
    assert(!looping_);
    assertInLoopThread();
    looping_ = true;

    looping_ = false;
}


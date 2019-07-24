#pragma once
#include "EventLoop.h"
#include <functional>

class EventLoop;

class Channel
{
public:
    typedef std::function<void()> ReadEventCallback;
    typedef std::function<void()> EventCallback;
    Channel(EventLoop* loop, int fd);
    ~Channel();

    // 由EventLoop::loop()调用， 根据revents_的值分别调用不同的用户回调
    void handleEvent();
    void setReadCallback(EventCallback cb) { readCallback_ = std::move(cb); }
    void setWriteCallback(EventCallback cb) { writeCallback_ = std::move(cb); }
    void setErrorCallback(EventCallback cb) { errorCallback_ = std::move(cb); }
    int fd() const { return fd_; }
    int events() const { return events_; }
    int revents() const { return revents_; }
    int state() const { return state_; }
    void setRevents(int revents) { revents_ = revents; }
    void setState(int state) { state_ = state; }


private:
    void update();
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;
 
    EventLoop* loop_;
    const int fd_;
    int events_; // 关心的事件
    int revents_; // 正在活动的事件
    // 标记当前channel的状态
    // -1:未负责任意一个描述符
    // 1:已经负责某一个描述符
    // 2:已经不再负责某一个描述符
    int state_;
    ReadEventCallback readCallback_;
    EventCallback writeCallback_;
    EventCallback errorCallback_;


};
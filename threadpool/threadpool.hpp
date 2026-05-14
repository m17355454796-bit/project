#ifndef __THREADPOOL_HPP__
#define __THREADPOOL_HPP__

#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <pthread.h>
#include<queue>
#include<vector>
using namespace std;
class Task
{
private:
    void(*_func)(void*);
    void*_arg;
public:
    Task():_func(nullptr),
            _arg(nullptr)
            {
            }
    Task(void(*func)(void*),void*arg):
        _func(func),
        _arg(arg)
    {}
    void Run()
    {
        if(_func!=nullptr)
        {
            _func(_arg);
        }
    }
};
class WaitQueue{
    private:
    queue<Task> _wait_queue;
    int _capacity;
    pthread_mutex_t _mutex;
    pthread_cond_t _not_empty;
    pthread_cond_t _not_full;
    bool _stop;
    public:
    WaitQueue(int capacity)
    {
        _capacity=capacity;
        pthread_mutex_init(&_mutex,nullptr);
        pthread_cond_init(&_not_empty,nullptr);
        pthread_cond_init(&_not_full,nullptr);
        _stop=false;
    }
    ~WaitQueue()
    {
        pthread_mutex_destroy(&_mutex);
        pthread_cond_destroy(&_not_empty);
        pthread_cond_destroy(&_not_full);
    }
    bool Push(const Task&task)
    {
        pthread_mutex_lock(&_mutex);
        while(_capacity==_wait_queue.size()&&_stop==false)
        {
            pthread_cond_wait(&_not_full,&_mutex);
        }
        if(_stop==true)
        {
            pthread_mutex_unlock(&_mutex);
            return false;
        }
        _wait_queue.push(task);
        pthread_cond_signal(&_not_empty);
        pthread_mutex_unlock(&_mutex);
        return true;
    }
    bool Pop(Task&task)
    {
        pthread_mutex_lock(&_mutex);
        while(_wait_queue.size()==0&&_stop==false)
        {
            pthread_cond_wait(&_not_empty,&_mutex);
        }
        if(_wait_queue.size()==0&&_stop==true)
        {
            pthread_mutex_unlock(&_mutex);
            return false;
        }
        task=_wait_queue.front();
        _wait_queue.pop();
        pthread_cond_signal(&_not_full);
        pthread_mutex_unlock(&_mutex);
        return true;
    }
    void Stop()
    {
        pthread_mutex_lock(&_mutex);
        _stop=true;
        pthread_cond_broadcast(&_not_empty);
        pthread_cond_broadcast(&_not_full);
        pthread_mutex_unlock(&_mutex);
    }
};
class ThreadPool
{
private:
    int _pthread_num;
    vector<pthread_t> _pthread;
    WaitQueue _wait_queue;
public:
    ThreadPool(int thread_num,int queue_capacity): 
    _pthread_num(thread_num),
    _wait_queue(queue_capacity)
    {
        _pthread.resize(_pthread_num);
    }
    void start()
    {
        for(int i=0;i<_pthread_num;i++)
        {
            pthread_create(&_pthread[i],nullptr,worker,this);
        }
    }
    void Stop()
    {
        _wait_queue.Stop();
        for(int i=0;i<_pthread_num;i++)
        {
            pthread_join(_pthread[i],nullptr);
        }
    }
    bool PushTask(const Task&task)
    {
        return _wait_queue.Push(task);
    }
private:
    static void*worker(void*arg)
    {
        ThreadPool*tp=(ThreadPool*)arg;
        while(1)
        {
            Task task;
            bool ret=tp->_wait_queue.Pop(task);
            if(ret==false)
            {
                break;
            }
            task.Run();
        }
        return nullptr;
    }
};
#endif



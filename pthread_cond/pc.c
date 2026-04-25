#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#define QUEUE_CAPACITY 5
int queue[QUEUE_CAPACITY];
int size=0;
int head=0;
int tail=0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty=PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full=PTHREAD_COND_INITIALIZER;
void push(int data)
{
    queue[tail]=data;
    tail=(tail+1)%QUEUE_CAPACITY;
    size++;
}
int pop()
{
    int data=queue[head];
    head=(head+1)%QUEUE_CAPACITY;
    size--;
    return data;
}
void* consumer(void*arg)
{
    
    for(int i=0;i<20;i++)
    { 
        pthread_mutex_lock(&mutex);
        while(size==0)
        {
            printf("条件为空，消费者等待\n");
            pthread_cond_wait(&not_empty,&mutex);
        }
        int data=pop();
        printf("消费者消费了一个数据:%d,size=%d\n",data,size);
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);
        sleep(1);
    }
    return NULL;
}
void* producer(void*arg)
{
    for(int i=1;i<=20;i++)
    {
        pthread_mutex_lock(&mutex);
         while(size==QUEUE_CAPACITY)
        {
            printf("队列满了，生产者等待\n");
            pthread_cond_wait(&not_full,&mutex);
        }
        push(i*10);
        printf("生产者生产一个数据:%d size=%d\n",i*10,size);
        pthread_cond_signal(&not_empty);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
int main()
{
    pthread_t c;
    pthread_t p;
    pthread_create(&c,NULL,consumer,NULL);
    pthread_create(&p,NULL,producer,NULL);
    pthread_join(p,NULL);
    pthread_join(c,NULL);
    return 0;
}
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>
#define QUEUE_CAPACITY 5
#define TOTAL_TASK 30
typedef struct Task{
    void(*function)(void*arg);
    void*arg;
}Task;
int produced_count=0;
int consumed_count=0;
Task queue[QUEUE_CAPACITY];
int size=0;
int head=0;
int tail=0;
int shutdown=0;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t not_empty=PTHREAD_COND_INITIALIZER;
pthread_cond_t not_full=PTHREAD_COND_INITIALIZER;
void push(Task task)
{
    queue[tail]=task;
    tail=(tail+1)%QUEUE_CAPACITY;
    size++;
}
Task pop()
{
    Task task=queue[head];
    head=(head+1)%QUEUE_CAPACITY;
    size--;
    return task;
}
void add_task(void(*function)(void*),void*arg)
{
    pthread_mutex_lock(&mutex);
    while(size==QUEUE_CAPACITY)
    {
      printf("队列满了，生产者等待\n");
      pthread_cond_wait(&not_full,&mutex);
    }
    Task task;
    task.function=function;
    task.arg=arg;
    push(task);
    pthread_cond_signal(&not_empty);
    pthread_mutex_unlock(&mutex);
}
void print_task(void*arg)
{
    int num=*(int*)arg;
    printf("线程正在执行任务%d\n",num);
    free(arg);
}
void* worker(void*arg)
{
    
    while(1)
    {
        pthread_mutex_lock(&mutex);
         while(size==0&&shutdown==0)
        {
            printf("条件为空，消费者等待\n");
            pthread_cond_wait(&not_empty,&mutex);
            printf("消费者被唤醒，并且重新拿到 mutex\n");
        }
        if(size==0&&shutdown==1)
        {
            pthread_mutex_unlock(&mutex);
            printf("所有任务已经完成！\n");
            break;
        }
        Task task=pop();
        consumed_count++;
        printf("消费者取出了一个任务,size=%d\n",size);
        pthread_cond_signal(&not_full);
        pthread_mutex_unlock(&mutex);
        task.function(task.arg);
        sleep(1);
    }
    return NULL;
}
void* producer(void*arg)
{
    while (1)
    {
        pthread_mutex_lock(&mutex);
         if(produced_count>=TOTAL_TASK)
        {
            pthread_cond_broadcast(&not_empty);
            pthread_mutex_unlock(&mutex);
            break;
        }
        produced_count++;
        int*num=malloc(sizeof(int));
        *num=produced_count;
        pthread_mutex_unlock(&mutex);
        add_task(print_task,num);
    }    
    return NULL;
}
int main()
{
    pthread_t workers[3];
    for(int i=0;i<3;i++)
    {
        pthread_create(&workers[i],NULL,worker,NULL);
    }
    for(int i = 1; i <= TOTAL_TASK; i++)
    {
        int* num = malloc(sizeof(int));
        *num = i;
        add_task(print_task, num);
    }
    pthread_mutex_lock(&mutex);
        shutdown=1;
        pthread_cond_broadcast(&not_empty);
        pthread_mutex_unlock(&mutex);
    for(int i=0;i<3;i++)
    {
        pthread_join(workers[i],NULL);
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&not_empty);
    pthread_cond_destroy(&not_full);
    return 0;
}
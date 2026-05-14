#include "threadpool.hpp"
#include <cstdio>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <pthread.h>

void PrintTask(void* arg)
{
    int num = *(int*)arg;

    printf("thread: %lu, task: %d\n", (unsigned long)pthread_self(), num);

    delete (int*)arg;

    sleep(1);
}

int main()
{
    ThreadPool pool(3, 5);

    pool.start();

    for(int i = 0; i < 10; i++)
    {
        int* p = new int(i);

        Task task(PrintTask, p);

        pool.PushTask(task);
    }

    sleep(5);

    pool.Stop();

    return 0;
}

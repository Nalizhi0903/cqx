#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include "MSgQueue.hpp"
using namespace std;
#define THREAD_COUNT 1

void* cons_start(void* arg)
{
    MsgQueue* mq = (MsgQueue*)arg;
    while(1)
    {
        int tmp = mq->Pop();
        printf("i am cons_start, %d\n", tmp);
    }
}

void* prod_start(void* arg)
{
    MsgQueue* mq = (MsgQueue*)arg;
    int i = 0;
    while(1)
    {
        mq->Push(i++);
        //sleep;
    }
}

int main()
{
    MsgQueue* mq = new MsgQueue();
    pthread_t cons[THREAD_COUNT], prod[THREAD_COUNT];
    for(int i = 0; i < THREAD_COUNT; i++)
    {
        int ret = pthread_create(&cons[i], NULL, cons_start, (void*)mq);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }
        ret = pthread_create(&prod[i], NULL, prod_start, (void*)mq);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }
    }
    for(int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(cons[i], NULL);
        pthread_join(prod[i], NULL);
    }
    return 0;
}

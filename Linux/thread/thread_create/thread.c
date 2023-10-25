#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void* fun(void* arg)
{
    printf("i am thread\n");
    while(1)
    {

    }
}

int main()
{
    //创建线程
    //pthread_create(pthread_t* tid, const pthread_attr_t* attr, (void*)(*start_routine)(void*), void* arg)
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, fun, NULL);
    if(ret < 0)
    {
        perror("thread");
        return 0;
    }
    printf("create thread successfully\n");
    sleep(1);
    while(1)
    {

    }
    return 0;
}

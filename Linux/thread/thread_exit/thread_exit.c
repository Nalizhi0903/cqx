#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
void* fun(void* arg)
{
    printf("i am thread %d\n", *((int*)arg));
    //什么时候线程不使用该内存，什么时候释放
    free(arg);
    int tid = pthread_self();//线程可以获取自己的线程标识符
    pthread_cancel(pthread_self());//线程将自己取消掉
    //pthread_exit(NULL);//线程退出
    while(1)
    {

    }
}

int main()
{
    //创建线程
    //pthread_create(pthread_t* tid, const pthread_attr_t* attr, (void*)(*start_routine)(void*), void* arg)
    int i;
    for(i = 0; i < 5; i++)
    {
        int* num = (int*)malloc(sizeof(int)*1);
        *num = i;
        pthread_t tid;
        int ret = pthread_create(&tid, NULL, fun, (void*)num);
        if(ret < 0)
        {
            perror("thread");
            return 0;
        }
        printf("create thread %d successfully\n", i);
        sleep(1);
        //不能在这释放，会导致线程非法访问,在线程中释放最好
    }
    sleep(1);
    while(1)
    {

    }
    return 0;
}

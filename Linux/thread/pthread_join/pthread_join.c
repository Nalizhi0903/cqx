#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* my_thread_start(void* arg)
{
   sleep(10);
   //pthread_exit(0);
   return NULL;
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, my_thread_start, NULL);
    if(ret < 0)
    {
        perror("pthread_create");
        return 0;
    }
    //创建线程成功，但是默认属性（joinable），需要其他线程回收该线程的资源
    pthread_join(tid, NULL);//阻塞等待
    return 0;
}

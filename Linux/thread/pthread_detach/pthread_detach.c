#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* my_fun(void* arg)
{
    int i = 0;
    for(; i<5;i++)
    {
        printf("i am my(), %d\n", i);
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    int ret = pthread_create(&tid, NULL, my_fun, NULL);
    if(ret < 0)
    {
        perror("pthread_create");
        return 0;
    }
    pthread_detach(tid);
    while(1)
    {
        sleep(1);
    }
    return 0;
}

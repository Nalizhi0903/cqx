#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t _lock;
pthread_cond_t _cond_lock;
void* fun(void* data)
{
    pthread_mutex_lock(&_lock);
    while(1)
    {
        pthread_cond_wait(&_cond_lock, &_lock);
    }
    printf("Data is %d\n", *((int*)data));
    pthread_cond_signal(&_cond_lock);
    pthread_mutex_unlock(&_lock);
    return NULL;
}

int main()
{
    pthread_t tid[2];
    pthread_mutex_init(&_lock, NULL);
    int i;
    for(i = 0; i < 2; i++)
    {
        int* num = (int*)malloc(1);
        *num = i;
        int ret = pthread_create(&tid[i], NULL, fun, (void*)num);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }
    }
    for(i = 0; i < 2;i++)
    {
        pthread_join(tid[i], NULL);
    }
    sleep(1);

    return 0;
}

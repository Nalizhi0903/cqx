#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int g_tmp = 1;
pthread_rwlock_t g_lock;
void* my_thread_start(void* arg)
{
    pthread_rwlock_rdlock(&g_lock);
    printf("i am %p, g_tmp is %d\n", pthread_self(), g_tmp);
    return NULL;
}

int main()
{
    pthread_rwlock_init(&g_lock, NULL);
    pthread_t tid[2];
    for(int i = 0; i < 2; i++)
    {
        int ret = pthread_create(&tid[i], NULL, my_thread_start, NULL);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }
    }
    for(int i = 0; i < 2; i++)
    {
        pthread_join(tid[i], NULL);
    }
    pthread_rwlock_destroy(&g_lock);
    return 0;
}

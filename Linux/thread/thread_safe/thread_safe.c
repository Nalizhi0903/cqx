#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_COUNT 2

int g_tickets = 1000;
pthread_mutex_t l;//互斥锁要在线程前初始化
void* get_tickets(void* art)
{
    while(1)
    {
        pthread_mutex_lock(&l);//在访问临界资源前加锁
        if(g_tickets > 0)
        {
            printf("i am %p, i get g_tickets %d\n", pthread_self(), g_tickets);
            g_tickets--;
        }
        else 
        {
            pthread_mutex_unlock(&l);
            break;
        }
        pthread_mutex_unlock(&l);
    }
    while(1)
    {

    }
    return NULL;
}

void* my_thread_fun(void* arg)
{
    return NULL;    
}

int main()
{
    pthread_mutex_init(&l, NULL);
    pthread_t tid[THREAD_COUNT];
    for(int i = 0; i< THREAD_COUNT; i++)
    {
        int ret = pthread_create(&tid[i], NULL, get_tickets, NULL);
        if(ret < 0)
            return 0;
    }   
    for(int i = 0; i < THREAD_COUNT; i++)
    {
        pthread_join(tid[i], NULL);
    }
    pthread_mutex_destroy(&l);
    return 0;
}

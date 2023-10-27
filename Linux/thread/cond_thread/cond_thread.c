#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define THREAD_COUNT 2

int g_bowl = 0;
pthread_mutex_t g_lock;
//创建两个条件变量，防止全部线程都在PCB等待队列
pthread_cond_t make_cond;
pthread_cond_t eat_cond;

void* eat_start(void* arg)
{
    pthread_detach(pthread_self());
    while(1)
    {
        pthread_mutex_lock(&g_lock);
        if(g_bowl <= 0)
            pthread_cond_wait(&eat_cond, &g_lock);
        printf("i eat, there are %d bowls of noodles\n", g_bowl--);
        pthread_mutex_unlock(&g_lock);
        //通知做面人做面
        pthread_cond_signal(&make_cond);
    }
    return NULL;
}

void* make_start(void* arg)
{
    pthread_detach(pthread_self());
    while(1)
    {
        pthread_mutex_lock(&g_lock);
        if(g_bowl > 0)
            pthread_cond_wait(&make_cond, &g_lock);
        printf("i make noodle, there are %d bowls of noodle\n", ++g_bowl);
        pthread_mutex_unlock(&g_lock);
        //通知吃面人吃面
        pthread_cond_signal(&eat_cond);
    }
    return NULL;
}
/*
void* eat_start(void* arg)
{
    pthread_detach(pthread_self());
    while(1)
    {
        if(g_bowl > 0)//频繁判断是否有面，消耗cpu资源
        {
            pthread_mutex_lock(&g_lock);
            printf("i eat, there are %d bowls of noodles\n", --g_bowl);
            pthread_mutex_unlock(&g_lock);
        }
        else 
        {
            printf("i want to eat, there is no noodles\n");
            sleep(1);
        }
    }
    return NULL;
}

void* make_start(void* arg)
{
    pthread_detach(pthread_self());
    while(1)
    {
        pthread_mutex_lock(&g_lock);
        printf("i make noodle, there are %d bowls of noodle\n", ++g_bowl);
        pthread_mutex_unlock(&g_lock);
        sleep(1);
    }
    return NULL;
}
*/

int main()
{
    pthread_mutex_init(&g_lock, NULL);
    pthread_cond_init(&make_cond, NULL);
    pthread_cond_init(&make_cond, NULL);
    pthread_t eat_tid[THREAD_COUNT], make_tid[THREAD_COUNT];
    int i;
    for(i = 0; i < THREAD_COUNT; i++)
    {
        int ret = pthread_create(&eat_tid[i], NULL, eat_start, NULL);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }
        ret = pthread_create(&make_tid[i], NULL, make_start, NULL);
        if(ret < 0)
        {
            perror("pthread_create");
            return 0;
        }        
    }
    while(1)
    {
        sleep(1);
    }
    pthread_mutex_destroy(&g_lock);
    pthread_cond_destroy(&make_cond);
    pthread_cond_destroy(&eat_cond);
    return 0;
}

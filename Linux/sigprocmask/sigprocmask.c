#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void sigcallback(int sig)
{
    printf("sig is %d\n", sig);
}
int main()
{
    sigset_t set;
    //signal(9, sigcallback);//9/19都是不能被阻塞的，也不能被自定义处理！
    signal(2, sigcallback);//2号信号是非可靠信号，可能会丢失
    signal(40, sigcallback);//40号信号是可靠信号，不会丢失
    sigfillset(&set);
    sigprocmask(SIG_SETMASK, &set, NULL);
    getchar();
    sigprocmask(SIG_UNBLOCK, &set, NULL);
    while(1)
    {
        sleep(1);
    }
    return 0;
}

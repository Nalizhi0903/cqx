#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void sigcallback(int sig)
{
    printf("sig is %d\n", sig);
    sleep(5);
    wait();
}

int main()
{
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork");
        return 0;
    }
    else if(pid == 0)
    {
        sleep(10);
        exit(1);
    }
    else
    {
        signal(SIGCHLD, sigcallback);//father不会受wait阻塞
        //father TODO F-self things
        while(1)
        {
            sleep(1);
            printf("i am father\n");
        }
    }
    return 0;
}

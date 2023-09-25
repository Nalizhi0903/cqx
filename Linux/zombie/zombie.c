#include <stdio.h>
#include <unistd.h>
//子进程先于父进程退出，子进程会变成僵尸进程
int main()
{
    pid_t ret = fork();
    if(ret < 0)
    {
       perror("fork");
       return 0;
    }
    else if(ret == 0)
    {
        printf("i am child, pid is %d, ppid is %d\n", getpid(), getppid());
    }
    else 
    {
        while(1)
        {
            printf("i am father\n");
            sleep(1);
        }
    }
}

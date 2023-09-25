#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//在命令行当中输入的程序启动命令启动的进程是由bash创建出来的
//父进程在子进程前退出，子进程就会变为孤儿进程被pid为1的init进程收养
int main()
{
    pid_t ret = fork();
    if(ret < 0)
    {
        perror("fork()");
        return 0;
    }
    else if(ret == 0)
    {
        printf("i am child, pid is %d\n", getpid());
        sleep(10);
    }
    else 
    {
        printf("i am father, pid is %d\n", getpid());
        sleep(3);
        exit(0);
    }
    //孤儿进程并没有危害，在孤儿进程退出后被1号进程回收资源，防止变成僵尸进程
    return 0;
}

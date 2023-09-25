#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main()
{
    pid_t ret = fork();
    if(ret < 0)
        return 0;
    else if(ret == 0)
    {
        //child
        printf("i am child...\n");
        //异常
        int* lp =NULL;
        *lp = 10;
        exit(1);
    }
    else 
    {
        //father
        int status;
        wait(&status);
        if((status & 0x7f) > 0)
            //异常
            printf("error, signal is %d, coredump is %d\n", status & 0x7f, (status >> 7) & 0x1);
        else 
        {
            //正常
            printf("正常退出： return code is %d", (status >> 8) & 0xff);
        }
    }

    return 0;
}

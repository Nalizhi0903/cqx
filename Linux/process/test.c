#include <stdio.h>
#include <unistd.h>
int main()
{
    int ret = fork();
    while(1)
    {
        if(ret == 0)
        {
            printf("i am child, pid is %d, ppid is %d\n", getpid(), getppid());
        }
        else 
            printf("i am father, pid is %d\n", getpid());
        sleep(1);
    }
    return 0;
}

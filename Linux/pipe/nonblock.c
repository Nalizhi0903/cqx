#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
int main()
{
    int fd[2];
    int ret = pipe(fd);
    if(ret < 0)
    {
        perror("pipe");
        return 0;
    }
    pid_t pid = fork();
    if(pid < 0)
    {
        perror("fork");
        return 0;
    }
    else if(pid == 0)
    {
        close(fd[0]);
        int count = 0;
        int Flag = fcntl(fd[1], F_GETFL);
        fcntl(fd[1], F_SETFL, Flag | O_NONBLOCK);
        const char* str = "Linux-88";
        while(1)
        {
            int w_t = write(fd[1], str, strlen(str));
            printf("i am son, w_t is %d\n", w_t);
            printf("count is : %d\n", count++);
        }
    }
    else 
    {   
        //close(fd[1]);//写不关，read一直读，返回-1，写关闭，返回0
        //sleep(1);
        //int FLAG = fcntl(fd[0], F_GETFL); 
        //fcntl(fd[0], F_SETFL, FLAG | O_NONBLOCK);
        //char buf[1024] = {0};
        //while(1)
        //{
        //    sleep(1);
        //    int r_d = read(fd[0], buf, sizeof(buf)-1);
        //    printf("i am father, ret = %d, buf is : %s\n",r_d, buf);
        //    memset(buf, 0, sizeof buf);
        //}
        close(fd[0]);
        close(fd[1]);
    }

    return 0; 
}

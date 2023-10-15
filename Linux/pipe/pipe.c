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
        close(fd[0]);//关闭不用的描述符，读端
        const char* str = "abc";
        write(fd[1], str, strlen(str));
        const char* str1 = "def";
        write(fd[1], str1, strlen(str1));
    }
    else 
    {
        close(fd[1]);//关闭不用的描述符，写端
        sleep(1);
        char buf[1024]={0};
        read(fd[0], buf, sizeof(buf) - 1);
        printf("i am father : read buf: [%s]\n", buf);
    }
    while(1)
    {
        sleep(1);
    }
    return 0;
}

#if 0
int main()
{
    int fd[2];
    int ret = pipe(fd);
    if(ret < 0)
    {
        perror("pipe");
        return 0;
    }
    int r_attr = fcntl(fd[0], F_GETFL);
    printf("r_attr : %d\n", r_attr);
    int w_attr = fcntl(fd[1], F_GETFL);
    printf("w_attr : %d\n", w_attr);
    return 0;
}
#endif

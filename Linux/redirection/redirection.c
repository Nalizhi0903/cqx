#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main()
{
    //int dup2(int oldfd, int newfd);将newfd的值重定向为oldfd，即newfd拷贝oldfd，oldfd/newfd均是文件描述符
    int fd = open("1.txt", O_RDWR | O_CREAT, 0664);
    if(fd < 0)
    {
        perror("open");
        return 0;
    }
    //重定向标准输出将hello输入到1.txt文件中
    //dup2(fd, 1);
    //printf("hello\n");
    //重定向标准输入，将标准输入定向到1.txt文件中，用scanf获取文件中的内容存放在str中，并打印出来
    char str[10] = {0};
    dup2(fd, 0);
    scanf("%s", str);
    printf("%s", str); 
    return 0;
}

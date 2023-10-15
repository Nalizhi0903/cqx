#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
    int fd = open("./fifo_test",O_RDONLY);
    if(fd<0)
    {
        perror("open");
        return 0;
    }
    char buf[1024] = {0};
    while(1)
    {
        read(fd, buf, sizeof(buf));
        printf("buf ： %s\n", buf);
    }
    return 0;
}

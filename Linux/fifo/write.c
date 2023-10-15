#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main()
{
    int fd = open("./fifo_test",O_WRONLY);
    if(fd < 0)
    {
        perror("open");
        return 0;
    }
    while(1)
    {
        sleep(1);
        const char* str = "Linux-88";
        write(fd,str,strlen(str));
    }
    return 0;
}

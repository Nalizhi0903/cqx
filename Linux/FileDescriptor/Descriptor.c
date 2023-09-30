#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
int main()
{
   int fd = open("./1.txt", O_RDWR | O_CREAT, 0664); 
   if(fd < 0)
   {
       perror("open");
       return 0;
   }
   printf("fd = %d\n", fd);
   while(1)
   {
       sleep(1);
   }
   close(fd);
    return 0;
}

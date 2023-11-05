#include <iostream>
#include <unistd.h>
#include <poll.h>

int main()
{
  //目标：poll监控0号文件描述符的可读事件
  //1.组织事件结构体数组
  //2.调用poll函数
  //3.处理0号文件描述符的可读事件
  
  struct pollfd arr[10];
  arr[0].fd = 0;
  arr[0].events = POLLIN;
  int ret = poll(arr, 1, -1);
  if(ret < 0)
  {
    perror("poll");
    return 0;
  }
  char buf[1024] = {0};
  read(0, buf, sizeof(buf) - 1);
  printf("[buf is] %s\n", buf);
  return 0;
}

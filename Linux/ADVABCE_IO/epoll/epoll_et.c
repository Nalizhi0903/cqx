#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>

int main()
{
  /*
   * 目标：验证epoll的et
   * 方法：通过0号文件描述符的可读事件进行验证
   * */
  int epfd = epoll_create(10);
  if(epfd < 0)
  {
    perror("epoll_create");
    return 0;
  }
  struct epoll_event epv;
  epv.events = EPOLLIN;
  epv.data.fd = 0;
  epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &epv);
  struct epoll_event epvs[5];
  int ret = epoll_wait(epfd, epvs, sizeof(epvs)/sizeof(epvs[0]), -1);
  if(ret < 0)
  {
    perror("epoll_wait");
    return 0;
  }
  char buf[1024] = {0};
  read(0, buf, sizeof(buf) - 1);
  printf("[buf is] %s\n", buf);
  return 0;
}

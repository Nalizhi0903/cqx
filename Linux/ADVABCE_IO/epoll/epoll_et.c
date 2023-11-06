#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>

int main()
{
  /*
   * 目标：验证epoll的et
   * 方法：通过0号文件描述符的可读事件进行验证
   * */
  int flag = fcntl(0, F_GETFL);
  fcntl(0, F_SETFL, flag | O_NONBLOCK);
  int epfd = epoll_create(10);
  if(epfd < 0)
  {
    perror("epoll_create");
    return 0;
  }
  struct epoll_event epv;
  epv.events = EPOLLIN | EPOLLET;//ET模式  触发一次，需要搭配循环将数据读完+设置非阻塞
  //epv.events = EPOLLIN;
  epv.data.fd = 0;
  epoll_ctl(epfd, EPOLL_CTL_ADD, 0, &epv);
  while(1)
  {
    struct epoll_event epvs[5];
    int ret = epoll_wait(epfd, epvs, sizeof(epvs)/sizeof(epvs[0]), -1);
    if(ret < 0)
    {
      perror("epoll_wait");
      return 0;
    }
    //问题：如何判断已经读完
    while(1)
    {
      char buf[3] = {'\0'};
      int r_size = read(0, buf, sizeof(buf) - 1);
      if(r_size < 0)
      {
        if(errno == EAGAIN || errno == EWOULDBLOCK)
        {
          //认为是正常的，缓冲区没有数据的时候，非阻塞调用会走到这里
          printf("nonblock\n");
          break;
        }
        return 0;
      }
      printf("[buf is] %s\n, r_size = %d\n", buf, r_size);
      sleep(1);
      //只能解决部分问题，子符数为奇数的时候
      if(r_size < (int)sizeof(buf) - 1)
      {
        printf("break...\n");
        break;
      }
    }
  }
  return 0;
}

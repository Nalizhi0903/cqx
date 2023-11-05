#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>

int main()
{
  //目标：改造单线程tcp代码
  //做法：
  //1.tcp的准备工作
  //2.创建epoll操作句柄
  //3.添加侦听套接字
  //4.循环处理
  //  1.调用epoll_wait
  //  2.分情况处理
  int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(sockfd < 0)
  {
    perror("socket");
    return 0;
  }
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(38989);
  addr.sin_addr.s_addr = inet_addr("0.0.0.0");//0.0.0.0 :表示当前机器的任意一块网卡
  int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
  if(ret < 0)
  {
    perror("bind");
    return 0;
  }
  ret = listen(sockfd, 5);//已完成队列大小为5，最多可以放五个连接
  if(ret < 0)
  {
    perror("listen");
    return 0;
  }
  int epfd = epoll_create(10);
  if(epfd < 0)
  {
    perror("epoll_create");
    return 0;
  }
  struct epoll_event ep;
  ep.events = EPOLLIN;
  ep.data.fd = sockfd;
  epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &ep);
  while(1)
  {
    struct epoll_event eps[10];
    int ret = epoll_wait(epfd, eps, sizeof(eps)/sizeof(eps[0]), -1);
    if(ret < 0)
    {
      perror("epoll_wait");
      return 0;
    }
    for(int i = 0; i < ret; i++)
    {
      if(sockfd == eps[i].data.fd)
      {
        //accept
        //添加套接字到epoll中
        int newsockfd = accept(eps[i].data.fd, NULL, NULL);
        if(newsockfd < 0)
        {
          continue;
        }
        struct epoll_event new_ep;
        new_ep.data.fd = newsockfd;
        new_ep.events = EPOLLIN;
        epoll_ctl(epfd, EPOLL_CTL_ADD, newsockfd, &new_ep);
      }
      else 
      {
        char buf[1024] = {0};
        size_t r_size = recv(eps[i].data.fd, buf, sizeof(buf) - 1, 0);
        if(r_size < 0)
        {
          continue;
        }
        else if(r_size == 0)
        {
          epoll_ctl(epfd, EPOLL_CTL_DEL, eps[i].data.fd, NULL);
          close(eps[i].data.fd);
          continue;
        }
        printf("[recieve from %d, msg is] %s\n", eps[i].data.fd, buf);
        memset(buf, '\0', 1024);
        snprintf(buf, sizeof(buf) -1, "hello %d, i am sever.", eps[i].data.fd);
        send(eps[i].data.fd, buf, strlen(buf), 0);
      }
      
    }
  }
 
  return 0; 
}

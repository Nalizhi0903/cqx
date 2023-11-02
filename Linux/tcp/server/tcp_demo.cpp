#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
int main()
{
  /*  1.创建侦听套接字
   *  2.绑定地址信息（IP，PORT）
   *  3.监听
   *  4.获取新连接
   *  5.收发数据
   *  6.关闭套接字
   * */
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
  int new_sockfd = accept(sockfd, NULL, NULL);//accept有阻塞属性，没有新连接阻塞等待，有新连接就执行
  if(new_sockfd < 0)
  {
    perror("accept");
    return 0;
  }
  char buf[1024] = {0};
  ssize_t recv_size = recv(new_sockfd, buf, sizeof(buf) - 1, 0);
  if(recv_size < 0)
  {
    perror("recv");
    return 0;
  }
  else if(recv_size == 0)
  {
    close(new_sockfd);
    return 0;
  }
  else 
  {
    printf("[buf is] %s:\n", buf);
  }
  memset(buf, '\0', 1024);
  strcpy(buf, "i am server");
  send(new_sockfd, buf, strlen(buf), 0);
  close(sockfd);
  return 0;
}

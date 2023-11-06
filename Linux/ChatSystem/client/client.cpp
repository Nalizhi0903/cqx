#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

int main() 
{
  //创建套接字
  //发起连接
  //收发数据
  //关闭套接字
  int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(sockfd < 0)
  {
    perror("sockfd");
    return 0;
  }
  struct sockaddr_in svr_addr;
  svr_addr.sin_family = AF_INET;
  svr_addr.sin_port = htons(7878);
  svr_addr.sin_addr.s_addr = inet_addr("192.168.163.132");
  int ret = connect(sockfd, (struct sockaddr*)&svr_addr, sizeof(svr_addr));
  if(ret < 0)
  {
    perror("connect");
    return 0;
  }
  while(1)
  {
    char buf[1024] = {0};
    std::cout << "please enter your msg:  ";
    fflush(stdout);
    std::cin >> buf;
    send(sockfd, buf, strlen(buf), 0);
    memset(buf, '\0', 1024);
    ssize_t recv_size = recv(sockfd, buf, sizeof(buf) - 1, 0);
    if(recv_size < 0)
    {
      perror("recv");
      return 0;
    }
    else if(recv_size == 0)
    {
      printf("close\n");
      close(sockfd);
      return 0;
    }
    else 
    {
      printf("[buf is]: %s\n", buf); 
    }
  }
  close(sockfd);
  return 0;
}

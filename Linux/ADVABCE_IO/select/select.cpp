#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
using namespace std;
int main()
{
  //验证select返回后，是否会从事件集和当中去掉未就绪的文件描述符
  //1.创建tcp套接字
  //2.让select监控0号文件描述符和tcp套接字
  //3.让0号文件描述符就绪，select返回
  //4.判断返回的的事件集和
  
  int sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(sockfd < 0)
  {
    perror("socket");
    return 0;
  }
  
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(38989);
  addr.sin_addr.s_addr = inet_addr("0.0.0.0");
  int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
  if(ret < 0)
  {
    perror("bind");
    return 0;
  }
  listen(sockfd, 5);
  
  fd_set* readfds = new fd_set;
  //清空事件集和
  FD_ZERO(readfds);
  //将事件集和0，sockfd位设置为1
  FD_SET(0, readfds);
  FD_SET(sockfd, readfds);

  //阻塞循环监听0号描述符和tcp套接字
  ret = select(sockfd + 1, readfds, NULL, NULL, NULL);
  cout << ret << endl;
  char buf[1024] = {0};
  //说明有描述符就绪了
  read(0, buf, sizeof(buf) -1);
  printf("read buf: %s\n", buf);
  //selct返回后会把集合中未就绪的文件描述符去除调
  cout << FD_ISSET(sockfd, readfds) << endl;
  cout << FD_ISSET(0, readfds) << endl;
  return 0;
}

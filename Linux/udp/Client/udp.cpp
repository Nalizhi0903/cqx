#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/udp.h>
#include <unistd.h>
#include <string.h>

int main()
{
  //1.创建套接字
  //2.绑定地址信息
  //3.发送信息
  //4.接收信息
  //5.关闭套接字
  int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(sockfd < 0)
  {
    perror("socket");
    return 0;
  }
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(38989);
  addr.sin_addr.s_addr = inet_addr("192.168.163.132");
  
  while(1)
  {
    char buf[1024] = {0};
    printf("[please enter your msg]");
    fflush(stdout);
    std::cin >> buf;
    sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&addr, sizeof(addr)); 

    memset(buf, '\0', 1024);
    recvfrom(sockfd, buf, sizeof(buf) - 1, 0, NULL, NULL);
    printf("[sever say]:%s\n", buf);
  }
  
  return 0;
}

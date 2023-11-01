#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>//IPPROTO_UDP
#include <netinet/in.h>//IPPROTO_UDP
class UDPServer
{
  public:
    UDPServer()
    {

    }
    ~UDPServer()
    {

    }
  private:  
    int _sockfd;
};

int main()
{
  //1.创建套接字
  //2.绑定地址信息
  //3.接收信息
  //4.发送信息
  //5.关闭套接字
  
  int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  if(sockfd < 0)
  {
    perror("socket");
    return 0;
  }
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;//基于ipv4版本的ip协议进行通信
  addr.sin_port = htons(38989);//当前程序绑定的端口，字节序转换，主机字节序转换为网络字节序
  addr.sin_addr.s_addr = inet_addr("192.168.163.132");//将点分十进制的ip地址转换为无符号32位整数， 无符号32位的整数从主机字节序转换为网络字节序
  
  
  char buf[1024] = {0};
  memset(buf, '\0', 1024);
  strcpy(buf, "i am client");
  sendto(sockfd, buf, strlen(buf), 0, (struct sockaddr*)&addr, sizeof(addr));

  //接收服务端的数据 
  memset(buf, '\0', 1024);
  recvfrom(sockfd, buf, sizeof(buf) -1, 0, NULL, NULL);
  printf("buf is :%s\n", buf);
  close(sockfd);
  while(1)
  {
    sleep(1);
  }
  return 0;
}

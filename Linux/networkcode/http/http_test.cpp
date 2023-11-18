#include <iostream>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sstream>

int main()
{
  int fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); 
  struct sockaddr_in addr;
  addr.sin_family =AF_INET;
  addr.sin_port = htons(7878);
  addr.sin_addr.s_addr = inet_addr("192.168.163.132");
  int ret = bind(fd, (struct sockaddr*) &addr, sizeof(addr));
  if(ret < 0)
  {
    return 0;
  }
  ret = listen(fd, 5);
  if(ret < 0)
  {
    return 0;
  }
  int newsocketfd = accept(fd, NULL, NULL);
  if(newsocketfd < 0)
  {
    return 0;
  }
  while(1)
  {
    char buf[1024] = {0};
    ssize_t recv_size = recv(newsocketfd, buf, sizeof(buf)-1, 0);
    if(recv_size < 0)
    {
      continue;
    }
    else if(recv_size == 0)
    {
      close(fd);
      close(newsocketfd);
      return 0;
    }
    printf("buf is: \n%s\n", buf);
    //TO chrome
    //响应首行
    std::string msg = "hello";
    std::stringstream ss;
    //ss << "HTTP/1.1 200 OK\r\n";
    ss << "HTTP/1.1 302 OK\r\n";
    ss << "Content-Length:" << msg.size() << "\r\n";
    ss << "Content-Type: text/html\r\n";
    ss << "Set-Cookie：sessionid=17878\r\n";
    ss << "Location: https://www.baidu.com\r\n";
    ss << "\r\n";
    send(newsocketfd, ss.str().c_str(), ss.str().size(), 0);
    send(newsocketfd, msg.c_str(), msg.size(), 0);
  }
}

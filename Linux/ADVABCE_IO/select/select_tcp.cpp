#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
int nfds = 0;
int main()
{
  // 目标：单线程通过select处理tcp的代码
  
  // 1.创建tcp套接字，绑定
  int listen_sockfd = socket(AF_INET, SOCK_STREAM, 0);
  nfds = listen_sockfd + 1;
  if(listen_sockfd < 0)
  {
    perror("socket");
    return 0;
  }
  struct sockaddr_in addr;
  addr.sin_family = AF_INET;
  addr.sin_port = htons(38989);
  addr.sin_addr.s_addr = inet_addr("0.0.0.0");
  int ret = bind(listen_sockfd, (struct sockaddr*)&addr, sizeof(addr));
  if(ret < 0)
  {
    perror("bind");
    return 0;
  }
  // 2.监控(第一次监听只有侦听套接字)
  ret = listen(listen_sockfd, 5);
  if(ret < 0)
  {
    perror("listen");
    return 0;
  }
  fd_set readfds;
  FD_ZERO(&readfds);
  FD_SET(listen_sockfd, &readfds);
  while(1)
  {
    fd_set tmp = readfds;
    //nfds后续代码可以进行修改
    int ret = select(nfds, &tmp, NULL, NULL, NULL);
    if(ret < 0)
    {
      continue;
    }
    //区分是侦听套接字还是新连接套接字
    if(FD_ISSET(listen_sockfd, &tmp))
    {
      //侦听套接字的处理逻辑
      int new_sockfd = accept(listen_sockfd, NULL, NULL);
      if(ret < 0)
      {
        continue;
      }
      //1.添加newsockfd到readfds事件集合当中
      //2.更新nfds
      FD_SET(new_sockfd, &readfds);
      if(new_sockfd >= nfds)
      {
        nfds = new_sockfd + 1;
      }
    } 
    else 
    {
      //新连接套接字的处理方式
      //区分文件描述符
      printf("hehe\n");
      sleep(1);
      for(int i = 0; i < nfds; i++)
      {
        if(FD_ISSET(i, &tmp) && i !=listen_sockfd)
        {
          //收发数据
          char buf[1024] = {0};
          size_t r_size = recv(i, buf, sizeof(buf), 0);
          if(r_size < 0)
          {
            continue;
          }
          else if(r_size == 0)
          {
            //对端关闭连接
            //从事件集合去除，后续不监控 FD_CLR
            FD_CLR(i, &readfds); 
            //关闭套接字
            close(i);
          }
          else 
          {
            //正常接收数据
            printf("from sockfd num %d recv msg is %s\n", i, buf);
            memset(buf, '\0', 1024);
            snprintf(buf, sizeof(buf) - 1, "hello cilent %d, i am server", i);
            send(i, buf, strlen(buf), 0);
          }
        }
      }
    }
    
  }
  // 3.就绪,分情况处理
  //    第一次就绪：处理侦听套接字，accpet产生的新连接套接字放到select事件集和中进行监控
  //    第二次就绪：
  //        侦听套接字就绪
  //        新连接套接字就绪
  

  return 0;
}

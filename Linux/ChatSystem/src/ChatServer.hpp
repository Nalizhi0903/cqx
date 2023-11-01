#pragma once 
#include "MsgQueue.hpp"
#include "UserManager.hpp"
#include <unistd.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

/*
 *网络的搭建
 *  侦听套接字的创建
 *  新连接的接受
 *
 *业务处理
 * 线程当中展开业务的处理
 *
 * 线程的创建
 *
 * 接受队列的创建
 *
 * 发送队列的创建
 *
 * 创建监控文件描述符（epoll）
 * */
#define TCP_PORT 7878
#define THREAD_COUNT 4
class CharServer 
{
  public:
    CharServer():_tcp_listen_sockfd(-1), _tcp_port(TCP_PORT), _work_thread_count(THREAD_COUNT), _um(nullptr)
    {}
    ~CharServer()
    {
      if(_recv_que != NULL)
      {
        delete _recv_que;
      }
      if(_send_que != NULL)
      {
        delete _send_que;
      }
    }
  public:
    int InitChatServer(int tcp_port = TCP_PORT, int thread_count = THREAD_COUNT)
    {
      _tcp_port = tcp_port;
      _work_thread_count = thread_count;
      //1.初始化tcp：创建套接字， 绑定地址信息， 监听
      _tcp_listen_sockfd = socket(AF_INET, SOCK_STREAM, 0); 
      if(_tcp_listen_sockfd < 0)
      {
        return -1;
      }
      //端口复用
      int opt = 1;
      setsockopt(_tcp_listen_sockfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

      struct sockaddr_in addr;
      addr.sin_family = AF_INET;
      addr.sin_port = htons(_tcp_port);
      addr.sin_addr.s_addr = inet_addr("0.0.0.0");
      int ret = bind(_tcp_listen_sockfd, (struct sockaddr*)&addr, sizeof(addr));
      if(ret < 0)
      {
        return -2;
      }
      ret = listen(_tcp_listen_sockfd, 1024);
      if(ret < 0)
      {
        return -3;
      }
      //2.epoll的初始化
      _epoll_fd = epoll_create(5);
      if(_epoll_fd < 0)
      {
        return -4;
      }
      //3.两个队列的初始化
      _recv_que = new MsgQueue<string>();
      if(_recv_que == nullptr)
      {
        return -5;
      }
      _send_que = new MsgQueue<string>();
      if(_send_que == nullptr)
      {
        return -6;
      }
      //初始化用户管理模块
      _um = new UserManager();
      if(_um == nullptr)
      {
        return -7;
      }
      return 0;
    }

    int startChatSever()
    {
      //启动各类线程
      //1.接受线程
      pthread_t tid;
      int ret = pthread_create(&tid, NULL, recv_msg_start, NULL);
      if(ret < 0)
      {
        return -1;
      }
      //2.发送线程
      ret = pthread_create(&tid, NULL, send_msg_start, NULL);
      if(ret < 0)
      {
        return -2;
      }
      //3.工作线程
      int faile_start_count = 0;
      for(int i = 0; i < _work_thread_count; i++)
      {
        ret = pthread_create(&tid, NULL, deal_start, NULL);
        if(ret < 0)
        {
          faile_start_count++;
        }
      }
      if(_work_thread_count - faile_start_count <= 0)
      {
        return -2;
      }
      _work_thread_count -= faile_start_count;
      //4.循环接收新连接
      //  将接收回来的新连接套接字描述符放在epoll当中进行监控
      struct sockaddr_in cli_addr;
      socklen_t cli_addr_len = sizeof(cli_addr);

      while(1)
      {
        int newsockfd = accept(_tcp_listen_sockfd, (struct sockaddr*)&cli_addr, &cli_addr_len);
        if(newsockfd < 0)
        {
          continue;
        }
        cout << "have a new link from ip is" << inet_ntoa(cli_addr.sin_addr) << "port" << ntohs(cli_addr.sin_port) << endl;; 
        //接收成功
        struct epoll_event ee;
        //关心可读事件
        ee.events = EPOLLIN;
        ee.data.fd = newsockfd;
        epoll_ctl(_epoll_fd, EPOLL_CTL_ADD, newsockfd, &ee);
      }
      return 0;
    }

    static void* recv_msg_start(void* arg)
    {
      while(1)
      {
        //cout << "recv_msg_start" << endl;
        sleep(1);
      }
    }
    
    static void* send_msg_start(void* arg)
    {
      while(1)
      {
        //cout << "send_msg_start" << endl;
        sleep(1);
      }
    }

    static void* deal_start(void* arg)
    {
      while(1)
      {
        //cout << "deal_start" << endl;
        sleep(1);
      }
    }
  private:
    //监听套接字
    int _tcp_listen_sockfd;
    //tcp的端口
    int _tcp_port;
    //工作线程个数
    int _work_thread_count;
    //接受队列
    MsgQueue<string>* _recv_que;
    //发送队列
    MsgQueue<string>* _send_que;
    //epoll的操作句柄
    int _epoll_fd;
    //用户管理模块
    UserManager* _um;
};

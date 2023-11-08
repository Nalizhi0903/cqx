#pragma once 
#include "MsgQueue.hpp"
#include "UserManager.hpp"
#include "ChatMsg.hpp"
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
class ChatServer 
{
  public:
    ChatServer():_tcp_listen_sockfd(-1), _tcp_port(TCP_PORT), _work_thread_count(THREAD_COUNT), _um(nullptr)
    {
    }
    ~ChatServer()
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
      _recv_que = new MsgQueue<ChatMsg>();
      if(_recv_que == nullptr)
      {
        return -5;
      }
      _send_que = new MsgQueue<ChatMsg>();
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
      if(_um->InitUserManager() == false)
      {
        return -8;
      }
      return 0;
    }

    int startChatSever()
    {
      //启动各类线程
      //1.接受线程
      pthread_t tid;
      int ret = pthread_create(&tid, NULL, recv_msg_start, (void*)this);
      if(ret < 0)
      {
        return -1;
      }
      //2.发送线程
      ret = pthread_create(&tid, NULL, send_msg_start, (void*)this);
      if(ret < 0)
      {
        return -2;
      }
      //3.工作线程
      int faile_start_count = 0;
      for(int i = 0; i < _work_thread_count; i++)
      {
        ret = pthread_create(&tid, NULL, deal_start, (void*)this);
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
      pthread_detach(pthread_self());
      /*
       *  1.调用epoll_wait获取就绪的文件描述符
       *  2.调用recv获取就绪的文件描述符对应的数据
       *  3.将获取的内容插入到接收队列中
       */ 
      ChatServer* cs = (ChatServer*)arg;
      while(1)
      {
        struct epoll_event arr[10];//arr：存放就绪的事件结构的数组
        int ret = epoll_wait(cs->_epoll_fd, arr, sizeof(arr)/sizeof(arr[0]), -1);//-1阻塞监控
        if(ret < 0)
        {
          continue;
        }
        else 
        {
          //epoll监控的文件描述符的类型
          for(int i = 0; i < ret; i++)
          {
            char buf[1024] = {0};
            ssize_t r_size = recv(arr[i].data.fd, buf, sizeof(buf) - 1, 0);
            if(r_size < 0)
            {
              cout << "recv data failed,sockfd is " << arr[i].data.fd << endl;
              continue;
            }
            else if(r_size == 0)
            {  
              //对端关闭连接
              // 1.不再监控该文件描述符
              // 2.关闭这个文件描述符
              // 3.业务场景
              epoll_ctl(cs->_epoll_fd, EPOLL_CTL_DEL, arr[i].data.fd, NULL);
              close(arr[i].data.fd);
            }
            else 
            {
              cout << "recv_msg_start recv msg: " << buf << " from newsockfd is " << arr[i].data.fd << endl;
              ChatMsg cm;
              cm.PraseChatMsg(buf);
              cm._sockfd = arr[i].data.fd;
              cs->_recv_que->Push(cm);
            }
          }
        }
        sleep(1);
      }
    }
    
    static void* send_msg_start(void* arg)
    {
      pthread_detach(pthread_self());
      ChatServer* cs = (ChatServer*)arg;
      while(1)
      {
        ChatMsg cm;
        cs->_send_que->Pop(&cm); 
        string msg;
        cm.GetMsg(&msg);
        send(cm._sockfd, msg.c_str(), msg.size(), 0);
      }
    }

    static void* deal_start(void* arg)
    {
      pthread_detach(pthread_self());
      ChatServer* cs = (ChatServer*)arg;
      while(1)
      {
        //1.从队列中获取消息类型为ChatMsg的消息
        ChatMsg cm;
        cs->_recv_que->Pop(&cm);
        //2.根据不同的消息类型，分清处理
        int msg_type = cm._msg_type;
        switch(msg_type)
        {
          case Register:
            cs->DealRegister(cm);
            break;
          case Login:
            cs->DealLogin(cm);
            break;
        }
      }
    }
    
    void DealRegister(ChatMsg& cm)
    {
      //1.get register info
      std::string nickname = cm.GetValue("nickname");
      std::string school = cm.GetValue("school");
      std::string telnum = cm.GetValue("telnum");
      std::string passwd = cm.GetValue("passwd");
      int user_id = -1;
      //2.call UserManager register function
      int ret = _um->DealRegister(nickname, school, telnum, passwd, &user_id);
      //3.回复响应
      cm.Clear();
      cm._msg_type = Register_Resp;
      if(ret < 0)
      {
        cm._reply_statu = REGISTER_FAILED;
      }
      else
      {
        cm._reply_statu = REGISTER_SUCCESS;
      }
      cm._user_id = user_id;
      _send_que->Push(cm);
    }

    void DealLogin(ChatMsg& cm)
    {
      //1.获取登入信息
      std::string telnum = cm.GetValue("telnum");
      std::string passwd = cm.GetValue("passwd");
      //2.调用用户管理模块的登入函数
      int ret = _um->DealLogin(telnum, passwd, cm._sockfd);
      //3.回复应答
      cm.Clear();
      cm._msg_type = Login_Resp;
      if(ret < 0)
      {
        cm._reply_statu = LOGIN_FAILED;  
      }
      else 
      {
        cm._reply_statu = LOGIN_SUCCESS;
      }
      cm._user_id = ret;

      _send_que->Push(cm);
    }

  private:
    //监听套接字
    int _tcp_listen_sockfd;
    //tcp的端口
    int _tcp_port;
    //工作线程个数
    int _work_thread_count;
    //接受队列
    MsgQueue<ChatMsg>* _recv_que;
    //发送队列
    MsgQueue<ChatMsg>* _send_que;
    //epoll的操作句柄
    int _epoll_fd;
    //用户管理模块
    UserManager* _um;
};

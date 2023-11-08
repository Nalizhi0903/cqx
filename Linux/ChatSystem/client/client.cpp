#include "ChatMsg.hpp"
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
<<<<<<< HEAD
  //while(1)
  {
    ChatMsg cm;
    /*注册
    cm._msg_type = Register;
    cm._json_msg["nickname"] = "aa";
    cm._json_msg["school"] = "bite";
    cm._json_msg["telnum"] = "1963716321";
    cm._json_msg["passwd"] = "717273";
    */
    /*登入*/
    cm._msg_type = Login;
    cm._json_msg["telnum"] = "13672678168";
    cm._json_msg["passwd"] = "cqxctz123";
=======
  while(1)
  {
    ChatMsg cm;
    cm._msg_type = Register;
    cm._json_msg["nickname"] = "cqx";
>>>>>>> ae694aced12244a1ab85a9458c869ce47fe74f91
    string msg;
    cm.GetMsg(&msg);
    send(sockfd, msg.c_str(), msg.size(), 0);
    char buf[1024] = {0};
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
      ChatMsg rcvms;
      rcvms.PraseChatMsg(buf);
<<<<<<< HEAD
      if(rcvms._reply_statu == LOGIN_SUCCESS)
      {
        cout << "登入成功" << endl;
      }
      else 
      {
        cout << "登入失败" << endl;
      }
      cout << buf << endl;
=======
      cout << buf << endl;
      //cout << rcvms._msg_type << endl;
      //cout << rcvms._reply_statu<< endl;
      //cout << rcvms._user_id<< endl;
>>>>>>> ae694aced12244a1ab85a9458c869ce47fe74f91
    }
  }
  close(sockfd);
  return 0;
}

#pragma once
#include <Windows.h>
#include <stdio.h>
#include <WinSock2.h>
#include <string>
#include <mutex>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)
/*
*	1.初始化的时候连接服务端
*	2.提供发送数据和接受数据的接口
*/
class TcpSvr
{
private:
	TcpSvr();
	TcpSvr(const TcpSvr& ts);
public:
	~TcpSvr();
public:
	int ConnectToSvr();
	int Send(std:: string& msg);
	int Recv(std::string* msg);
	static TcpSvr* GetInstance();
private:
	SOCKET _sockfd;
	/*全局唯一的实例化对象*/
	static TcpSvr* _instance;
};


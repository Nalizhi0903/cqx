#pragma once
#include <Windows.h>
#include <stdio.h>
#include <WinSock2.h>
#include <string>
#include <mutex>
#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)
/*
*	1.��ʼ����ʱ�����ӷ����
*	2.�ṩ�������ݺͽ������ݵĽӿ�
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
	/*ȫ��Ψһ��ʵ��������*/
	static TcpSvr* _instance;
};


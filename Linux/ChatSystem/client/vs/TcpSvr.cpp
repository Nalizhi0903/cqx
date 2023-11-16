#include "pch.h"
#include "TcpSvr.h"

std::mutex g_mt;
TcpSvr* TcpSvr::_instance = nullptr;

TcpSvr* TcpSvr::GetInstance()
{
	g_mt.lock();
	if (_instance == nullptr)
	{
		_instance = new TcpSvr();
		_instance->ConnectToSvr();
	}
	g_mt.unlock();
	return _instance;
}

TcpSvr::TcpSvr()
{

}

TcpSvr::~TcpSvr()
{

}

int TcpSvr::ConnectToSvr()
{
	/*1.�����׽��ֿ�*/
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	//Winsock��汾�����ֽڴ������汾�����ֽڴ����汾
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
	{
		return -1;
	}
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2)
	{
		//��ֹ��winsock���ʹ��
		WSACleanup();
		return -1;
	}
	/*2.�����׽���  */
	_sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (_sockfd == INVALID_SOCKET)
	{
		WSACleanup();
		return -1;
	}
	/*3.���ӷ����	*/
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("192.168.163.132");

	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(7878);
	int ret = connect(_sockfd, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	if (ret < 0)
	{
		closesocket(_sockfd);
		WSACleanup();
		return -1;
	}
	return 0;
}

int TcpSvr::Send(std::string& msg)
{
	return send(_sockfd, msg.c_str(), msg.size(), 0);
}

int TcpSvr::Recv(std::string* msg)
{
	char buf[1024] = { 0 };
	int r_s = recv(_sockfd, buf, sizeof(buf) - 1, 0);
	if (r_s < 0)
	{
		return r_s;
	}
	else if (r_s == 0)
	{
		//1.��������
		//2.�ر�Ӧ��
		exit(1);
	}
	else
	{
		*msg = buf;
	}
	return r_s;
}
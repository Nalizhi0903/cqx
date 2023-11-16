#pragma once
#include <vector>
#include <string>
#include <queue>
#include <mutex>
/*�����Ϣ���п��԰�����Ϣ���ʹ����Ϣ�� Ҳ���԰�����Ϣ���ͻ�ȡ��Ϣ
	��Ϣ��ChatMsg
*/
class MsgQueue
{
public:
	static MsgQueue* GetInstance();
	void Push(int msg_type, const std::string& msg);
	void Pop(int msg_type, std::string* msg);
private:
	std::vector <std::queue<std::string>> _v_msg;
	MsgQueue();
	MsgQueue(const MsgQueue& m);
	/*�������Ψһ��ʵ��������*/
	static MsgQueue* _instance;
};


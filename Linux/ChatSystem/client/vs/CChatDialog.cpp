// CChatDialog.cpp: 实现文件
//

#include "pch.h"
#include "ChatSystem88.h"
#include "CChatDialog.h"
#include "afxdialogex.h"
#include "ChatMsg.h"
#include "TcpSvr.h"
#include "MsgQueue.h"


// CChatDialog 对话框

IMPLEMENT_DYNAMIC(CChatDialog, CDialogEx)

CChatDialog::CChatDialog(int userid, CWnd* pParent /*=nullptr*/)
	: _user_id(userid), CDialogEx(IDD_CHATDIALOG, pParent)
	, friend_list(_T(""))
	, _input(_T(""))
{

}

CChatDialog::~CChatDialog()
{
}

void CChatDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_LBString(pDX, IDC_FRIEND_LIST, friend_list);
	DDX_Control(pDX, IDC_FRIEND_LIST, user_list);
	DDX_Text(pDX, IDC_INPUT, _input);
	DDX_Control(pDX, IDC_OUTPUT, _output);
}


BEGIN_MESSAGE_MAP(CChatDialog, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CChatDialog::OnBnClickedButton1)
	ON_LBN_SELCHANGE(IDC_FRIEND_LIST, &CChatDialog::OnLbnSelchangeFriendList)
	ON_LBN_SELCHANGE(IDC_OUTPUT, &CChatDialog::OnLbnSelchangeOutput)
	ON_EN_CHANGE(IDC_INPUT, &CChatDialog::OnEnChangeInput)
	ON_BN_CLICKED(IDC_COMMIT, &CChatDialog::OnBnClickedCommit)
END_MESSAGE_MAP()


// CChatDialog 消息处理程序


void CChatDialog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
}

void CChatDialog::ReFreshUserList()
{
	//清空
	for (int i = 0; i < user_list.GetCount(); i++)
	{
		user_list.DeleteString(i);
	}
	//展示
	for (int i = 0; i < (int)_friend_vec.size(); i++)
	{
		std::string nickname = _friend_vec[i].nickname;
		if (_friend_vec[i].msg_count > 0)
		{
			nickname += " : ";
			nickname += std::to_string(_friend_vec[i].msg_count);
		}
		user_list.InsertString(user_list.GetCount(), nickname.c_str());
	}
}

void DealMsg(CChatDialog* cc)
{
	//1.获取消息队列
	MsgQueue* mq = MsgQueue::GetInstance();
	if (mq == nullptr)
	{
		MessageBox(cc->m_hWnd ,TEXT("内部有错，请联系开发人员"), "error", MB_OK);
		return;
	}
	
	//2.循环获取消息
	while (1)
	{
		std::string msg;
		mq->Pop(PushMsg, &msg);
		//3.解析消息
		ChatMsg cm;
		cm.PraseChatMsg(msg);
		std::string peer_nickname = cm._json_msg["peer_nickname"].asString();
		std::string peer_school = cm._json_msg["peer_school"].asString();
		std::string peer_msg = cm._json_msg["peer_msg"].asString();
		int peer_userid = cm._json_msg["peer_userid"].asInt();
		//4.展示在聊天框
		for (int i = 0; i < cc->_friend_vec.size(); i++)
		{
			if (peer_userid == cc->_friend_vec[i].user_id)
			{
				std::string tmp = peer_nickname + "-" + peer_school + ": " + peer_msg;
				//找到好友，并判断是否和好友正在聊天
				if (peer_userid == cc->_send_id)
				{
					//是，则直接展示	
					cc->_output.InsertString(cc->_output.GetCount(), tmp.c_str());
				}
				else
				{
					//否，userlist当中对应的好友添加消息个数
					cc->_friend_vec[i].msg_count++;
				}
				cc->_friend_vec[i]._history_msg.push_back(tmp);
			}
		}
		//刷新好友列表
		cc->ReFreshUserList();
	}
}

BOOL CChatDialog::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	MessageBox(TEXT("初始化聊天界面..."), MB_OK);
	// TODO:  在此添加额外的初始化
	
	//创建线程，接受其他客户端发送的消息
	std::thread recv_msg(DealMsg, this);
	recv_msg.detach();
	//组织登入信息
	ChatMsg cm;
	cm._msg_type = GetFriend;
	cm._user_id = _user_id;
	std::string msg;
	cm.GetMsg(&msg);
	TcpSvr* ts = TcpSvr::GetInstance();
	ts->Send(msg);
	//获取消息队列实例化指针
	MsgQueue* mq = MsgQueue::GetInstance();
	if (mq == nullptr)
	{
		MessageBox(TEXT("内部错误，请联系开发人员"));
		return false;
	}
	//从队列中获得消息
	msg.clear();
	mq->Pop(GetFriend_Resp, &msg);
	//解析消息
	cm.Clear();
	cm.PraseChatMsg(msg);
	if (cm._reply_statu == GETFRIEND_SUCCESS)
	{
		for (int i = 0; i < (int)cm._json_msg.size(); i++)
		{
			struct UserInfo ui;
			ui.nickname = cm._json_msg[i]["nickname"].asString();
			ui.school = cm._json_msg[i]["school"].asString();
			ui.user_id = cm._json_msg[i]["userid"].asInt();

			_friend_vec.push_back(ui);
		}
		//刷新好友信息到userlist当中
		for (int i = 0; i < (int)_friend_vec.size(); i++)
		{
			std::string nickname = _friend_vec[i].nickname;
			if (_friend_vec[i].msg_count > 0)
			{
				nickname += " : ";
				nickname += std::to_string(_friend_vec[i].msg_count);
			}
			user_list.InsertString(user_list.GetCount(), nickname.c_str());
			if (i == 0)
			{
				_send_id = _friend_vec[i].user_id;
			}
		}
	}
	else
	{
		MessageBox(TEXT("内部错误，请联系开发人员"), MB_OK);
		return false;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

//点击userlist调用的函数

void CChatDialog::OnLbnSelchangeFriendList()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取文本框的内容
	CString str;
	user_list.GetText(user_list.GetCurSel(), str);
	//判断是哪个好友，更改发送id
	for (int i = 0; i < _friend_vec.size(); i++)
	{
		if (strstr(str, _friend_vec[i].nickname.c_str()))
		{
			_send_id = _friend_vec[i].user_id;
		}
	}
	//清空聊天框
	for (int i = 0; _output.GetCount(); i++)
	{
		_output.DeleteString(i);
	}
	//展示被点击好友的历史聊天记录
	for (int i = 0; i < _friend_vec.size(); i++)
	{
		if (_send_id == _friend_vec[i].user_id)
		{
			for (int j = 0; j < _friend_vec[i]._history_msg.size(); i++)
			{
				_output.InsertString(_output.GetCount(), _friend_vec[i]._history_msg[j].c_str());
			}
			//清空未读消息
			_friend_vec[i].msg_count = 0;
			break;
		}
	}
	//刷新Userlist
	ReFreshUserList();
}

//展示消息
void CChatDialog::OnLbnSelchangeOutput()
{
	// TODO: 在此添加控件通知处理程序代码
}

//发送数据
void CChatDialog::OnEnChangeInput()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

//发送按钮
void CChatDialog::OnBnClickedCommit()
{
	// TODO: 在此添加控件通知处理程序代码
	//1.获取发送框的内容
	UpdateData(TRUE);
	if (_input.IsEmpty())
	{
		MessageBox(TEXT("发送内容不能为空"));
		return;
	}
	//2.组织发送消息，序列化消息
	ChatMsg cm;
	cm._msg_type = chat_msg_type::SendMsg;
	cm._user_id = _user_id;

	cm._json_msg["recvid"] = _send_id;
	cm._json_msg["msg"] = _input.GetString();
	//3.获取tcp实例化指针
	TcpSvr* ts = TcpSvr::GetInstance();
	if (ts == nullptr)
	{
		MessageBox(TEXT("内部有错，请联系开发人员"));
		return;
	}
	std::string msg;
	cm.GetMsg(&msg);
	//4.发送消息
	ts->Send(msg);
	//5.接受应答，判断消息是否成功
	MsgQueue* mq = MsgQueue::GetInstance();
	msg.clear();
	mq->Pop(SendMsg_Resp, &msg);
	cm.Clear();
	cm.PraseChatMsg(msg);	
	std::string send_status = "";
	if (cm._reply_statu == SENDMSG_FAILED)
	{
		send_status += "(send failed)";
	}
	else
	{
		send_status += "(send successed)";
	}
	//6.将消息添加到历史消息当中， 并且展示到输出框
	for (int i = 0; i < _friend_vec.size(); i++)
	{
		if (_send_id == _friend_vec[i].user_id)
		{
			std::string tmp = "我：";
			tmp += _input.GetString();
			tmp += send_status;
			_friend_vec[i]._history_msg.push_back(tmp);
			_output.InsertString(_output.GetCount(), tmp.c_str());
		}
	}
	//7.清空发送框
	_input.Empty();
}

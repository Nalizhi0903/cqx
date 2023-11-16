// AddFriend.cpp: 实现文件
//

#include "pch.h"
#include "ChatSystem88.h"
#include "AddFriend.h"
#include "afxdialogex.h"

#include "ChatMsg.h"
#include "TcpSvr.h"
#include "MsgQueue.h"


// AddFriend 对话框

IMPLEMENT_DYNAMIC(AddFriend, CDialogEx)

AddFriend::AddFriend(int user_id, CWnd* pParent /*=nullptr*/)
	: _user_id(user_id)
	, CDialogEx(IDD_ADDFRIENDDIALOG, pParent)
	, _tel_num(_T(""))
{

}

AddFriend::~AddFriend()
{
}

void AddFriend::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TELNUM, _tel_num);
}


BEGIN_MESSAGE_MAP(AddFriend, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &AddFriend::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_ADDFRIENDBUTTON, &AddFriend::OnBnClickedAddfriendbutton)
	ON_EN_CHANGE(IDC_TELNUM, &AddFriend::OnEnChangeTelnum)
END_MESSAGE_MAP()


// AddFriend 消息处理程序


void AddFriend::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void AddFriend::OnBnClickedAddfriendbutton()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取发送框的内容
	UpdateData(true);
	std::string str;
	if (_tel_num.IsEmpty() == true)
	{
		MessageBox(TEXT("输入不能为空"));
		return;
	}
	//2.组织发送消息，序列化消息
	ChatMsg cm;
	cm._msg_type = chat_msg_type::AddFriend;
	cm._user_id = _user_id;

	cm._json_msg["friendtelnum"] = _tel_num.GetString();
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
}


void AddFriend::OnEnChangeTelnum()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

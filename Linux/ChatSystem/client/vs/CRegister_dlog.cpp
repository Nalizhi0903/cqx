// CRegister_dlog.cpp: 实现文件
//

#include "pch.h"
#include "ChatSystem88.h"
#include "CRegister_dlog.h"
#include "afxdialogex.h"
#include "ChatMsg.h"
#include "TcpSvr.h"
#include "MsgQueue.h"

// CRegister_dlog 对话框

IMPLEMENT_DYNAMIC(CRegister_dlog, CDialogEx)

CRegister_dlog::CRegister_dlog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_REGISTER, pParent)
	, _nickname(_T(""))
	, _school(_T(""))
	, _telnum(_T(""))
	, _passwd(_T(""))
{

}

CRegister_dlog::~CRegister_dlog()
{
}

void CRegister_dlog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_REGISTER_NAME, _nickname);
	DDX_Text(pDX, IDC_SCHOOL, _school);
	DDX_Text(pDX, IDC_TELNUM, _telnum);
	DDX_Text(pDX, IDC_PASSWD, _passwd);
}


BEGIN_MESSAGE_MAP(CRegister_dlog, CDialogEx)
	ON_EN_CHANGE(IDC_SCHOOL, &CRegister_dlog::OnEnChangeSchool)
	ON_BN_CLICKED(IDC_BUTTON1, &CRegister_dlog::OnBnClickedButton1)
END_MESSAGE_MAP()


// CRegister_dlog 消息处理程序


void CRegister_dlog::OnEnChangeSchool()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CRegister_dlog::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

/*当用户点击按钮后，默认调用下面函数*/

void CRegister_dlog::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	/*1.获取edit的内容，并判断*/	
	//MFC获取EDIT控件内容的时候要调用UpdateData函数获取最新值
	UpdateData(TRUE);
	if (_nickname.IsEmpty() || _school.IsEmpty() || _telnum.IsEmpty() || _passwd.IsEmpty())
	{
		//在界面当中弹框
		MessageBox(TEXT("输入不能为空"));//TEXT MFC定义的宏
		return;
	}
	/*2.组织注册消息（ChatMsg）*/
	ChatMsg cm;
	cm._msg_type = chat_msg_type::Register;
	cm._json_msg["nickname"] = _nickname.GetString();
	cm._json_msg["school"] = _school.GetString();
	cm._json_msg["telnum"] = _telnum.GetString();
	cm._json_msg["passwd"] = _passwd.GetString();
	std::string msg;
	cm.GetMsg(&msg);
	/*3.获取TcpSvr实例化指针*/
	TcpSvr* ts = TcpSvr::GetInstance();
	if (ts == nullptr)
	{
		MessageBox(TEXT("获取服务器连接失败，请联系开发人员"));//TEXT MFC定义的宏
		return;
	}
	/*4.发送消息*/
	ts->Send(msg);
	/*5.获取消息队列的实例化指针*/
	MsgQueue* mq = MsgQueue::GetInstance();
	if (mq == nullptr)
	{
		MessageBox(TEXT("消息错误，请联系开发人员"));
		return;
	}
	/*6.获取注册应答*/
	msg.clear();
	mq->Pop(Register_Resp, &msg);
	cm.Clear();
	cm.PraseChatMsg(msg);
	/*7.判断注册应答当中的状态*/
	if (cm._reply_statu == REGISTER_SUCCESS)
	{
		//提醒用户注册成功，关闭页面
		MessageBox(TEXT("注册成功"));
		//推出当前界面
		CDialog::OnCancel();
	}
	else
	{
		//提醒用户注册失败
		MessageBox(TEXT("注册失败"));
	}
}

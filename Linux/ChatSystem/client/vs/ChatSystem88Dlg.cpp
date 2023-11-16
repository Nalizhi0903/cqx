
// ChatSystem88Dlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "ChatSystem88.h"
#include "ChatSystem88Dlg.h"
#include "CChatDialog.h"
#include "afxdialogex.h"
#include "CRegister_dlog.h"
#include "MsgQueue.h"
#include "ChatMsg.h"
#include "TcpSvr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CChatSystem88Dlg 对话框



CChatSystem88Dlg::CChatSystem88Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATSYSTEM88_DIALOG, pParent)
	, _telnum(_T(""))
	, _passwd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatSystem88Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TELNUM, _telnum);
	DDX_Text(pDX, IDC_PASSWD, _passwd);
}

BEGIN_MESSAGE_MAP(CChatSystem88Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CChatSystem88Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON5, &CChatSystem88Dlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON4, &CChatSystem88Dlg::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_TELNUM, &CChatSystem88Dlg::OnEnChangeTelnum)
END_MESSAGE_MAP()


// CChatSystem88Dlg 消息处理程序

BOOL CChatSystem88Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CChatSystem88Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatSystem88Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChatSystem88Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatSystem88Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CChatSystem88Dlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CChatSystem88Dlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

/*界面*/
//登入按钮
void CChatSystem88Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	//1.获取登入信息
	UpdateData(TRUE);
	if (_telnum.IsEmpty() || _passwd.IsEmpty())
	{
		MessageBox(TEXT("输入内容不能为空"));
		return;
	}
	//2.组织登入信息
	ChatMsg cm;
	cm._msg_type = Login;
	cm._json_msg["telnum"] = _telnum.GetString();
	cm._json_msg["passwd"] = _passwd.GetString();
	std::string msg;
	cm.GetMsg(&msg);
	//3.获取tcp的实例化指针
	TcpSvr* ts = TcpSvr::GetInstance();
	if (ts == nullptr)
	{
		MessageBox(TEXT("内部错误，请联系开发人员"));
	}
	//4.发送登入信息
	ts->Send(msg);
	//5.获取消息队列
	MsgQueue* mq = MsgQueue::GetInstance();
	if (mq == nullptr)
	{
		MessageBox(TEXT("内部错误，请联系开发人员"));
		return;
	}
	//6.从消息队列中获取登入应答
	msg.clear();
	mq->Pop(Login_Resp, &msg);
	//7.通过登入应答判断是否登入成功
	cm.Clear();
	cm.PraseChatMsg(msg);
	if (cm._reply_statu == LOGIN_SUCCESS)
	{
		MessageBox(TEXT("登入成功"));
		//关闭当前界面
		CDialog::OnCancel();
		//跳转到聊天界面
		CChatDialog cd(cm._user_id);
		cd.DoModal();
	}
	else
	{
		MessageBox(TEXT("登入失败，请检查账号和密码"));
	}
}

//注册按钮
void CChatSystem88Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	CRegister_dlog crd;
	crd.DoModal();
}


void CChatSystem88Dlg::OnEnChangeTelnum()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

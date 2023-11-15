#pragma once
#include <string>
#include <vector>

struct UserInfo
{
	std::string nickname;
	std::string school;
	int user_id;

	//消息历史
	std::vector<std::string> _history_msg;
	//未读消息个数
	int msg_count;
};

// CChatDialog 对话框

class CChatDialog : public CDialogEx
{
	DECLARE_DYNAMIC(CChatDialog)

public:
	CChatDialog(int userid, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CChatDialog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	//客户端的id
	int _user_id;
	//当前发送消息的好友id
	int _send_id;
	afx_msg void OnBnClickedButton1();
	virtual BOOL OnInitDialog();
	CString friend_list;
	afx_msg void OnLbnSelchangeFriendList();
	CListBox user_list;
	std::vector<struct UserInfo> _friend_vec;
	CString _input;
	CListBox _output;
	afx_msg void OnLbnSelchangeOutput();
	afx_msg void OnEnChangeInput();
	afx_msg void OnBnClickedCommit();
	void ReFreshUserList();
};

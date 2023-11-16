#pragma once


// AddFriend 对话框

class AddFriend : public CDialogEx
{ 
	DECLARE_DYNAMIC(AddFriend)

public:
	AddFriend(int user_id, CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AddFriend();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADDFRIENDDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedAddfriendbutton();
	afx_msg void OnEnChangeTelnum();
	CString _tel_num;
	int _user_id;
};

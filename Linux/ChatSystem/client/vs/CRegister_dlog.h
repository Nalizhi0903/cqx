#pragma once


// CRegister_dlog 对话框

class CRegister_dlog : public CDialogEx
{
	DECLARE_DYNAMIC(CRegister_dlog)

public:
	CRegister_dlog(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRegister_dlog();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_REGISTER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString _nickname;
	CString _school;
	CString _telnum;
	CString _passwd;
	afx_msg void OnEnChangeEdit6();
	afx_msg void OnEnChangeSchool();
	afx_msg void OnBnClickedButton1();
};

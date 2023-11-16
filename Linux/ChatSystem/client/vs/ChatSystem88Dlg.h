
// ChatSystem88Dlg.h: 头文件
//

#pragma once


// CChatSystem88Dlg 对话框
class CChatSystem88Dlg : public CDialogEx
{
// 构造
public:
	CChatSystem88Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATSYSTEM88_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit3();
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton4();
	CString _telnum;
	CString _passwd;
	afx_msg void OnEnChangeTelnum();
};

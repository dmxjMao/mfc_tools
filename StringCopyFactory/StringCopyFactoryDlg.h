
// StringCopyFactoryDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "MyFmtSplitBtn.h"

//struct CMyFmtSplitBtn::FmtContext;

// CStringCopyFactoryDlg dialog
class CStringCopyFactoryDlg : public CDialogEx
{
// Construction
public:
	CStringCopyFactoryDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STRINGCOPYFACTORY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	CString												m_templateStr;//模板字符串
	std::vector<CMyFmtSplitBtn::FmtContext>				m_vecFmt;//新匹配的格式
	std::vector<CMyFmtSplitBtn::FmtContext>				m_vecExistFmt;//已创建的格式

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//模板字符串变化
	afx_msg void OnChangeEdit1();
	DECLARE_MESSAGE_MAP()
	CEdit m_edit1;
	virtual void OnOK();
private:
	//读取按钮菜单
	void doReadMenu();
	//赋值行号
	void doSetFmtLineno();
	//动态创建格式控制按钮
	void doCreateFmtButton();
	//判断是否需要创建格式控制按钮
	bool doJudgeFmtChange();

public:
};

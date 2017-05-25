
// StringCopyFactoryDlg.h : header file
//

#pragma once
#include "afxwin.h"

//enum FmtType : int;//前置声明

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
	//格式枚举
	enum FmtType {
		INTEGER,
		FLOAT
	};
	std::vector<FmtType>				m_vecFmt;//格式控制符
	CString								m_templateStr;//模板字符串

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	CEdit m_edit1;
	virtual void OnOK();
public:
	afx_msg void OnChangeEdit1();


};

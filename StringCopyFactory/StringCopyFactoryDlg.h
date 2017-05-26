
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
	//map,multimap会给你排序！
	//std::map<FmtType, std::shared_ptr<CSplitButton>>	m_mapExistFmt;//已创建的格式控制按钮
	std::vector<std::tuple<FmtType, std::shared_ptr<CSplitButton>>> m_vecExistFmt;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnChangeEdit1();
	DECLARE_MESSAGE_MAP()
	CEdit m_edit1;
	virtual void OnOK();
private:
	//动态创建格式控制按钮
	void doCreateFmtButton();
};

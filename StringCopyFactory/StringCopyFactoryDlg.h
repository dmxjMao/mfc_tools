
// StringCopyFactoryDlg.h : header file
//

#pragma once
#include "afxwin.h"

//enum FmtType : int;//ǰ������

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
	//��ʽö��
	enum FmtType {
		INTEGER,
		FLOAT
	};
	std::vector<FmtType>				m_vecFmt;//��ʽ���Ʒ�
	CString								m_templateStr;//ģ���ַ���

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

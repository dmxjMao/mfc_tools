
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
	CString												m_templateStr;//ģ���ַ���
	std::vector<CMyFmtSplitBtn::FmtContext>				m_vecFmt;//��ƥ��ĸ�ʽ
	std::vector<CMyFmtSplitBtn::FmtContext>				m_vecExistFmt;//�Ѵ����ĸ�ʽ

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//ģ���ַ����仯
	afx_msg void OnChangeEdit1();
	DECLARE_MESSAGE_MAP()
	CEdit m_edit1;
	virtual void OnOK();
private:
	//��ȡ��ť�˵�
	void doReadMenu();
	//��ֵ�к�
	void doSetFmtLineno();
	//��̬������ʽ���ư�ť
	void doCreateFmtButton();
	//�ж��Ƿ���Ҫ������ʽ���ư�ť
	bool doJudgeFmtChange();

public:
};

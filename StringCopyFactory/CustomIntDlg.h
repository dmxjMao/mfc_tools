#pragma once


// CCustomIntDlg dialog

class CCustomIntDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomIntDlg)

public:
	CCustomIntDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCustomIntDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_int_custom };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
	virtual void OnOK();
public:
	int m_a; //随机整数的边界[a,b]
	int m_b;
};

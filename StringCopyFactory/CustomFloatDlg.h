#pragma once


// CCustomFloatDlg dialog

class CCustomFloatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCustomFloatDlg)

public:
	CCustomFloatDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCustomFloatDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_float_custom };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};

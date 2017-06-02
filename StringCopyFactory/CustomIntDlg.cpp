// CustomIntDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StringCopyFactory.h"
#include "CustomIntDlg.h"
#include "afxdialogex.h"


// CCustomIntDlg dialog

IMPLEMENT_DYNAMIC(CCustomIntDlg, CDialogEx)

CCustomIntDlg::CCustomIntDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_int_custom, pParent)
	, m_a(0)
	, m_b(0)
{

}

CCustomIntDlg::~CCustomIntDlg()
{
}

void CCustomIntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT1, m_a);
	DDX_Text(pDX, IDC_EDIT2, m_b);
}


BEGIN_MESSAGE_MAP(CCustomIntDlg, CDialogEx)

END_MESSAGE_MAP()


// CCustomIntDlg message handlers


void CCustomIntDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class
	UpdateData();

	CDialogEx::OnOK();
}



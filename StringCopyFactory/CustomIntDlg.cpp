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
{

}

CCustomIntDlg::~CCustomIntDlg()
{
}

void CCustomIntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCustomIntDlg, CDialogEx)
END_MESSAGE_MAP()


// CCustomIntDlg message handlers

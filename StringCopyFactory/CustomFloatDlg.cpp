// CustomFloatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StringCopyFactory.h"
#include "CustomFloatDlg.h"
#include "afxdialogex.h"


// CCustomFloatDlg dialog

IMPLEMENT_DYNAMIC(CCustomFloatDlg, CDialogEx)

CCustomFloatDlg::CCustomFloatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_float_custom, pParent)
{

}

CCustomFloatDlg::~CCustomFloatDlg()
{
}

void CCustomFloatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCustomFloatDlg, CDialogEx)
END_MESSAGE_MAP()


// CCustomFloatDlg message handlers

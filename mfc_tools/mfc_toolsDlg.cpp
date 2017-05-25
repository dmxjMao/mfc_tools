
// mfc_toolsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfc_tools.h"
#include "mfc_toolsDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// Cmfc_toolsDlg dialog



Cmfc_toolsDlg::Cmfc_toolsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFC_TOOLS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cmfc_toolsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(Cmfc_toolsDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &Cmfc_toolsDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// Cmfc_toolsDlg message handlers

BOOL Cmfc_toolsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void Cmfc_toolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void Cmfc_toolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR Cmfc_toolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cmfc_toolsDlg::OnBnClickedButton1()
{
	static int nMaxFileNum = 50;//最多50个文件

	//获取编辑框后缀名
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	CString strExt;
	pEdit->GetWindowText(strExt);
	if (strExt.IsEmpty()) return;

	//去掉输入的'.'
	strExt.Trim(_T('.'));

	CFileDialog fileDlg(TRUE);
	OPENFILENAME& ofn = fileDlg.GetOFN();
	ofn.Flags |= OFN_ALLOWMULTISELECT;
	CString strBuf;//存储文件列表的buf
	LPTSTR pBuf = strBuf.GetBuffer(nMaxFileNum * MAX_PATH);
	ofn.lpstrFile = pBuf;
	ofn.nMaxFile = nMaxFileNum * MAX_PATH;

	bool bSuccess = true;
	if (IDOK == fileDlg.DoModal()) {
		//多选之后，pathName是上层文件夹
		CString& pathName = fileDlg.GetPathName();

		int ptPos = 0;//'.'位置
		POSITION pos = fileDlg.GetStartPosition();		
		while (pos) {
			pathName = fileDlg.GetNextPathName(pos);
			ptPos = pathName.Find(_T('.'));//查找第一个'.'
			if (-1 == ptPos) {
				bSuccess = false;
				continue;
			}
				
			//构造新文件名
			CString tmpStr = pathName.Left(ptPos + 1);
			tmpStr += strExt;
			CFile::Rename(pathName, tmpStr);
		}
	}
	strBuf.ReleaseBuffer();
	CString strMsg =
		bSuccess ? _T("转换成功！") : _T("有未成功转换后缀的文件，请检查！");
	AfxMessageBox(strMsg);
}

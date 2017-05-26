
// StringCopyFactoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StringCopyFactory.h"
#include "StringCopyFactoryDlg.h"
#include "afxdialogex.h"
#include <algorithm>
#include <vector>
#include <memory>
#include <tuple>
//#include <functional>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace {
	//using std::multimap;
	using std::vector;
	using std::shared_ptr;
	using std::tuple;
	using std::pair;
	using namespace std::placeholders;

	using FmtType = CStringCopyFactoryDlg::FmtType;

	bool MismatchFunc(FmtType t, tuple<FmtType, shared_ptr<CSplitButton>>& p)
	{
		return t == std::get<0>(p);
	}

	//struct FmtSymbolContext {
	//	int nPrefix;//ǰ׺����
	//	std::string suffix;//��׺
	//};

	//ƥ���ʽ���Ʒ�
	boost::regex g_regexTemplateStr;

	//�޷�֪������ƥ�����������ͣ�ֻ���ñ�������
	std::map<std::string, FmtType> g_mapFmtType =
	{
		{"%d",FmtType::INTEGER},
		{"%f",FmtType::FLOAT} 
	};

	//��ť��Ӧ���ı�
	CString g_btnText[] = { _T("����"),_T("С��"), _T("Сд��ĸ"), _T("��д��ĸ"), 
		_T("��Сд������ĸ"), _T("�ɴ�ӡ�ַ�"), _T("Сд�ַ���"), _T("��д�ַ���"),
		_T("��Сд�����ַ���"),_T("����") };
	
	//��ť��Ӧ�Ĳ˵�
	//DWORD g_dwResID[] = { IDD_int_custom,IDD_float_custom };
}

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


// CStringCopyFactoryDlg dialog



CStringCopyFactoryDlg::CStringCopyFactoryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_STRINGCOPYFACTORY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	try {
		g_regexTemplateStr.assign(("(%d)|(%f)"));
	}
	catch (boost::regex_error e) {

	}
}

void CStringCopyFactoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	DDX_Control(pDX, IDC_BUTTON1, m_abc);
}

BEGIN_MESSAGE_MAP(CStringCopyFactoryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CStringCopyFactoryDlg::OnChangeEdit1)
	ON_COMMAND(IDM_int_randpositive, &CStringCopyFactoryDlg::OnIntRandpositive)
END_MESSAGE_MAP()


// CStringCopyFactoryDlg message handlers

BOOL CStringCopyFactoryDlg::OnInitDialog()
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
	//m_edit1.ModifyStyle(0, ES_MULTILINE | ES_WANTRETURN);
	m_abc.ModifyStyle(BS_PUSHBUTTON, BS_SPLITBUTTON);
	m_abc.SetDropDownMenu(IDR_MENU1, 0);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CStringCopyFactoryDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CStringCopyFactoryDlg::OnPaint()
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
HCURSOR CStringCopyFactoryDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CStringCopyFactoryDlg::OnOK()
{
	// TODO: Add your specialized code here and/or call the base class

	//CDialogEx::OnOK();
}




void CStringCopyFactoryDlg::OnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	m_edit1.GetWindowText(m_templateStr);

	//ƥ���ʽ���Ʒ�
	CT2A psz(m_templateStr.GetBuffer());
	std::string textStr(psz);
	boost::sregex_iterator itStart(textStr.begin(), textStr.end(), g_regexTemplateStr);
	boost::sregex_iterator itEnd;

	m_vecFmt.clear();
	for (; itStart != itEnd; ++itStart) {
		const boost::smatch& sm = *itStart;
		const std::string& str = sm.str();
		m_vecFmt.push_back(g_mapFmtType[str]);
	}

	//CString str;
	//str.Format(_T("%d"), m_vecFmt.size());
	//AfxMessageBox(str);

	if (!m_vecFmt.empty()) {
		//��̬������ť
		doCreateFmtButton();
	}
}

void CStringCopyFactoryDlg::doCreateFmtButton()
{
	//�ж��Ƿ���Ҫ������ʽ���ư�ť
	bool bNeedCreate = doJudgeFmtChange();
	if (bNeedCreate) {
		LONG l = GetDialogBaseUnits();
		int x = LOWORD(l);//8
		int y = HIWORD(l);//16
		RECT rcEdit;//�༭����������
		GetDlgItem(IDC_EDIT1)->GetWindowRect(&rcEdit);
		ScreenToClient(&rcEdit);

		for (auto& elm : m_vecExistFmt) {
			//std::tuple<FmtType, std::shared_ptr<CSplitButton>>
			auto spBtn = std::get<1>(elm);
			int w = 0;//��ť��
			if (!spBtn) {
				spBtn = std::make_shared<CSplitButton>();
				FmtType t = std::get<0>(elm);
				CString& btnStr = g_btnText[t];
				w = btnStr.GetLength() * 2 * x;
				//��Ȼ��CSplitButton������������Ҫָ��BS_SPLITBUTTON���
				spBtn->Create(g_btnText[t], WS_CHILD | WS_VISIBLE | BS_SPLITBUTTON,
					CRect(rcEdit.left, rcEdit.bottom - 10, 100, 100),this, 155/*t+100*/);
				spBtn->SetDropDownMenu(IDR_MENU1, 0);
				//���겻�ԣ���β鿴��
				//DWORD style = spBtn->GetStyle();
				//int a = style & BS_PUSHBUTTON;
				//a = style & BS_SPLITBUTTON;
				//a = style & WS_CHILD;
				//a = style & WS_VISIBLE;
				//a = style & WS_POPUP;
				//a = 0;

				/*����
				��ȡedit1 �������꣬�ճ��иߣ�
				��ȡ�ļ���ߣ����ð�ť��С
				�Ի棺https://msdn.microsoft.com/en-us/library/windows/desktop/bb775794(v=vs.85).aspx
				*/
				//spBtn->MoveWindow(rcEdit.left, rcEdit.bottom - 10, 100, 100);
				//CString str;
				//spBtn->GetWindowText(str);
				//TEXTMETRIC tm;
				//spBtn->GetDC()->GetTextMetrics(&tm);
			}
		}
	}

}

bool CStringCopyFactoryDlg::doJudgeFmtChange()
{
	bool bNeed = false;

	auto& v = m_vecFmt;
	auto& vExist = m_vecExistFmt;

	size_t vLen = v.size(), vExistLen = vExist.size();

	/*Ԫ�ز�ƥ���λ�õ���������end(), E �����Ѵ��ڵ�Ԫ�أ�v����̬�仯��Ԫ��*/
	using misPos_vE = pair<decltype(m_vecFmt)::iterator, decltype(m_vecExistFmt)::iterator>;
	using rmisPos_vE = pair<decltype(m_vecFmt)::reverse_iterator, decltype(m_vecExistFmt)::reverse_iterator>;
	using misPos_Ev = pair<decltype(m_vecExistFmt)::iterator, decltype(m_vecFmt)::iterator>;
	//using rmisPos_Ev = pair<decltype(vExist)::reverse_iterator, decltype(v)::reverse_iterator>;

	//mismatchԪ���ٵķ�ǰ��
	if (vLen > vExistLen) {//����Ԫ��
		auto f = bind(MismatchFunc, _2, _1);
		//�鲻ƥ��λ�ã���vExist�й������ӵ�Ԫ��
		misPos_Ev misPos = mismatch(vExist.begin(), vExist.end(), v.begin(), f);
		vExist.erase(misPos.first, vExist.end());
		for (auto it = misPos.second; it != v.end(); ++it) {
			//����յİ�ť
			vExist.emplace_back(std::make_tuple(*it, nullptr));
			bNeed = true;
		}

	}
	else if (vLen < vExistLen) {//ɾ��Ԫ��
		misPos_vE misPos = mismatch(v.begin(), v.end(), vExist.begin(), MismatchFunc);
		vExist.erase(misPos.second, vExist.end());
		for (auto it = misPos.first; it != v.end(); ++it) {
			vExist.emplace_back(std::make_tuple(*it, nullptr));
			bNeed = true;
		}
	}
	else {//�滻Ԫ��
		
		misPos_vE misPos = mismatch(v.begin(), v.end(), vExist.begin(), MismatchFunc);
		if (v.end() == misPos.first && vExist.end() == misPos.second) {
			return false;//��ͬԪ��
		}
		size_t pos = distance(vExist.begin(), misPos.second);
		rmisPos_vE rmisPos = mismatch(v.rbegin(), v.rend(), vExist.rbegin(), MismatchFunc);
		size_t rpos = distance(rmisPos.second, vExist.rend()) - 1;
		auto it = v.begin();
		while (pos <= rpos) {
			vExist[pos] = std::make_tuple(*(it + pos), nullptr);
			++pos;
			bNeed = true;
		}
	}
	return bNeed;
}

void CStringCopyFactoryDlg::OnIntRandpositive()
{
	// TODO: Add your command handler code here
	AfxMessageBox(_T("rand postive!"));
}

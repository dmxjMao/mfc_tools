
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
	//using std::tuple;
	using std::pair;
	using namespace std::placeholders;

	using FmtType = CMyFmtSplitBtn::FmtType;
	using FmtContext = CMyFmtSplitBtn::FmtContext;

	bool MismatchFunc(const FmtContext& l, const FmtContext& r)
	{
		return l.type == r.type;
	}

	//std::map<FmtType, FmtContext> g_mapFmtContext;

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

	//��ť���˵����Ӳ˵�
	CMenu g_menu; 
	CMenu g_subMenu[FmtType::FmtTypeBuf];//���븽�ӵ����˵�
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
		g_regexTemplateStr.assign(("(%d)|(%f)"), boost::regbase::save_subexpression_location);
	}
	catch (boost::regex_error e) {

	}
}

void CStringCopyFactoryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit1);
	//DDX_Control(pDX, IDC_BUTTON1, m_abc);
}

BEGIN_MESSAGE_MAP(CStringCopyFactoryDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CStringCopyFactoryDlg::OnChangeEdit1)
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
	//��ȡ��ť�˵�
	doReadMenu();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

//��ȡ��ť�˵�
void CStringCopyFactoryDlg::doReadMenu()
{
	bool bDefault = true;//Ĭ�ϲ˵�
	g_menu.CreateMenu();
	if (bDefault) {
		vector<vector<CString>> defaultStr = {
			{ _T("���������"),_T("�������"), _T("�Զ���...") },
			{ _T("�����������"),_T("���������"), _T("�Զ���...") }
		};
		size_t cnt = defaultStr.size();
		for (size_t i = 0; i < cnt; ++i) {
			CMenu& menu = g_subMenu[i];
			menu.CreateMenu();
			auto& vecStr = defaultStr[i];
			for (size_t j = 0; j < vecStr.size(); ++j) {
				menu.AppendMenu(MF_STRING, (i + 1) * 1000 + (j + 1), vecStr[j]);
			}
			g_menu.AppendMenu(MF_POPUP, (UINT_PTR)menu.GetSafeHmenu(), _T(""));
		}
	}
	else {//���ļ���ȡ

	}
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

		m_vecFmt.emplace_back(g_mapFmtType[str],
			0,//�����к�
			sm.position()//����
		);
		//sm.prefix().length(),//ǰ׺����
		//sm.suffix().length());//��׺����
	}
	
	if (!m_vecFmt.empty()) {
		//��ֵ�к�
		doSetFmtLineno();
		//��̬������ť
		doCreateFmtButton();
	}
}

void CStringCopyFactoryDlg::doSetFmtLineno()
{
	int pos = 0, lineno = 0;
	pos = m_templateStr.Find(_T("\r\n"), pos);
	auto it = m_vecFmt.begin();
	while (-1 != pos) {//�ҵ�����
		for (; it != m_vecFmt.end(); ++it) {
			FmtContext& ctx = *it;
			if (ctx.pos < pos) {
				ctx.line = lineno;
			}
			else {
				break;
			}
		}
		++lineno;
		pos = m_templateStr.Find(_T("\r\n"), pos + 1);
	}
	for (; it != m_vecFmt.end(); ++it) {
		FmtContext& ctx = *it;
		ctx.line = lineno;
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
		CFont* pFont = GetFont();//�Ի���ʹ�õ�����

		int left = rcEdit.left;//��ť��������
		int bottom = rcEdit.bottom + 10;

		for (auto& ctx : m_vecExistFmt) {
			auto& spBtn = ctx.spBtn; //���ﲻ�����ã���Զ��������
			int w = 0, h = y * 3 / 2;//��ť���
			
			if (!spBtn) {
				FmtType t = ctx.type;
				spBtn = std::make_shared<CMyFmtSplitBtn>(t);
				
				CString& btnStr = g_btnText[t];
				w = (btnStr.GetLength() * 2 * x/*���ٸ��ַ���*/) * 3 / 2/*1.5��*/;
				spBtn->SetSize(w, h);//���ð�ť���
				//��Ȼ��CSplitButton������������Ҫָ��BS_SPLITBUTTON���
				spBtn->Create(_T(""), WS_CHILD | WS_VISIBLE | BS_SPLITBUTTON,
					CRect(0,0,0,0), this, t+100);//һ��ҪCRect(0,0,0,0)
				
				spBtn->SetFont(pFont);
				spBtn->SetWindowText(g_btnText[t]);
				//spBtn->SetDropDownMenu(IDR_MENU1, t);
				spBtn->SetDropDownMenu(&g_subMenu[t]);

				//RECT rcBtn;
				//rcBtn.left = rcEdit.left + x * ctx.pos;
				//rcBtn.top = rcEdit.bottom;
				//rcBtn.right = rcBtn.left + w;
				//rcBtn.bottom = rcBtn.top + h;
				spBtn->MoveWindow(left, bottom, w, h);
				//spBtn->MoveWindow(&rcBtn);
			}
			else {//��Ϊ�վ�Ҫ������һ����ť����ʾλ��

			}
			left += spBtn->GetSize().cx;
			bottom += (rcEdit.bottom + 10) * ctx.line;
		}
	}

}

bool CStringCopyFactoryDlg::doJudgeFmtChange()
{
	bool bNeed = false;

	auto& v = m_vecFmt;//�µĸ�ʽ����
	auto& vExist = m_vecExistFmt;//�Ѵ�������

	size_t vLen = v.size(), vExistLen = vExist.size();

	/*Ԫ�ز�ƥ���λ�õ���������end(), E �����Ѵ��ڵ�Ԫ�أ�v����̬�仯��Ԫ��*/
	using vecFmtIter = decltype(m_vecFmt)::iterator;
	using vecFmtRIter = decltype(m_vecFmt)::reverse_iterator;

	//mismatchԪ���ٵķ�ǰ��
	if (vLen > vExistLen) {//����Ԫ��
		//auto f = bind(MismatchFunc, _2, _1);
		//�鲻ƥ��λ�ã���vExist���ƶ����ӵ�Ԫ��
		pair<vecFmtIter, vecFmtIter> misPos = 
			mismatch(vExist.begin(), vExist.end(), v.begin(), MismatchFunc);
		vExist.erase(misPos.first, vExist.end());
		for (auto it = misPos.second; it != v.end(); ++it) {
			//�ƶ�
			vExist.emplace_back(*it);
			bNeed = true;
		}

	}
	else if (vLen < vExistLen) {//ɾ��Ԫ��
		pair<vecFmtIter, vecFmtIter> misPos = 
			mismatch(v.begin(), v.end(), vExist.begin(), MismatchFunc);
		vExist.erase(misPos.second, vExist.end());
		for (auto it = misPos.first; it != v.end(); ++it) {
			//vExist.emplace_back(std::make_tuple(*it, nullptr));
			vExist.emplace_back(*it);
			bNeed = true;
		}
	}
	else {//�滻Ԫ��
		
		pair<vecFmtIter, vecFmtIter> misPos = 
			mismatch(v.begin(), v.end(), vExist.begin(), MismatchFunc);
		if (v.end() == misPos.first && vExist.end() == misPos.second) {
			return false;//��ͬԪ��
		}
		size_t pos = distance(vExist.begin(), misPos.second);
		pair<vecFmtRIter, vecFmtRIter> rmisPos =
			mismatch(v.rbegin(), v.rend(), vExist.rbegin(), MismatchFunc);
		size_t rpos = distance(rmisPos.second, vExist.rend()) - 1;
		auto it = v.begin();
		while (pos <= rpos) {
			vExist[pos] = *(it + pos);
			++pos;
			bNeed = true;
		}
	}
	return bNeed;
}


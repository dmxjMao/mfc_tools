
// StringCopyFactoryDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StringCopyFactory.h"
#include "StringCopyFactoryDlg.h"
#include "afxdialogex.h"
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace {
	using std::multimap;
	using std::vector;
	using std::pair;
	using std::shared_ptr;
	
	using misPair_vm = pair<vector<CStringCopyFactoryDlg::FmtType>::iterator,
		multimap<CStringCopyFactoryDlg::FmtType, shared_ptr<CSplitButton>>::iterator>;
	using misPair_mv = pair<multimap<CStringCopyFactoryDlg::FmtType, shared_ptr<CSplitButton>>::iterator,
		vector<CStringCopyFactoryDlg::FmtType>::iterator>;
	using namespace std::placeholders;

	bool MismatchFunc(CStringCopyFactoryDlg::FmtType t, 
		pair<CStringCopyFactoryDlg::FmtType, shared_ptr<CSplitButton>> p)
	{
		return t == p.first;
	}

	//struct FmtSymbolContext {
	//	int nPrefix;//前缀长度
	//	std::string suffix;//后缀
	//};

	//匹配格式控制符
	boost::regex g_regexTemplateStr;

	//无法知道正则匹配了哪种类型，只能用笨方法了
	std::map<std::string, CStringCopyFactoryDlg::FmtType> g_mapFmtType =
	{
		{"%d",CStringCopyFactoryDlg::FmtType::INTEGER},
		{"%f",CStringCopyFactoryDlg::FmtType::FLOAT} 
	};
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
	//m_edit1.ModifyStyle(0, ES_MULTILINE | ES_WANTRETURN);

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

	//匹配格式控制符
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

	//动态创建按钮
	doCreateFmtButton();
}

void CStringCopyFactoryDlg::doCreateFmtButton()
{


	vector<tuple<FmtType, CSplitBtn*>> vExist
		= {
			{ INTEGER,new CSplitBtn },
			{ FLOAT,new CSplitBtn },
			{ ANYCHAR,new CSplitBtn }
	};

	//增删改
	vector<FmtType> v = { INTEGER,ANYCHAR };

	size_t vLen = v.size(), vExistLen = vExist.size();

	/*元素不匹配的位置迭代器，有end(), E 代表已存在的元素，v代表动态变化的元素*/
	using misPos_vE = pair<decltype(v)::iterator, decltype(vExist)::iterator>;
	//using rmisPos_vE = pair<decltype(v)::reverse_iterator, decltype(vExist)::reverse_iterator>;
	using misPos_Ev = pair<decltype(vExist)::iterator, decltype(v)::iterator>;
	//using rmisPos_Ev = pair<decltype(vExist)::reverse_iterator, decltype(v)::reverse_iterator>;

	using namespace std::placeholders;

	//mismatch元素少的放前面
	if (vLen > vExistLen) {//增加, 动态元素多
		auto f = bind(MismatchFunc, _2, _1);
		//查不匹配位置，在vExist中构造增加的元素
		misPos_Ev misPos = mismatch(vExist.begin(), vExist.end(), v.begin(), f);
		vExist.erase(misPos.first, vExist.end());
		for (auto it = misPos.second; it != v.end(); ++it) {
			//构造空的按钮
			vExist.emplace_back(make_tuple(*it, nullptr));
		}

		//哪个位置开始不匹配
		//size_t misPos = distance(v.begin(), pEv.second);
		//反向查找一次不匹配
		//rmisPos_Ev prEv = mismatch(vExist.rbegin(), vExist.rend(), v.rbegin(), f);
		////反向哪个位置开始不匹配
		//size_t rmisPos = distance(prEv.second, v.rend()) - 1;/*vLen - distance(v.rbegin(), prEv.second) - 1;*/
		//有一种v=112, vExist=12的情况：反向位置<正向  1234 和 12334都是
		//if (rmisPos < misPos) {
		//	rmisPos = misPos +
		//		distance(vExist.begin(), pEv.first)
		//		- distance(prEv.first, vExist.rend()) - 1 ;
		//}
		/* rmisPos - misPos 是要插入元素的个数 */
		//auto tmpIt = pEv.first;//正向不匹配位置
		//while (misPos <= rmisPos) {//遍历所有要插入的元素
		//	tmpIt = vExist.insert(tmpIt, make_tuple(*(v.begin() + rmisPos++),nullptr));
		//	++tmpIt; //vector在前面插入,这样就在后面插入了
		//}
	}
	else if (vLen < vExistLen) {//删,动态元素少
		misPos_vE misPos = mismatch(v.begin(), v.end(), vExist.begin(), MismatchFunc);
		vExist.erase(misPos.second, vExist.end());
		for (auto it = misPos.first; it != v.end(); ++it) {
			vExist.emplace_back(make_tuple(*it, nullptr));
		}
		//misPos_vE pvE = mismatch(v.begin(), v.end(), vExist.begin(), MismatchFunc);//正向查找一次不匹配
		//size_t pvEpos = distance(vExist.begin(), pvE.second);//第几个元素开始为删除的元素，从多的取
		//rmisPos_vE prvE = mismatch(v.rbegin(), v.rend(), vExist.rbegin(), MismatchFunc);//反向查找一次不匹配
		//size_t prvEpos = vExistLen - distance(vExist.rbegin(), prvE.second) - 1;

		//auto eIt1 = pvE.second;
		//auto eIt2 = eIt1 + prvEpos - pvEpos;
		//vExist.erase(eIt1, eIt2);

	}
	else {//改
		  //misPair_vm p = mismatch(v.begin(), v.end(), m.begin(), MismatchFunc);
		  //FmtType tv = *p.first;
		  //FmtType tm = p.second->first;
		  //cout << "FmtType add:" << tv << "\tdelete:" << tm << endl;
	}

}
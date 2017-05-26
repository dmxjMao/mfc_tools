
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
	//	int nPrefix;//ǰ׺����
	//	std::string suffix;//��׺
	//};

	//ƥ���ʽ���Ʒ�
	boost::regex g_regexTemplateStr;

	//�޷�֪������ƥ�����������ͣ�ֻ���ñ�������
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

	//��̬������ť
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

	//��ɾ��
	vector<FmtType> v = { INTEGER,ANYCHAR };

	size_t vLen = v.size(), vExistLen = vExist.size();

	/*Ԫ�ز�ƥ���λ�õ���������end(), E �����Ѵ��ڵ�Ԫ�أ�v����̬�仯��Ԫ��*/
	using misPos_vE = pair<decltype(v)::iterator, decltype(vExist)::iterator>;
	//using rmisPos_vE = pair<decltype(v)::reverse_iterator, decltype(vExist)::reverse_iterator>;
	using misPos_Ev = pair<decltype(vExist)::iterator, decltype(v)::iterator>;
	//using rmisPos_Ev = pair<decltype(vExist)::reverse_iterator, decltype(v)::reverse_iterator>;

	using namespace std::placeholders;

	//mismatchԪ���ٵķ�ǰ��
	if (vLen > vExistLen) {//����, ��̬Ԫ�ض�
		auto f = bind(MismatchFunc, _2, _1);
		//�鲻ƥ��λ�ã���vExist�й������ӵ�Ԫ��
		misPos_Ev misPos = mismatch(vExist.begin(), vExist.end(), v.begin(), f);
		vExist.erase(misPos.first, vExist.end());
		for (auto it = misPos.second; it != v.end(); ++it) {
			//����յİ�ť
			vExist.emplace_back(make_tuple(*it, nullptr));
		}

		//�ĸ�λ�ÿ�ʼ��ƥ��
		//size_t misPos = distance(v.begin(), pEv.second);
		//�������һ�β�ƥ��
		//rmisPos_Ev prEv = mismatch(vExist.rbegin(), vExist.rend(), v.rbegin(), f);
		////�����ĸ�λ�ÿ�ʼ��ƥ��
		//size_t rmisPos = distance(prEv.second, v.rend()) - 1;/*vLen - distance(v.rbegin(), prEv.second) - 1;*/
		//��һ��v=112, vExist=12�����������λ��<����  1234 �� 12334����
		//if (rmisPos < misPos) {
		//	rmisPos = misPos +
		//		distance(vExist.begin(), pEv.first)
		//		- distance(prEv.first, vExist.rend()) - 1 ;
		//}
		/* rmisPos - misPos ��Ҫ����Ԫ�صĸ��� */
		//auto tmpIt = pEv.first;//����ƥ��λ��
		//while (misPos <= rmisPos) {//��������Ҫ�����Ԫ��
		//	tmpIt = vExist.insert(tmpIt, make_tuple(*(v.begin() + rmisPos++),nullptr));
		//	++tmpIt; //vector��ǰ�����,�������ں��������
		//}
	}
	else if (vLen < vExistLen) {//ɾ,��̬Ԫ����
		misPos_vE misPos = mismatch(v.begin(), v.end(), vExist.begin(), MismatchFunc);
		vExist.erase(misPos.second, vExist.end());
		for (auto it = misPos.first; it != v.end(); ++it) {
			vExist.emplace_back(make_tuple(*it, nullptr));
		}
		//misPos_vE pvE = mismatch(v.begin(), v.end(), vExist.begin(), MismatchFunc);//�������һ�β�ƥ��
		//size_t pvEpos = distance(vExist.begin(), pvE.second);//�ڼ���Ԫ�ؿ�ʼΪɾ����Ԫ�أ��Ӷ��ȡ
		//rmisPos_vE prvE = mismatch(v.rbegin(), v.rend(), vExist.rbegin(), MismatchFunc);//�������һ�β�ƥ��
		//size_t prvEpos = vExistLen - distance(vExist.rbegin(), prvE.second) - 1;

		//auto eIt1 = pvE.second;
		//auto eIt2 = eIt1 + prvEpos - pvEpos;
		//vExist.erase(eIt1, eIt2);

	}
	else {//��
		  //misPair_vm p = mismatch(v.begin(), v.end(), m.begin(), MismatchFunc);
		  //FmtType tv = *p.first;
		  //FmtType tm = p.second->first;
		  //cout << "FmtType add:" << tv << "\tdelete:" << tm << endl;
	}

}
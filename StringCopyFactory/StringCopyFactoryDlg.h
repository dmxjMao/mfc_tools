
// StringCopyFactoryDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "MyFmtSplitBtn.h"

//struct CMyFmtSplitBtn::FmtContext;

// CStringCopyFactoryDlg dialog
class CStringCopyFactoryDlg : public CDialogEx
{
// Construction
public:
	CStringCopyFactoryDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STRINGCOPYFACTORY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	CString												m_templateStr;//ģ���ַ���
	std::vector<CMyFmtSplitBtn::FmtContext>				m_vecFmt;//��ƥ��ĸ�ʽ
	std::vector<CMyFmtSplitBtn::FmtContext>				m_vecExistFmt;//�Ѵ����ĸ�ʽ

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//ģ���ַ����仯
	afx_msg void OnChangeEdit1();
	DECLARE_MESSAGE_MAP()
	CEdit m_edit1;
	virtual void OnOK();
private:
	//��ȡ��ť�˵�
	void doReadMenu();
	//��ֵ�к�
	void doSetFmtLineno();
	//��̬������ʽ���ư�ť
	void doCreateFmtButton();
	//�ж��Ƿ���Ҫ������ʽ���ư�ť
	bool doJudgeFmtChange();

public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	afx_msg void OnClickedGenerate();
};

////һ���󶨲˵���Ľṹ
//struct MenuItem {
//	TCHAR	szTitle[10] = { 0 };//�˵��ı� 9����
//	UINT	nID = -1;//�˵�ID
//	int		len = 0;//���Ӳ����ĳ���
//	void*	lpParam = nullptr;//�˵����Ӳ���
//	
//	union MenuItemFunc{
//		void(*v_ii)(int, int);
//		void(*v_ff)(float, float);
//	} func;//�˵�����ָ��
//
//	MenuItem(TCHAR* sz, UINT id, int l, void* lp, MenuItemFunc u) {
//		memcpy(szTitle, sz, 10);
//		nID = id;
//		len = l;
//		memcpy(lpParam, lp, len);
//		func = u;
//	}
//};

enum class RandType;
//���ɰ�ť��ʶ���ķ�ʽ
//UINT_PTR GenerateMenuID(int nBtnIdx, int nItemIdx);
//������ɷ�Χ�ڵ�����
int RandInt(RandType t, int a = 0, int b = 0);
//������ɷ�Χ�ڵ�С��
float RandFloat(RandType t, float a = 0, float b = 0);

class stream_visit : public boost::static_visitor<> {
	std::wostream& m_os;
public:
	stream_visit(std::wostream& os) : m_os(os) {}
	template<typename T>
	void operator()(T& t) const {
		m_os << t;
	}
};
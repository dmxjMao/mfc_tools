
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
	CString												m_templateStr;//模板字符串
	std::vector<CMyFmtSplitBtn::FmtContext>				m_vecFmt;//新匹配的格式
	std::vector<CMyFmtSplitBtn::FmtContext>				m_vecExistFmt;//已创建的格式

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//模板字符串变化
	afx_msg void OnChangeEdit1();
	DECLARE_MESSAGE_MAP()
	CEdit m_edit1;
	virtual void OnOK();
private:
	//读取按钮菜单
	void doReadMenu();
	//赋值行号
	void doSetFmtLineno();
	//动态创建格式控制按钮
	void doCreateFmtButton();
	//判断是否需要创建格式控制按钮
	bool doJudgeFmtChange();

public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	afx_msg void OnClickedGenerate();
};

////一个绑定菜单项的结构
//struct MenuItem {
//	TCHAR	szTitle[10] = { 0 };//菜单文本 9个字
//	UINT	nID = -1;//菜单ID
//	int		len = 0;//附加参数的长度
//	void*	lpParam = nullptr;//菜单附加参数
//	
//	union MenuItemFunc{
//		void(*v_ii)(int, int);
//		void(*v_ff)(float, float);
//	} func;//菜单函数指针
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
//生成按钮标识符的方式
//UINT_PTR GenerateMenuID(int nBtnIdx, int nItemIdx);
//随机生成范围内的整数
int RandInt(RandType t, int a = 0, int b = 0);
//随机生成范围内的小数
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
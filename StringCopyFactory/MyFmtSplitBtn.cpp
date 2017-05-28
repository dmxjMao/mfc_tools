#include"stdafx.h"
#include "MyFmtSplitBtn.h"
#include "resource.h"


int CMyFmtSplitBtn::m_curBtn = -1;

BEGIN_MESSAGE_MAP(CMyFmtSplitBtn, CSplitButton)
	
	ON_NOTIFY_REFLECT(BCN_DROPDOWN, &CMyFmtSplitBtn::OnDropDown)
END_MESSAGE_MAP()

//点击菜单项
void CMyFmtSplitBtn::OnMenuMsg(UINT nID)
{
	m_curID = nID;
	////如果点击了自定义
	//extern CMenu g_subMenu[FmtType::FmtTypeBuf];
	//extern UINT_PTR GenerateMenuID(int nBtnIdx, int nItemIdx);
	//
	//CMenu& menu = g_subMenu[m_curBtn];
	//UINT_PTR nCustomID = GenerateMenuID(m_curBtn, menu.GetMenuItemCount());
	//if (nID == nCustomID) {
	//	switch (m_curBtn)
	//	{
	//	case INTEGER:
	//	{
	//		CCustomIntDlg dlg;
	//		dlg.DoModal();
	//		break;
	//	}
	//	case FLOAT:
	//	{
	//		CCustomFloatDlg dlg;
	//		dlg.DoModal();
	//		break;
	//	}
	//	}
	//}
	//else { //否则记录点击的菜单ID
	//	m_curID = nID;
	//}

}


//对话框消息路由无法获取到当前正在处理的菜单句柄
//向导创建的OnBnDropDown有问题
void CMyFmtSplitBtn::OnDropDown(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMBCDROPDOWN pDropDown = reinterpret_cast<LPNMBCDROPDOWN>(pNMHDR);
	// TODO: Add your control notification handler code here
	//m_curBtn = m_type;
	m_curBtn = m_idx;
	//CSplitButton::OnBnDropDown(pNMHDR, pResult);
	__super::OnDropDown(pNMHDR, pResult);
	*pResult = 0;
}



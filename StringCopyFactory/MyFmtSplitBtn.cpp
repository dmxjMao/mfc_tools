#include"stdafx.h"
#include "MyFmtSplitBtn.h"
#include "resource.h"
#include "CustomIntDlg.h"

int CMyFmtSplitBtn::m_curBtn = -1;

BEGIN_MESSAGE_MAP(CMyFmtSplitBtn, CSplitButton)
	
	ON_NOTIFY_REFLECT(BCN_DROPDOWN, &CMyFmtSplitBtn::OnDropDown)
END_MESSAGE_MAP()

//点击菜单项
void CMyFmtSplitBtn::OnMenuMsg(UINT nID)
{
	m_curID = nID;
	
	//如果点击了自定义
	switch (nID) {
		case IDM_intCustom:{
			CCustomIntDlg dlg;
			if (IDOK == dlg.DoModal()) {
				m_param = IntParam(dlg.m_a, dlg.m_b);
			}
			break;
		}
	}

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



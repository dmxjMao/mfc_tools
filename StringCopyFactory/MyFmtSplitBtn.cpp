#include"stdafx.h"
#include "MyFmtSplitBtn.h"
#include "resource.h"


int CMyFmtSplitBtn::m_curBtn = -1;

BEGIN_MESSAGE_MAP(CMyFmtSplitBtn, CSplitButton)
	
	ON_NOTIFY_REFLECT(BCN_DROPDOWN, &CMyFmtSplitBtn::OnDropDown)
END_MESSAGE_MAP()

//����˵���
void CMyFmtSplitBtn::OnMenuMsg(UINT nID)
{
	m_curID = nID;
	////���������Զ���
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
	//else { //�����¼����Ĳ˵�ID
	//	m_curID = nID;
	//}

}


//�Ի�����Ϣ·���޷���ȡ����ǰ���ڴ���Ĳ˵����
//�򵼴�����OnBnDropDown������
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



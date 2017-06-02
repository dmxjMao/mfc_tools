#include"stdafx.h"
#include "MyFmtSplitBtn.h"
#include "resource.h"
#include "CustomIntDlg.h"

int CMyFmtSplitBtn::m_curBtn = -1;

BEGIN_MESSAGE_MAP(CMyFmtSplitBtn, CSplitButton)
	
	ON_NOTIFY_REFLECT(BCN_DROPDOWN, &CMyFmtSplitBtn::OnDropDown)
END_MESSAGE_MAP()

//����˵���
void CMyFmtSplitBtn::OnMenuMsg(UINT nID)
{
	m_curID = nID;
	
	//���������Զ���
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



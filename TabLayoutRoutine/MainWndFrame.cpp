#include "MainWndFrame.h"

CDuiString MainWndFrame::GetSkinFolder()
{
	return _T("TabLayout\\");
}

CDuiString MainWndFrame::GetSkinFile()
{
	return _T("skin.xml");
}

LPCTSTR MainWndFrame::GetWindowClassName(void) const
{
	return _T("TabLayoutWindow");
}

void MainWndFrame::Notify(TNotifyUI & msg)
{
	//�ж���Ϣ����
	if (msg.sType == DUI_MSGTYPE_BUTTONDOWN)
	{
		CDuiString strName = msg.pSender->GetName();//��ȡ�����¼��Ŀؼ���
		if (strName == _T("Option01"))
			_tabLayout->SelectItem(0);
		else if (strName == _T("Option02"))
			_tabLayout->SelectItem(1);
		else
			return;
	}

	__super::Notify(msg);
}

void MainWndFrame::InitWindow()
{
	//��ȡ�ؼ�����
	_tabLayout = dynamic_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("TabLayoutMain")));
}


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
	//判断消息类型
	if (msg.sType == DUI_MSGTYPE_BUTTONDOWN)
	{
		CDuiString strName = msg.pSender->GetName();//获取发出事件的控件名
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
	//获取控件对象
	_tabLayout = dynamic_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("TabLayoutMain")));
}


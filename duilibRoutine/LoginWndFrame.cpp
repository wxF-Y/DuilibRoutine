#include "LoginWndFrame.h"

using DuiLib::CButtonUI;

LoginWndFrame::LoginWndFrame()
	:_btn_close{NULL}
{
}

void LoginWndFrame::InitWindow()
{
	//_btn_close = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl("btn_loginFrame_close"));
}

void LoginWndFrame::Notify(TNotifyUI & msg)
{
	if (msg.sType == DUI_MSGTYPE_CLICK)
	{
		CDuiString strName = msg.pSender->GetName();
		if (strName == _T("btn_loginFrame_close"))
			ShowWindow(false);
	}
}

CDuiString LoginWndFrame::GetSkinFolder()
{
	return _T("theme");
}

CDuiString LoginWndFrame::GetSkinFile() 
{
	return _T("login.xml");
}

LPCTSTR LoginWndFrame::GetWindowClassName(void) const
{
	return _T("LoginWndFrame");
}

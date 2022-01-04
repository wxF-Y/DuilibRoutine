#include "MainWndFrame.h"

MainWndFrame::MainWndFrame()
	:_btn_min{NULL},_btn_max{NULL},_btn_restore{NULL},_btn_shutdown{NULL}
{
}

LPCTSTR MainWndFrame::GetWindowClassName() const
{
	return _T("Wangxi");
}

CDuiString MainWndFrame::GetSkinFile()
{
	return _T("skin.xml");
}

CDuiString MainWndFrame::GetSkinFolder()
{
	return "theme";
}

void MainWndFrame::InitWindow()
{
	//获取控件对象
	_btn_min = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_min")));
	_btn_max = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_max")));
	_btn_restore = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_restore")));
	_btn_shutdown = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_shutdown")));
}

void MainWndFrame::Notify(TNotifyUI & msg)
{
	//判断消息类型
	if (msg.sType == DUI_MSGTYPE_CLICK)//click事件 
	{
		CDuiString strName = msg.pSender->GetName();//获取发出事件的控件名
		if (strName == _T("btn_min"))
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);
		else if (strName == _T("btn_max"))
		{
			_btn_restore->SetVisible(true);
			_btn_max->SetVisible(false);
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
		}
		else if (strName == _T("btn_restore"))
		{
			_btn_restore->SetVisible(false);
			_btn_max->SetVisible(true);
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0);
		}
		else  if (strName == _T("btn_shutdown"))
			SendMessage(WM_SYSCOMMAND, SC_CLOSE, 0);
		else
			return;
	}

	__super::Notify(msg);
}

LRESULT MainWndFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	if (uMsg == WM_CLOSE)
		PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}


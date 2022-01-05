#include "MainWndFrame.h"

MainWndFrame::MainWndFrame()
	:_btn_min{NULL},_btn_max{NULL},_btn_restore{NULL},_btn_shutdown{NULL},_btn_personal{NULL},
	_loginWndFrame{NULL}
{
}

CDuiString MainWndFrame::GetSkinFolder()
{
	
	return _T("theme");
}

CDuiString MainWndFrame::GetSkinFile()
{
	return _T("main_frame.xml");
}

LPCTSTR MainWndFrame::GetWindowClassName(void) const
{
	return _T("Wangxi");
}

void MainWndFrame::InitWindow()
{
	//获取控件对象
	_btn_min = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_min")));
	_btn_max = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_max")));
	_btn_restore = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_restore")));
	_btn_shutdown = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_shutdown")));
	_btn_personal = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_personal")));
	_btn_skin = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_skinChange")));
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
		else if (strName == _T("btn_personal"))
		{
			if (_loginWndFrame == NULL)
			{
				_loginWndFrame = new (nothrow)LoginWndFrame;
				ASSERT(_loginWndFrame);
				if (_loginWndFrame == NULL)
					MessageBox(NULL, _T("创建登录子窗口失败"), _T("MainWndFrame"), MB_OK | MB_ICONERROR);
#if defined(WIN32) && !(UNDRE_CE)
				_loginWndFrame->Create(this->GetHWND(), _loginWndFrame->GetWindowClassName(), UI_WNDSTYLE_FRAME | WS_CLIPCHILDREN, WS_EX_WINDOWEDGE, 0, 0, 300, 400);
#else
				_loginWndFrame->Create(this->GetHWND(), _loginWndFrame->GetWindowClassName(), UI_WNDSTYLE_FRAME, WS_EX_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
#endif
			}
			_loginWndFrame->CenterWindow();
			_loginWndFrame->ShowWindow();
		}
		else if (strName == _T("btn_skinChange"))
		{
			CDuiRect rcWindow;
			GetWindowRect(m_hWnd, &rcWindow);
			rcWindow.top = rcWindow.top + msg.pSender->GetPos().bottom;

		}
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




#include "MainWndFrame.h"

#include "ColorSkinWndFrame.h"

#include <string>

using DuiLib::CDuiRect;

MainWndFrame::MainWndFrame()
	:_btn_min{NULL},_btn_max{NULL},_btn_restore{NULL},_btn_shutdown{NULL},_btn_personal{NULL},_btn_skin{NULL},
	_loginWndFrame{NULL},_builder{new (std::nothrow)CDialogBuilder}
{
	ASSERT(_builder && _T("new CDialogBuilder fail"));
	if(_builder == NULL)
		MessageBox(NULL, _T("主窗口创建DialogBuilder失败"), _T("MainWndFrame"), MB_OK | MB_ICONERROR);
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

#if defined _UNICODE
std::wstring FromCDuiString(CDuiString name)
{
	return std::move(std::wstring(name.GetData()));
}
#else
const char_t* FromCDuiString(CDuiString name)
{
	return std::move(std::string(name.GetData()));
}
#endif


void MainWndFrame::InitWindow()
{
	//获取控件对象
	_btn_min = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_min")));
	_btn_max = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_max")));
	_btn_restore = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_restore")));
	_btn_shutdown = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_shutdown")));
	_btn_personal = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_personal")));
	_btn_skin = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_skinChange")));

	_tabLayout = dynamic_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentTabLayout")));


	_curSelectedOption = dynamic_cast<COptionUI*>(m_PaintManager.FindControl(_T("findMusic")));
	_curSelectedOption->SetAttribute(_T("bkcolor"), _T("#FFBCC6D0"));//将选中Option背景颜色修改
	_curSelectedOption->SetFont(2);

	CControlUI* curTabContent = CreateNewTab();
	ASSERT(curTabContent && _T("new tab content fail"));
	_tabLayout->Add(curTabContent);
	int index = _tabLayout->GetItemIndex(curTabContent);
	_tabLayout->SelectItem(index);

	//进行名字映射
	auto name = FromCDuiString(_curSelectedOption->GetName());
	m_optionMapToTab[name] = index;
}



void MainWndFrame::Notify(TNotifyUI & msg)
{
	//判断消息类型
	if (msg.sType == DUI_MSGTYPE_CLICK)//click事件 
	{
		CControlUI* senderParent = msg.pSender->GetParent();
		if (senderParent->GetName() == _T("OptionLayout"))
			HandleOptionEvent(msg);
		else if (senderParent->GetName() == _T("BasicWindowComLayout"))
			HandleBasicBtnEvEnt(msg);
		else if (senderParent->GetName() == _T("PersonalLayout"))
			HandlePersonalEvent(msg);
	}

	__super::Notify(msg);
}

LRESULT MainWndFrame::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	if (uMsg == WM_CLOSE)
		PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

void MainWndFrame::setBKColor(DWORD dwBackColor)
{
	CControlUI* background = m_PaintManager.FindControl(_T("bkControl"));
	if (background != NULL)
	{
		background->SetBkImage(_T(""));//置空背景图
		background->SetBkColor(dwBackColor);//设置背景控件的颜色
		background->NeedUpdate();//刷新
	}
}

void MainWndFrame::HandleOptionEvent(TNotifyUI & msg)
{
	CDuiString strName = msg.pSender->GetName();//获取发出事件的控件名
	if (strName == _curSelectedOption->GetName())//发出点击事件的option与当前已选中option是一个
		return;

	//option设置
	//发出点击事件的option与当前选中option不一样
	//将当前选中option设置未选中和修改回背景颜色，以及字体
	_curSelectedOption->Selected(false);
	_curSelectedOption->SetAttribute(_T("bkcolor"), _T("#FFFFFFFF"));
	_curSelectedOption->SetFont(1);

	_curSelectedOption = dynamic_cast<COptionUI*>(msg.pSender);
	ASSERT(_curSelectedOption);
	if (_curSelectedOption == nullptr) return;

	_curSelectedOption->Selected(true);
	_curSelectedOption->SetAttribute(_T("bkcolor"), _T("#FFBCC6D0"));
	_curSelectedOption->SetFont(2);
	_curSelectedOption->GetName();

	//tab内容区设置
	//已经存在tab控件
	auto name = FromCDuiString(strName);
	if (m_optionMapToTab.find(name) != m_optionMapToTab.end())
	{
		_tabLayout->SelectItem(m_optionMapToTab[name]);
		return;
	}

	//option还没有对应的tab控件
	CControlUI* curNewContent = CreateNewTab();
	ASSERT(curNewContent && _T("new tab content fail"));
	if (curNewContent == nullptr) return;
	_tabLayout->Add(curNewContent);
	int index = _tabLayout->GetItemIndex(curNewContent);
	_tabLayout->SelectItem(index);
	m_optionMapToTab[name] = index;
}

void MainWndFrame::HandleBasicBtnEvEnt(TNotifyUI & msg)
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

void MainWndFrame::HandlePersonalEvent(TNotifyUI & msg)
{
	CDuiString strName = msg.pSender->GetName();//获取发出事件的控件名
	if (strName == _T("btn_personal"))
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
		new ColorSkinWndFrame(this,rcWindow);
	}
	else
		return;
}

CControlUI * MainWndFrame::CreateNewTab()
{
	CDuiString xmlName = _curSelectedOption->GetName();
	xmlName += _T(".xml");
	DuiLib::STRINGorID name(xmlName);
	return _builder->Create(name, (UINT)0, this, &m_PaintManager);
}




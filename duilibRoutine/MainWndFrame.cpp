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
		MessageBox(NULL, _T("�����ڴ���DialogBuilderʧ��"), _T("MainWndFrame"), MB_OK | MB_ICONERROR);
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
	//��ȡ�ؼ�����
	_btn_min = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_min")));
	_btn_max = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_max")));
	_btn_restore = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_restore")));
	_btn_shutdown = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_shutdown")));
	_btn_personal = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_personal")));
	_btn_skin = dynamic_cast<CButtonUI*>(m_PaintManager.FindControl(_T("btn_skinChange")));

	_tabLayout = dynamic_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("ContentTabLayout")));


	_curSelectedOption = dynamic_cast<COptionUI*>(m_PaintManager.FindControl(_T("findMusic")));
	_curSelectedOption->SetAttribute(_T("bkcolor"), _T("#FFBCC6D0"));//��ѡ��Option������ɫ�޸�
	_curSelectedOption->SetFont(2);

	CControlUI* curTabContent = CreateNewTab();
	ASSERT(curTabContent && _T("new tab content fail"));
	_tabLayout->Add(curTabContent);
	int index = _tabLayout->GetItemIndex(curTabContent);
	_tabLayout->SelectItem(index);

	//��������ӳ��
	auto name = FromCDuiString(_curSelectedOption->GetName());
	m_optionMapToTab[name] = index;
}



void MainWndFrame::Notify(TNotifyUI & msg)
{
	//�ж���Ϣ����
	if (msg.sType == DUI_MSGTYPE_CLICK)//click�¼� 
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
		background->SetBkImage(_T(""));//�ÿձ���ͼ
		background->SetBkColor(dwBackColor);//���ñ����ؼ�����ɫ
		background->NeedUpdate();//ˢ��
	}
}

void MainWndFrame::HandleOptionEvent(TNotifyUI & msg)
{
	CDuiString strName = msg.pSender->GetName();//��ȡ�����¼��Ŀؼ���
	if (strName == _curSelectedOption->GetName())//��������¼���option�뵱ǰ��ѡ��option��һ��
		return;

	//option����
	//��������¼���option�뵱ǰѡ��option��һ��
	//����ǰѡ��option����δѡ�к��޸Ļر�����ɫ���Լ�����
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

	//tab����������
	//�Ѿ�����tab�ؼ�
	auto name = FromCDuiString(strName);
	if (m_optionMapToTab.find(name) != m_optionMapToTab.end())
	{
		_tabLayout->SelectItem(m_optionMapToTab[name]);
		return;
	}

	//option��û�ж�Ӧ��tab�ؼ�
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
	CDuiString strName = msg.pSender->GetName();//��ȡ�����¼��Ŀؼ���
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
	CDuiString strName = msg.pSender->GetName();//��ȡ�����¼��Ŀؼ���
	if (strName == _T("btn_personal"))
	{
		if (_loginWndFrame == NULL)
		{
			_loginWndFrame = new (nothrow)LoginWndFrame;
			ASSERT(_loginWndFrame);
			if (_loginWndFrame == NULL)
				MessageBox(NULL, _T("������¼�Ӵ���ʧ��"), _T("MainWndFrame"), MB_OK | MB_ICONERROR);
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




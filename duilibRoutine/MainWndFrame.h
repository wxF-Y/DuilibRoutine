#pragma once
#include "UIlib.h"
using DuiLib::WindowImplBase;
using DuiLib::CDuiString;
using DuiLib::CTabLayoutUI;
using DuiLib::CControlUI;
using DuiLib::COptionUI;
using DuiLib::CDialogBuilder;
using DuiLib::CButtonUI;

#include "LoginWndFrame.h"

#include <map>

class MainWndFrame :
	public DuiLib::WindowImplBase
{
public:
	MainWndFrame();
	virtual CDuiString GetSkinFolder()  override;
	virtual CDuiString GetSkinFile() override;
	virtual LPCTSTR GetWindowClassName(void) const override;
	virtual void InitWindow();//��ȡ�ؼ�����
	virtual void Notify(TNotifyUI& msg);//�������¼�
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);//��ϵͳ������ֹ

	void setBKColor(DWORD dwBackColor);

	void HandleOptionEvent(TNotifyUI & msg);
	void HandleBasicBtnEvEnt(TNotifyUI& msg);
	void HandlePersonalEvent(TNotifyUI& msg);
private:

	CControlUI* CreateNewTab();//�Ե�ǰѡ��option -- _curSelectedOption��name���д���tab.�ڴ���֮ǰһ��Ҫ�ȳ�ʼ��_curSelectedOption��Ա����

#if defined _UNICODE
	std::map<std::wstring, int> m_optionMapToTab;
#else
	std::map<std::string, int> m_optionMapToTab;
#endif
	
	CDialogBuilder* _builder;

	//�������ڿؼ�
	CButtonUI* _btn_min;
	CButtonUI* _btn_max;
	CButtonUI* _btn_restore;
	CButtonUI* _btn_shutdown;


	//�������ؼ�
	CButtonUI* _btn_personal;
	CButtonUI* _btn_skin;

	//���option��tab������
	CTabLayoutUI* _tabLayout;
	COptionUI* _curSelectedOption;

	//�Ӵ���
	LoginWndFrame* _loginWndFrame;
};


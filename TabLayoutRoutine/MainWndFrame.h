#pragma once
#include "UILib.h"
using DuiLib::WindowImplBase;
using DuiLib::CDuiString;
using DuiLib::TNotifyUI;
using DuiLib::CTabLayoutUI;
using DuiLib::CHorizontalLayoutUI;
using DuiLib::CControlUI;
using DuiLib::COptionUI;
using DuiLib::CLabelUI;
using DuiLib::CDialogBuilder;
using DuiLib::CMarkup;
using DuiLib::UILIB_RESOURCETYPE;

class CTabBarUI;

class MainWndFrame :
	public WindowImplBase
{
public:
	MainWndFrame();
	~MainWndFrame();
	// ͨ�� WindowImplBase �̳�
	CDuiString GetSkinFolder() override;
	CDuiString GetSkinFile() override;
	LPCTSTR GetWindowClassName(void) const override;
	void Notify(TNotifyUI& msg) override;//�������¼�
	void InitWindow() override;//��ȡ�ؼ�����

	//zip
	UILIB_RESOURCETYPE GetResourceType() const override;

	//ʹ����Դzipʱ���ر�����
	LPCTSTR GetResourceID() const override;

	//ʹ�ô���zipʱ���ر�����
	CDuiString GetZIPFileName() const override;

private:
	CTabLayoutUI* _tabLayout;
	COptionUI* _curSelected;
	CHorizontalLayoutUI* _optionsLayout;

	CDialogBuilder* _builder;

	CTabBarUI* _tabBarUI;
};


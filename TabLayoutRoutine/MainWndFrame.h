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
	// 通过 WindowImplBase 继承
	CDuiString GetSkinFolder() override;
	CDuiString GetSkinFile() override;
	LPCTSTR GetWindowClassName(void) const override;
	void Notify(TNotifyUI& msg) override;//处理触发事件
	void InitWindow() override;//获取控件对象

	//zip
	UILIB_RESOURCETYPE GetResourceType() const override;

	//使用资源zip时重载本函数
	LPCTSTR GetResourceID() const override;

	//使用磁盘zip时重载本函数
	CDuiString GetZIPFileName() const override;

private:
	CTabLayoutUI* _tabLayout;
	COptionUI* _curSelected;
	CHorizontalLayoutUI* _optionsLayout;

	CDialogBuilder* _builder;

	CTabBarUI* _tabBarUI;
};


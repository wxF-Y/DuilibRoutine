#pragma once
#include "UILib.h"
using DuiLib::WindowImplBase;
using DuiLib::CDuiString;
using DuiLib::TNotifyUI;
using DuiLib::CTabLayoutUI;

class MainWndFrame :
	public WindowImplBase
{
public:
	// 通过 WindowImplBase 继承
	CDuiString GetSkinFolder() override;
	CDuiString GetSkinFile() override;
	LPCTSTR GetWindowClassName(void) const override;
	void Notify(TNotifyUI& msg) override;//处理触发事件
	void InitWindow() override;//获取控件对象
private:
	CTabLayoutUI* _tabLayout;
};


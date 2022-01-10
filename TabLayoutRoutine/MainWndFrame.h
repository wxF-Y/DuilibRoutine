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

class MainWndFrame :
	public WindowImplBase
{
public:
	// ͨ�� WindowImplBase �̳�
	CDuiString GetSkinFolder() override;
	CDuiString GetSkinFile() override;
	LPCTSTR GetWindowClassName(void) const override;
	void Notify(TNotifyUI& msg) override;//�������¼�
	void InitWindow() override;//��ȡ�ؼ�����
private:
	CTabLayoutUI* _tabLayout;
	COptionUI* _curSelected;
	CHorizontalLayoutUI* _optionsLayout;
};


#pragma once

#include "UILib.h"
using  DuiLib::CDuiString;
using  DuiLib::CControlUI;
using  DuiLib::TNotifyUI;

class LoginWndFrame :
	public DuiLib::WindowImplBase
{
public:
	LoginWndFrame();
	virtual void InitWindow() override;
	virtual void Notify(TNotifyUI& msg) override; 

	// ͨ�� WindowImplBase �̳�
	virtual CDuiString GetSkinFolder()  override;
	virtual CDuiString GetSkinFile() override;
	virtual LPCTSTR GetWindowClassName(void) const override;

private:
	CControlUI* _btn_close;
};


#pragma once

#include "UILib.h"
using DuiLib::WindowImplBase;
using  DuiLib::CDuiString;

class MainWndFrame :
	public WindowImplBase
{
public:
	// ͨ�� WindowImplBase �̳�
	virtual CDuiString GetSkinFolder() override;
	virtual CDuiString GetSkinFile() override;
	virtual LPCTSTR GetWindowClassName(void) const override;
};


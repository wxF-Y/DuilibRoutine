#pragma once

#include "UILib.h"
using DuiLib::WindowImplBase;
using  DuiLib::CDuiString;

class MainWndFrame :
	public WindowImplBase
{
public:
	// Í¨¹ý WindowImplBase ¼Ì³Ð
	virtual CDuiString GetSkinFolder() override;
	virtual CDuiString GetSkinFile() override;
	virtual LPCTSTR GetWindowClassName(void) const override;
};


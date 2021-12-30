#pragma once
#include "UIlib.h"
using namespace DuiLib;


class MainWndFrame :
	public DuiLib::WindowImplBase
{
public:
	LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
};


#pragma once
#include "UILib.h"
using DuiLib::WindowImplBase;
using DuiLib::CDuiString;

class MainWndFrame;

class SkinWndFrame :
	public WindowImplBase
{
public:
	SkinWndFrame(MainWndFrame* main_frame, RECT rcParentWindow);

	virtual void InitWindow() override;
	// Í¨¹ý WindowImplBase ¼Ì³Ð
	virtual CDuiString GetSkinFolder() override;
	virtual CDuiString GetSkinFile() override;
	virtual LPCTSTR GetWindowClassName(void) const override;
private:
	MainWndFrame* _main_frame;
	RECT m_main_frame_Rect;

};


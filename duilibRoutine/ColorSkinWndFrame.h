#pragma once

#include "UILib.h"
class MainWndFrame;
using DuiLib::WindowImplBase;
using DuiLib::CDuiString;
using  DuiLib::TNotifyUI;

class ColorSkinWndFrame :
	public WindowImplBase
{
public:

	ColorSkinWndFrame(MainWndFrame* main_frame, RECT rcParentWindow);

	LPCTSTR GetWindowClassName() const;

	virtual void OnFinalMessage(HWND hWnd);

	void Notify(TNotifyUI& msg);

	virtual void InitWindow();

	virtual CDuiString GetSkinFile();

	virtual CDuiString GetSkinFolder();

	virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

private:
	RECT parent_window_rect_;

	MainWndFrame* main_frame_;
};


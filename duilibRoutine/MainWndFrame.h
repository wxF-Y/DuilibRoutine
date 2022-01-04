#pragma once
#include "UIlib.h"
using namespace DuiLib;




class MainWndFrame :
	public DuiLib::WindowImplBase
{
public:
	MainWndFrame();
	LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFile();
	virtual CDuiString GetSkinFolder();
	virtual void InitWindow();//获取控件对象
	virtual void Notify(TNotifyUI& msg);//处理触发事件
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);//向系统请求终止
private:
	CControlUI* _btn_min;
	CControlUI* _btn_max;
	CControlUI* _btn_restore;
	CControlUI* _btn_shutdown;

};


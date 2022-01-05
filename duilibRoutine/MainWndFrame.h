#pragma once
#include "UIlib.h"
using namespace DuiLib;

#include "LoginWndFrame.h"


class MainWndFrame :
	public DuiLib::WindowImplBase
{
public:
	MainWndFrame();
	virtual CDuiString GetSkinFolder()  override;
	virtual CDuiString GetSkinFile() override;
	virtual LPCTSTR GetWindowClassName(void) const override;
	virtual void InitWindow();//获取控件对象
	virtual void Notify(TNotifyUI& msg);//处理触发事件
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);//向系统请求终止
private:
	CControlUI* _btn_min;
	CControlUI* _btn_max;
	CControlUI* _btn_restore;
	CControlUI* _btn_shutdown;

	//标题栏控件
	CControlUI* _btn_personal;
	CControlUI* _btn_skin;


	//子窗口
	LoginWndFrame* _loginWndFrame;
};


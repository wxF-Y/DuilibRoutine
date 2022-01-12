#pragma once
#include "UIlib.h"
using DuiLib::WindowImplBase;
using DuiLib::CDuiString;
using DuiLib::CTabLayoutUI;
using DuiLib::CControlUI;
using DuiLib::COptionUI;
using DuiLib::CDialogBuilder;
using DuiLib::CButtonUI;

#include "LoginWndFrame.h"

#include <map>

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

	void setBKColor(DWORD dwBackColor);

	void HandleOptionEvent(TNotifyUI & msg);
	void HandleBasicBtnEvEnt(TNotifyUI& msg);
	void HandlePersonalEvent(TNotifyUI& msg);
private:

	CControlUI* CreateNewTab();//以当前选中option -- _curSelectedOption的name进行创建tab.在创建之前一定要先初始化_curSelectedOption成员变量

#if defined _UNICODE
	std::map<std::wstring, int> m_optionMapToTab;
#else
	std::map<std::string, int> m_optionMapToTab;
#endif
	
	CDialogBuilder* _builder;

	//基本窗口控件
	CButtonUI* _btn_min;
	CButtonUI* _btn_max;
	CButtonUI* _btn_restore;
	CButtonUI* _btn_shutdown;


	//标题栏控件
	CButtonUI* _btn_personal;
	CButtonUI* _btn_skin;

	//侧边option和tab内容区
	CTabLayoutUI* _tabLayout;
	COptionUI* _curSelectedOption;

	//子窗口
	LoginWndFrame* _loginWndFrame;
};


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
	virtual void InitWindow();//��ȡ�ؼ�����
	virtual void Notify(TNotifyUI& msg);//�������¼�
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);//��ϵͳ������ֹ
private:
	CControlUI* _btn_min;
	CControlUI* _btn_max;
	CControlUI* _btn_restore;
	CControlUI* _btn_shutdown;

};


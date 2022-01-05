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
	virtual void InitWindow();//��ȡ�ؼ�����
	virtual void Notify(TNotifyUI& msg);//�������¼�
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);//��ϵͳ������ֹ
private:
	CControlUI* _btn_min;
	CControlUI* _btn_max;
	CControlUI* _btn_restore;
	CControlUI* _btn_shutdown;

	//�������ؼ�
	CControlUI* _btn_personal;
	CControlUI* _btn_skin;


	//�Ӵ���
	LoginWndFrame* _loginWndFrame;
};


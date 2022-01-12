// duilibRoutine.cpp : 定义应用程序的入口点。
//

#include "framework.h"
#include "duilibRoutine.h"

#include "MainWndFrame.h"

#include "UIlib.h"
using DuiLib::CPaintManagerUI;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);


#if defined(WIN32) && !defined(UNDER_CE)
	HRESULT Hr = ::CoInitialize(NULL);
#else
	HRESULT Hr = ::CoInitializeEx(NULL, COINIT_MULTITHREADED);
#endif
	if (FAILED(Hr)) return 0;

	MainWndFrame* mainWnd = new (std::nothrow)MainWndFrame;
	if (mainWnd == NULL) return 0;

#if defined(WIN32) && !defined(UNDER_CE)
	mainWnd->Create(NULL, mainWnd->GetWindowClassName(), UI_WNDSTYLE_FRAME | WS_CLIPCHILDREN, WS_EX_WINDOWEDGE, 0, 0, 600, 800);
#else
	mainWnd->Create(NULL, mainWnd->GetWindowClassName(), UI_WNDSTYLE_FRAME, WS_EX_TOPMOST, 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
#endif

	mainWnd->CenterWindow();
	ShowWindow(*mainWnd, SW_SHOW);

	CPaintManagerUI::MessageLoop();

	return 0;
}

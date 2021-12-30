#include "MainWndFrame.h"

LPCTSTR MainWndFrame::GetWindowClassName() const
{
	return _T("Wangxi");
}

CDuiString MainWndFrame::GetSkinFile()
{
	return _T("skin.xml");
}

CDuiString MainWndFrame::GetSkinFolder()
{
	return CPaintManagerUI::GetInstancePath();
}

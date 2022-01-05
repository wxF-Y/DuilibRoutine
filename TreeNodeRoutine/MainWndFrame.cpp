#include "MainWndFrame.h"

CDuiString MainWndFrame::GetSkinFolder()
{
	return _T("TreeNodeRoutine\\");
}

CDuiString MainWndFrame::GetSkinFile()
{
	return _T("main_frame.xml");
}

LPCTSTR MainWndFrame::GetWindowClassName(void) const
{
	return _T("TreeNode");
}

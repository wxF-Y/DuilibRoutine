#include "SkinWndFrame.h"

#include "MainWndFrame.h"

SkinWndFrame::SkinWndFrame(MainWndFrame * main_frame, RECT rcParentWindow)
	:_main_frame{main_frame}, m_main_frame_Rect{rcParentWindow}
{
	Create(main_frame->GetHWND(), _T("skinChange"), WS_POPUP, WS_EX_TOOLWINDOW, 0, 0);
	ShowWindow(true);
}

void SkinWndFrame::InitWindow()
{
	SIZE size = m_PaintManager.GetInitSize();//获得控件的宽高,cx宽,cy高
	MoveWindow(m_hWnd, m_main_frame_Rect.right - size.cx, m_main_frame_Rect.top, size.cx, size.cy, FALSE);//移动窗口,(窗口的左边，上边，宽，高)
}

CDuiString SkinWndFrame::GetSkinFolder()
{
	return _T("theme");
}

CDuiString SkinWndFrame::GetSkinFile()
{
	return _T("skin.xml");
}

LPCTSTR SkinWndFrame::GetWindowClassName(void) const
{
	return _T("skinChange");
}

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
	SIZE size = m_PaintManager.GetInitSize();//��ÿؼ��Ŀ��,cx��,cy��
	MoveWindow(m_hWnd, m_main_frame_Rect.right - size.cx, m_main_frame_Rect.top, size.cx, size.cy, FALSE);//�ƶ�����,(���ڵ���ߣ��ϱߣ�����)
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

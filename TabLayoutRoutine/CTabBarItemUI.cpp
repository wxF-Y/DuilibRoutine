#include "framework.h"
#include "CTabBarItemUI.h"

#include "CTabBarUI.h"


CTabBarItemUI::CTabBarItemUI() :m_uCloseBtnState(0), m_bHaveClose(FALSE)
{
}


CTabBarItemUI::~CTabBarItemUI()
{
}


LPCTSTR CTabBarItemUI::GetClass() const
{
	return _T("TabBarItemUI");
}

LPVOID CTabBarItemUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcsicmp(pstrName, _T("TabBarItem")) == 0) return static_cast<CTabBarItemUI*>(this);
	return COptionUI::GetInterface(pstrName);
}

void CTabBarItemUI::SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue)
{
	//icon
	if (_tcsicmp(pstrName, _T("iconsize")) == 0)
	{
		SIZE cxySize = { 0 };
		LPTSTR pstr = NULL;
		cxySize.cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);
		cxySize.cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);
		SetIconSize(cxySize);
	}
	else if (_tcsicmp(pstrName, _T("iconpadding")) == 0)
	{
		RECT rcIconPadding = { 0 };
		LPTSTR pstr = NULL;
		rcIconPadding.left = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);
		rcIconPadding.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);
		rcIconPadding.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);
		rcIconPadding.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);
		SetIconPadding(rcIconPadding);
	}
	else if (_tcsicmp(pstrName, _T("iconimage")) == 0) SetIconImage(pstrValue);
	else if (_tcsicmp(pstrName, _T("selectediconimage")) == 0) SetSelectedIconImage(pstrValue);
	
	//close
	else if (_tcsicmp(pstrName, _T("closesize")) == 0)
	{
		SIZE cxySize = { 0 };
		LPTSTR pstr = NULL;
		cxySize.cx = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);
		cxySize.cy = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);
		SetCloseSize(cxySize);
	}
	else if (_tcsicmp(pstrName, _T("closepadding")) == 0)
	{
		RECT rcPadding = { 0 };
		LPTSTR pstr = NULL;
		rcPadding.left = _tcstol(pstrValue, &pstr, 10);  ASSERT(pstr);
		rcPadding.top = _tcstol(pstr + 1, &pstr, 10);    ASSERT(pstr);
		rcPadding.right = _tcstol(pstr + 1, &pstr, 10);  ASSERT(pstr);
		rcPadding.bottom = _tcstol(pstr + 1, &pstr, 10); ASSERT(pstr);
		SetClosePadding(rcPadding);
	}
	else if (_tcsicmp(pstrName, _T("closeimage")) == 0) SetCloseImage(pstrValue);
	else if (_tcsicmp(pstrName, _T("closehotimage")) == 0) SetCloseHotImage(pstrValue);
	else if (_tcsicmp(pstrName, _T("closepushimage")) == 0) SetClosePushImage(pstrValue);
	else if (_tcsicmp(pstrName, _T("haveclose")) == 0)
	{
		SetHaveClose(_tcsicmp(pstrValue, _T("true")) == 0);
	}
	else COptionUI::SetAttribute(pstrName, pstrValue);
}

void CTabBarItemUI::PaintStatusImage(HDC hDC)
{
	COptionUI::PaintStatusImage(hDC);

	//icon
	auto i = IsSelected();
	if (IsSelected())
	{
		if (!m_sSelectedIconImage.IsEmpty())
		{
			DrawIconImage(hDC, (LPCTSTR)m_sSelectedIconImage);
		}
	}
	else
	{
		if (!m_sIconImage.IsEmpty())
		{
			DrawIconImage(hDC, (LPCTSTR)m_sIconImage);
		}
	}

	//close
	if (m_bHaveClose)
	{
		if (IsSelected() || (m_uButtonState & UISTATE_HOT) != 0)
		{

			if ((m_uCloseBtnState & UISTATE_PUSHED) != 0 && !m_sClosePushImage.IsEmpty())
			{
				//OutputDebugString(L"m_sClosePushImage\r\n");
				DrawCloseImage(hDC, (LPCTSTR)m_sClosePushImage);
			}
			else if ((m_uCloseBtnState & UISTATE_HOT) != 0 && !m_sCloseHotImage.IsEmpty())
			{
				//OutputDebugString(L"m_sCloseHotImage\r\n");
				DrawCloseImage(hDC, (LPCTSTR)m_sCloseHotImage);
			}
			else
			{
				if (!m_sCloseImage.IsEmpty())
				{
					//OutputDebugString(L"m_sCloseImage\r\n");
					DrawCloseImage(hDC, (LPCTSTR)m_sCloseImage);
				}
			}
		}
	}

}

void CTabBarItemUI::DoEvent(DuiLib::TEventUI& event)
{
	if (!IsMouseEnabled() && event.Type > DuiLib::UIEVENT__MOUSEBEGIN && event.Type < DuiLib::UIEVENT__MOUSEEND) {
		if (m_pParent != NULL) m_pParent->DoEvent(event);
		else COptionUI::DoEvent(event);
		return;
	}

	if (event.Type == DuiLib::UIEVENT_BUTTONDOWN)
	{
		int x = event.ptMouse.x;
		m_ClickedInnerDistance.left = x - m_rcItem.left;
		m_ClickedInnerDistance.right = m_rcItem.right - x;
	}


	if (m_bHaveClose)
	{
		RECT rcClose;
		GetCloseRect(rcClose);//获取关闭按钮的矩形

		if (event.Type == DuiLib::UIEVENT_BUTTONDOWN || event.Type == DuiLib::UIEVENT_DBLCLICK)
		{
			if (::PtInRect(&rcClose, event.ptMouse))//判断鼠标是否在关闭按钮的矩形框中
			{
				m_uCloseBtnState |= UISTATE_PUSHED | UISTATE_CAPTURED;
				//OutputDebugString(L"BUTTONDOWN\r\n");
				Invalidate();
			}
		}
		else if (event.Type == DuiLib::UIEVENT_MOUSEMOVE)
		{
			if ((m_uCloseBtnState & UISTATE_CAPTURED ) != 0)
			{
				//OutputDebugString(L"MOUSEMOVE-CAPTURED\r\n");

				if (::PtInRect(&rcClose, event.ptMouse))
					m_uCloseBtnState |= UISTATE_PUSHED;
				else
					m_uCloseBtnState &= ~UISTATE_PUSHED;
				Invalidate();
			}
			else if (::PtInRect(&rcClose, event.ptMouse))
			{
				m_uCloseBtnState |= UISTATE_HOT;
				Invalidate();
			}
			else
			{
				m_uCloseBtnState &= ~UISTATE_HOT;
				Invalidate();
			}
		}
		else if (event.Type == DuiLib::UIEVENT_BUTTONUP)
		{
			if ((m_uCloseBtnState & UISTATE_CAPTURED) != 0)
			{
				if (::PtInRect(&rcClose, event.ptMouse))
				{
					m_pManager->SendNotify(this, DUI_MSGTYPE_OPTIONTABCLOSE, 0, 0);
				}
				m_uCloseBtnState &= ~(UISTATE_PUSHED | UISTATE_CAPTURED);
				Invalidate();
			}
			else if (::PtInRect(&rcClose, event.ptMouse))
			{

			}
		}
		else if (event.Type == DuiLib::UIEVENT_MOUSEENTER)
		{
			if (::PtInRect(&rcClose, event.ptMouse))
			{
				m_uCloseBtnState |= UISTATE_HOT;
				Invalidate();
			}
		}
		else if (event.Type == DuiLib::UIEVENT_MOUSELEAVE)
		{
			m_uCloseBtnState &= ~UISTATE_HOT;
			Invalidate();
		}
	}

	if (event.Type == DuiLib::UIEVENT_BUTTONDOWN)
	{
		if (::PtInRect(&m_rcItem, event.ptMouse) && IsEnabled())
		{
			m_uButtonState |= UISTATE_PUSHED | UISTATE_CAPTURED;
			Invalidate();
			//if (IsRichEvent()) m_pManager->SendNotify(this, DUI_MSGTYPE_BUTTONDOWN);

			RECT rcClose;
			GetCloseRect(rcClose);
			if (::PtInRect(&m_rcItem, event.ptMouse) && !::PtInRect(&rcClose, event.ptMouse))
			{
				Activate();
			}

			m_bIgnoreDrag = true;
			m_ptLButtonDownMouse = event.ptMouse;
			m_ptLastMouse = event.ptMouse;
			m_rcNewPos = m_rcItem;
			if (m_pManager)
			{
				m_pManager->RemovePostPaint(this);
				m_pManager->AddPostPaint(this);
			}

		}
		return;
	}
	else if (event.Type == DuiLib::UIEVENT_MOUSEMOVE)
	{
		if ((m_uButtonState & UISTATE_CAPTURED) != 0)
		{

			auto continer = static_cast<CTabBarUI*>(GetParent());
			RECT parentPos = continer->GetPos();
			auto add_btn = continer->FindSubControl(_T("btn_add_tab"));
			RECT add_btn_pos = add_btn->GetPos();

			if ( (event.ptMouse.x - m_ClickedInnerDistance.left) < parentPos.left || (event.ptMouse.x + m_ClickedInnerDistance.right) >  add_btn_pos.left) return;

			LONG cx = event.ptMouse.x - m_ptLastMouse.x;
			LONG cy = event.ptMouse.y - m_ptLastMouse.y;

			m_ptLastMouse = event.ptMouse;

			RECT rcCurPos = m_rcNewPos;

			rcCurPos.left += cx;
			rcCurPos.right += cx;
			rcCurPos.top += cy;
			rcCurPos.bottom += cy;

			//将当前拖拽块的位置 和 当前拖拽块的前一时刻的位置，刷新
			DuiLib::CDuiRect rcInvalidate = m_rcNewPos;
			m_rcNewPos = rcCurPos;
			rcInvalidate.Join(m_rcNewPos);
			if (m_pManager) m_pManager->Invalidate(rcInvalidate);

			NeedParentUpdate();
			return;
		}
	}
	if (event.Type == DuiLib::UIEVENT_BUTTONUP)
	{
		if ((m_uButtonState & UISTATE_CAPTURED) != 0)
		{
			m_uButtonState &= ~(UISTATE_PUSHED | UISTATE_CAPTURED);
			Invalidate();

			CTabBarUI* pParent = static_cast<CTabBarUI*>(m_pParent);
			if (pParent)
			{
				pParent->DoDragEnd(this, m_ptLastMouse);
			}

			if (m_pManager)
			{
				m_pManager->RemovePostPaint(this);
				m_pManager->Invalidate(m_rcNewPos);
			}
			NeedParentUpdate();

			m_bFirstDrag = true;
		}
		return;
	}

	COptionUI::DoEvent(event);
}

void CTabBarItemUI::DoPostPaint(HDC hDC, const RECT& rcPaint)
{
	if ((m_uButtonState & UISTATE_CAPTURED) != 0)
	{
		if (m_bIgnoreDrag && abs(m_ptLastMouse.x - m_ptLButtonDownMouse.x) < 15)
		{
			return;
		}
		m_bIgnoreDrag = false;

		CTabBarUI* pParent = static_cast<CTabBarUI*>(m_pParent);
		if (!pParent) return;

		if (m_bFirstDrag)
		{
			pParent->DoDragBegin(this);
			m_bFirstDrag = false;
			return;
		}

		DuiLib::CDuiRect rcParent = m_pParent->GetPos();
		RECT rcUpdate = { 0 };
		rcUpdate.left = m_rcNewPos.left < rcParent.left ? rcParent.left : m_rcNewPos.left;
		rcUpdate.top = m_rcItem.top < rcParent.top ? rcParent.top : m_rcItem.top;
		rcUpdate.right = m_rcNewPos.right > rcParent.right ? rcParent.right : m_rcNewPos.right;
		rcUpdate.bottom = m_rcItem.bottom > rcParent.bottom ? rcParent.bottom : m_rcItem.bottom;

		//DuiLib::CRenderEngine::DrawColor(hDC, rcUpdate, 0xFFFFFFFF);//拖动的矩形块
		//CRenderEngine::DrawText(m_pManager->GetPaintDC(), m_pManager, rcText, sText, 0, m_iFont, DT_CALCRECT | m_uTextStyle & ~DT_RIGHT & ~DT_CENTER);
		DuiLib::CRenderEngine::DrawText(hDC, m_pManager, rcUpdate, GetText(), GetTextColor(), GetFont(), DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		

		pParent->DoDragMove(this, rcUpdate);

	}
}

SIZE CTabBarItemUI::GetIconSize() const
{
	//if (m_pManager != NULL) return m_pManager->GetDPIObj()->Scale(m_cxyIconSize);
	return m_cxyIconSize;
}

void CTabBarItemUI::SetIconSize(SIZE cxySize)
{
	m_cxyIconSize = cxySize;
	Invalidate();
}

RECT CTabBarItemUI::GetIconPadding() const
{
	//if (m_pManager != NULL) return m_pManager->GetDPIObj()->Scale(m_rcIconPadding);
	return m_rcIconPadding;
}

void CTabBarItemUI::SetIconPadding(RECT rcIconPadding)
{
	m_rcIconPadding = rcIconPadding;
	NeedParentUpdate();
}

LPCTSTR CTabBarItemUI::GetIconImage() const
{
	return m_sIconImage;
}

void CTabBarItemUI::SetIconImage(LPCTSTR pStrImage)
{
	m_sIconImage = pStrImage;
	Invalidate();
}

LPCTSTR CTabBarItemUI::GetSelectedIconImage() const
{
	return m_sSelectedIconImage;
}

void CTabBarItemUI::SetSelectedIconImage(LPCTSTR pStrImage)
{
	m_sSelectedIconImage = pStrImage;
	Invalidate();
}

SIZE CTabBarItemUI::GetCloseSize() const
{
	//if (m_pManager != NULL) return m_pManager->GetDPIObj()->Scale(m_cxyCloseSize);
	return m_cxyCloseSize;
}

void CTabBarItemUI::SetCloseSize(SIZE cxySize)
{
	m_cxyCloseSize = cxySize;
	Invalidate();
}

RECT CTabBarItemUI::GetClosePadding() const
{
	//if (m_pManager != NULL) return m_pManager->GetDPIObj()->Scale(m_rcClosePadding);
	return m_rcClosePadding;
}

void CTabBarItemUI::SetClosePadding(RECT rcPadding)
{
	m_rcClosePadding = rcPadding;
	NeedParentUpdate();
}

LPCTSTR CTabBarItemUI::GetCloseImage() const
{
	return m_sCloseImage;
}

void CTabBarItemUI::SetCloseImage(LPCTSTR pStrImage)
{
	m_sCloseImage = pStrImage;
	Invalidate();
}

LPCTSTR CTabBarItemUI::GetCloseHotImage() const
{
	return m_sCloseHotImage;
}

void CTabBarItemUI::SetCloseHotImage(LPCTSTR pStrImage)
{
	m_sCloseHotImage = pStrImage;
	Invalidate();
}

LPCTSTR CTabBarItemUI::GetClosePushImage() const
{
	return m_sClosePushImage;
}

void CTabBarItemUI::SetClosePushImage(LPCTSTR pStrImage)
{
	m_sClosePushImage = pStrImage;
	Invalidate();
}

void CTabBarItemUI::GetIconRect(RECT &rc)
{
	memset(&rc, 0x00, sizeof(rc));

	RECT rcIconPadding = GetIconPadding();
	SIZE szIconSize = GetIconSize();

	int nHeight = m_rcItem.bottom - m_rcItem.top;
	rc.left = m_rcItem.left + rcIconPadding.left;
	rc.top = m_rcItem.top + (nHeight - szIconSize.cy) / 2;
	rc.right = rc.left + szIconSize.cx;
	rc.bottom = rc.top + szIconSize.cy;
}

BOOL CTabBarItemUI::DrawIconImage(HDC hDC, LPCTSTR pStrImage, LPCTSTR pStrModify /*= NULL*/)
{
	RECT rcIcon;
	GetIconRect(rcIcon);
	return DuiLib::CRenderEngine::DrawImageString(hDC, m_pManager, rcIcon, m_rcPaint, pStrImage, pStrModify);
	return TRUE;
}

void CTabBarItemUI::GetCloseRect(RECT &rc)
{
	memset(&rc, 0x00, sizeof(rc));

	RECT rcPadding = GetClosePadding();
	SIZE szSize = GetCloseSize();

	int nHeight = m_rcItem.bottom - m_rcItem.top;
	rc.top = m_rcItem.top + (nHeight - szSize.cy) / 2;
	rc.right = m_rcItem.right - rcPadding.right;
	rc.left = rc.right - szSize.cx;
	rc.bottom = rc.top + szSize.cy;
}

BOOL CTabBarItemUI::DrawCloseImage(HDC hDC, LPCTSTR pStrImage, LPCTSTR pStrModify /*= NULL*/)
{
	RECT rcClose;
	GetCloseRect(rcClose);

	return DuiLib::CRenderEngine::DrawImageString(hDC, m_pManager, rcClose, m_rcPaint, pStrImage, pStrModify);
	return TRUE;
}

BOOL CTabBarItemUI::GetHaveClose()
{
	return m_bHaveClose;
}

void CTabBarItemUI::SetHaveClose(BOOL bHaveClose)
{
	m_bHaveClose = bHaveClose;
}


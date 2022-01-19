#include "framework.h"
#include "CTabBarUI.h"


#include "CTabBarItemUI.h"
#include <string>

CTabBarUI::CTabBarUI()
{
	SetAttribute(_T("name"),_T("tabs_layout"));
	SetAttribute(_T("minwidth"), _T("247"));
	SetAttribute(_T("fillwidth"), _T("true"));
	SetAttribute(_T("bordersize"), _T("0"));
	SetAttribute(_T("bordercolor"), _T("0xFF000000"));
	//SetAttribute(_T(""), _T(""));

	m_pZhanWeiOption = new CTabBarItemUI();
	m_pZhanWeiOption->SetMaxWidth(0);
	//m_pZhanWeiOption->SetForeColor(0x000000ff);
	m_pZhanWeiOption->SetEnabled(false);

	Add(m_pZhanWeiOption);


	btn_add_tab_ = new (std::nothrow)DuiLib::CButtonUI();
	ASSERT(btn_add_tab_);
	if (!btn_add_tab_)
		return;

	btn_add_tab_->SetAttribute(_T("name"), _T("btn_add_tab"));
	btn_add_tab_->SetAttribute(_T("text"), _T("+"));
	btn_add_tab_->SetAttribute(_T("width"), _T("20"));
	btn_add_tab_->SetAttribute(_T("textcolor"), _T("0XFFA7B8C1"));
	btn_add_tab_->SetAttribute(_T("align"), _T("vcenter"));
	btn_add_tab_->SetAttribute(_T("pushedtextcolor"), _T("0XFF000000"));
	btn_add_tab_->SetAttribute(_T("hottextcolor"), _T("0XFF000000"));
	btn_add_tab_->SetAttribute(_T("font"), _T("5"));

	Add(btn_add_tab_);
}


CTabBarUI::~CTabBarUI()
{
}

LPCTSTR CTabBarUI::GetClass() const
{
	return _T("TabBarUI");
}

LPVOID CTabBarUI::GetInterface(LPCTSTR pstrName)
{
	if (_tcsicmp(pstrName, _T("TabBar")) == 0) return static_cast<CTabBarUI*>(this);
	return CHorizontalLayoutUI::GetInterface(pstrName);
}

CTabBarItemUI* CTabBarUI::AddItem()
{

	CTabBarItemUI* pTab = new CTabBarItemUI();

	//option整体
	pTab->SetName(_T("tab_item_opt"));
	pTab->SetGroup(_T("switch"));
	pTab->SetNormalImage(_T("file='img\\tab_bg.png' source='0,0,246,36'"));
	pTab->SetHotImage(_T("file='img\\tab_bg.png' source='246,0,492,36'"));
	pTab->SetSelectedImage(_T("file='img\\tab_bg.png' source='492,0,738,36'"));
	pTab->SetMaxWidth(246);
	pTab->SetAttribute(_T("endellipsis"), _T("true"));
	pTab->SetAttribute(_T("height"), _T("36"));

	int add_index = GetItemIndex(btn_add_tab_);
	if (add_index == 1) 	pTab->SetAttribute(_T("selected"), _T("true"));
#if defined _UNICODE
	std::wstring index = L"我的电脑" + std::to_wstring(add_index);
#else
	std::string index = "我的电脑" + std::to_string(add_index);
#endif
	//SetAttribute(_T(""), _T(""));

	//字体
	pTab->SetAttribute(_T("text"), (LPCTSTR)index.data());
	pTab->SetAttribute(_T("selectedtextcolor"), _T("#ff000000"));
	pTab->SetAttribute(_T("align"), _T("left"));
	pTab->SetAttribute(_T("textpadding"), _T("45"));
	pTab->SetAttribute(_T("font"), _T("0"));

	//icon
	pTab->SetAttribute(_T("iconsize"), _T("16,16"));
	pTab->SetAttribute(_T("iconpadding"), _T("16"));
	pTab->SetAttribute(_T("iconimage"), _T("file='img\\default_tab_icon.png'"));
	pTab->SetAttribute(_T("selectediconimage"), _T("file='img\\default_tab_icon.png'"));

	//close
	pTab->SetAttribute(_T("haveclose"), _T("true"));
	pTab->SetAttribute(_T("closesize"), _T("17,17"));
	pTab->SetAttribute(_T("closepadding"), _T("0,0,10,0"));
	pTab->SetAttribute(_T("closeimage"), _T("file='img\\btn_tab_close.png' source='0,0,17,17'"));
	pTab->SetAttribute(_T("closehotimage"), _T("file='img\\btn_tab_close.png' source='17,0,34,17'"));
	pTab->SetAttribute(_T("closepushimage"), _T("file='img\\btn_tab_close.png' source='34,0,51,17'"));

	pTab->OnNotify += MakeDelegate(this, &CTabBarUI::OnItemClose);

	if (AddAt(pTab,add_index))
	{
		return pTab;
	}
	return NULL;
}

CTabBarItemUI* CTabBarUI::GetPrevTab(CTabBarItemUI *pTab)
{
	if (!pTab)
	{
		return NULL;
	}

	for (int it = 0; it < m_items.GetSize(); it++)
	{
		if (static_cast<CTabBarItemUI*>(m_items[it]) == pTab)
		{
			int nCurIndex = GetItemIndex(pTab);
			if (nCurIndex == 0)
			{
				return NULL;
			}
			auto pItem = static_cast<CTabBarItemUI*>(m_items[nCurIndex - 1]);
			if (_tcsicmp(pItem->GetClass(), _T("tabbaritemui")) == 0)
			{
				return pItem;
			}
		}
	}
	return NULL;
}

CTabBarItemUI* CTabBarUI::GetNextTab(CTabBarItemUI *pTab)
{
	if (!pTab)
	{
		return NULL;
	}

	for (int it = 0; it < m_items.GetSize(); it++)
	{
		if (static_cast<CTabBarItemUI*>(m_items[it]) == pTab)
		{
			int nCurIndex = GetItemIndex(pTab);
			if (nCurIndex == m_items.GetSize() - 2)
			{
				return NULL;
			}
			auto pItem = static_cast<CTabBarItemUI*>(m_items[nCurIndex + 1]);
			if (_tcsicmp(pItem->GetClass(), _T("tabbaritemui")) == 0)
			{
				return pItem;
			}
		}
	}
	return NULL;
}

void CTabBarUI::DoDragBegin(CTabBarItemUI *pTab)
{
	if (!pTab)
	{
		return;
	}

	int index = GetItemIndex(pTab);
	if (index < 0)
	{
		return;
	}

	int index_blue = GetItemIndex(m_pZhanWeiOption);
	if (index_blue < 0)
	{
		return;
	}

	m_pDragOption = pTab;

	m_items.SetAt(index, m_pZhanWeiOption);
	m_items.SetAt(index_blue, m_pDragOption);

	m_pZhanWeiOption->SetMaxWidth(m_pDragOption->GetWidth());
	m_pDragOption->SetMaxWidth(0);
}

void CTabBarUI::DoDragMove(CTabBarItemUI *pTab, const RECT& rcPaint)
{
	if (m_pDragOption != pTab)
	{
		return;
	}
	DUITRACE(pTab->GetText());
	int x = rcPaint.left + (rcPaint.right - rcPaint.left) / 2;
	int y = rcPaint.top + (rcPaint.bottom - rcPaint.top) / 2;
	//auto rc = m_rcItem;
	//if (x < m_rcItem.left || x > m_rcItem.right)
	//{
	//	return;
	//}

	int index = -1;
	for (int it1 = 0; it1 < m_items.GetSize(); it1++)
	{
		CControlUI* pControl = static_cast<CControlUI*>(m_items[it1]);
		if (!pControl) continue;
		if (_tcsicmp(pControl->GetClass(), _T("tabbaritemui")) == 0 && ::PtInRect(&pControl->GetPos(), { x, y }))
		{
			index = it1;
			break;
		}
	}

	if (index == -1)
	{
		return;
	}

	CTabBarItemUI *pOption = static_cast<CTabBarItemUI*>(GetItemAt(index));
	int index_blue = GetItemIndex(m_pZhanWeiOption);

	m_items.SetAt(index, m_pZhanWeiOption);
	m_items.SetAt(index_blue, pOption);

}

void CTabBarUI::DoDragEnd(CTabBarItemUI *pTab, const POINT& Pt)
{
	if (m_pDragOption != pTab)
	{
		return;
	}

	int index = GetItemIndex(m_pDragOption);
	if (index < 0)
	{
		return;
	}

	int index_blue = GetItemIndex(m_pZhanWeiOption);
	if (index_blue < 0)
	{
		return;
	}

	m_items.SetAt(index, m_pZhanWeiOption);
	m_items.SetAt(index_blue, m_pDragOption);

	m_pDragOption->SetMaxWidth(m_pZhanWeiOption->GetWidth());
	m_pZhanWeiOption->SetMaxWidth(0);
}

bool CTabBarUI::OnItemClose(void* param)
{
	if (!param) return false;

	DuiLib::TNotifyUI* msg = (DuiLib::TNotifyUI*)param;
	if (msg->sType == DUI_MSGTYPE_OPTIONTABCLOSE)
	{
		if (!msg->pSender)
		{
			return false;
		}

		CTabBarItemUI *pItem = static_cast<CTabBarItemUI *>(msg->pSender);
		CTabBarItemUI *pNearTab = NULL;

		if (pItem->IsSelected())
		{
			pNearTab = GetPrevTab(pItem);
			if (!pNearTab)
			{
				pNearTab = GetNextTab(pItem);
			}
			if (pNearTab)
			{
				pNearTab->Selected(true);
			}
		}
		m_pManager->SendNotify(pItem, DUI_MSGTYPE_TABBARCLOSEITEM, 0, 0);

		Remove(pItem);
	}
	return true;
}

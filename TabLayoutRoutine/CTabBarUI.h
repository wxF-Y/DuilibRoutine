#pragma once

#define DUI_MSGTYPE_TABBARCLOSEITEM 		   	(_T("tabbarcloseitem"))

class CTabBarItemUI;


class CTabBarUI :
		public DuiLib::CHorizontalLayoutUI
	{
	public:
		CTabBarUI();
		~CTabBarUI();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		//Ìí¼ÓÒ»¸ö
		CTabBarItemUI* AddItem();

		CTabBarItemUI* GetPrevTab(CTabBarItemUI *pTab);
		CTabBarItemUI* GetNextTab(CTabBarItemUI *pTab);

		//drag
		void DoDragBegin(CTabBarItemUI *pTab);
		void DoDragMove(CTabBarItemUI *pTab, const RECT& rcPaint);
		void DoDragEnd(CTabBarItemUI *pTab, const POINT& Pt);

		bool OnItemClose(void* param);

	private:
		DuiLib::COptionUI *m_pZhanWeiOption = NULL;
		CTabBarItemUI *m_pDragOption = NULL;

		DuiLib::CButtonUI* btn_add_tab_ = 0;
	};


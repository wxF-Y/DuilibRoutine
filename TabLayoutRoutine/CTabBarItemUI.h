#pragma once

#define DUI_MSGTYPE_OPTIONTABCLOSE 		   	(_T("closeitem_tabbar"))

class CTabBarItemUI :
	public DuiLib::COptionUI
{
public:
	CTabBarItemUI();
	~CTabBarItemUI();

	LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);

	void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	void PaintStatusImage(HDC hDC);
	void DoEvent(DuiLib::TEventUI& event);
	void DoPostPaint(HDC hDC, const RECT& rcPaint);


	void GetIconRect(RECT &rc);
	BOOL DrawIconImage(HDC hDC, LPCTSTR pStrImage, LPCTSTR pStrModify = NULL);
	void GetCloseRect(RECT &rc);
	BOOL DrawCloseImage(HDC hDC, LPCTSTR pStrImage, LPCTSTR pStrModify = NULL);

	BOOL GetHaveClose();
	void SetHaveClose(BOOL bHaveClose);

	SIZE GetIconSize() const;
	void SetIconSize(SIZE cxySize);
	RECT GetIconPadding() const;
	void SetIconPadding(RECT rcIconPadding);
	LPCTSTR GetIconImage() const;
	void SetIconImage(LPCTSTR pStrImage);
	LPCTSTR GetSelectedIconImage() const;
	void SetSelectedIconImage(LPCTSTR pStrImage);

	SIZE GetCloseSize() const;
	void SetCloseSize(SIZE cxySize);
	RECT GetClosePadding() const;
	void SetClosePadding(RECT rcPadding);
	LPCTSTR GetCloseImage() const;
	void SetCloseImage(LPCTSTR pStrImage);
	LPCTSTR GetCloseHotImage() const;
	void SetCloseHotImage(LPCTSTR pStrImage);
	LPCTSTR GetClosePushImage() const;
	void SetClosePushImage(LPCTSTR pStrImage);

protected:
	BOOL m_bHaveClose;

	RECT m_ClickedInnerDistance;//��¼��갴��ʱ����item�ڲ��ľ���.��ʹ��left��right

	RECT m_rcIconPadding;
	SIZE m_cxyIconSize;

	RECT m_rcClosePadding;
	SIZE m_cxyCloseSize;

	DuiLib::CDuiString m_sIconImage;
	DuiLib::CDuiString m_sSelectedIconImage;

	DuiLib::CDuiString m_sCloseImage;
	DuiLib::CDuiString m_sCloseHotImage;
	DuiLib::CDuiString m_sClosePushImage;

private:
	UINT m_uCloseBtnState;

	POINT m_ptLastMouse;
	POINT m_ptLButtonDownMouse;
	RECT m_rcNewPos;

	//�жϿ�ʼ��ק
	bool m_bFirstDrag = true;

	//�ж��Ƿ������ק���״���Ҫ��갴ס��קһ������Ŵ�����ק
	bool m_bIgnoreDrag = true;

};



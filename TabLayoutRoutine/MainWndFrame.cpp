#include "MainWndFrame.h"

#include "resource.h"

#include <string>

MainWndFrame::MainWndFrame()
	:_tabLayout{NULL},_curSelected{NULL},_optionsLayout{NULL},_builder{new CDialogBuilder}
{

}

MainWndFrame::~MainWndFrame()
{
	delete _builder;
}

CDuiString MainWndFrame::GetSkinFolder()
{
	return _T("TabLayout\\");
}

CDuiString MainWndFrame::GetSkinFile()
{
	return _T("skin.xml");
}

LPCTSTR MainWndFrame::GetWindowClassName(void) const
{
	return _T("TabLayoutWindow");
}

void MainWndFrame::Notify(TNotifyUI & msg)
{
	//�ж���Ϣ����
	if (msg.sType == DUI_MSGTYPE_BUTTONDOWN)
	{
		CDuiString strName = msg.pSender->GetName();//��ȡ�����¼��Ŀؼ���
		CControlUI* sender_parent = msg.pSender->GetParent();
		if (!sender_parent) return;
		if (sender_parent->GetName() == _T("OptionsLayout"))
		{
			if (strName == _T("addNewOption"))//����±�ǩ������
			{
				int index_addOption = _optionsLayout->GetItemIndex(msg.pSender);//��ȡ��ǰ����Ӱ�ť��index

#if defined _UNICODE
				std::wstring option_name = L"Option" + std::to_wstring(index_addOption);
				std::wstring option_text = L"Tab" + std::to_wstring(index_addOption);
				std::wstring tab_text = L"This is tab" + std::to_wstring(index_addOption);
#else
				std::string option_name = "Option" + std::to_string(index_addOption);
				std::string option_text = "Tab" + to_string(index_addOption);
				std::string tab_text = "This is tab" + std::to_string(index_addOption);
#endif

//*********************
//xml�ļ������ؼ�
//*********************
				CDialogBuilder _builder;

				CControlUI* new_Option = _builder.Create(_T("option.xml"),(UINT)0, this, &m_PaintManager);
				CControlUI* new_Tab_Layout = _builder.Create(_T("tab.xml"), (UINT)0, this, &m_PaintManager);
				
				if (!new_Option || !new_Tab_Layout) return;
				
				//�����ɹ�����������
				_curSelected->Selected(false);//����ǰѡ��Option����Ϊδѡ��
				_curSelected->SetAttribute(_T("bkcolor"), _T("#00000000"));

				//����Ա����_curSelected����Ϊ�´�����Option
				_curSelected = dynamic_cast<COptionUI*>(new_Option);
				if (!_curSelected) return;
				
				_curSelected->Selected(true);
				_curSelected->SetAttribute(_T("name"), (LPCTSTR)option_name.data());
				_curSelected->SetAttribute(_T("text"), (LPCTSTR)option_text.data());
				_curSelected->SetAttribute(_T("bkcolor"), _T("#FF000000"));

				
				CHorizontalLayoutUI* new_Tab = dynamic_cast<CHorizontalLayoutUI*>(new_Tab_Layout);
				int n = new_Tab->getChildsCount();
				if (!new_Tab) return;
				CControlUI* label = new_Tab->GetItemAt(0);
				label->SetAttribute(_T("text"), (LPCTSTR)tab_text.data());
				_optionsLayout->AddAt(new_Option, index_addOption);
				_tabLayout->AddAt(new_Tab, index_addOption);
				_tabLayout->SelectItem(index_addOption);

//*********************
//�����봴���ؼ�
//*********************
//				//����Option
//				COptionUI* new_Option = new (std::nothrow)COptionUI;
//				if (!new_Option) return;
//
//				_curSelected->Selected(false);
//				_curSelected = new_Option;
//

//				_curSelected->SetAttribute(_T("name"), (LPCTSTR)option_name.data());
//				_curSelected->SetAttribute(_T("text"), (LPCTSTR)option_text.data());
//				_curSelected->SetAttribute(_T("align"), _T("center"));
//				_curSelected->SetAttribute(_T("width"),_T("60"));
//				_curSelected->SetAttribute(_T("height"), _T("30"));
//				_curSelected->SetAttribute(_T("textcolor"), _T("#FF1c1c1c"));
//				_curSelected->SetAttribute(_T("disabledtextcolor"), _T("#FFA7A6AA"));
//				_curSelected->SetAttribute(_T("leftbordersize"), _T("1"));
//				_curSelected->SetAttribute(_T("bordercolor"), _T("#FF000000"));
//				_curSelected->SetAttribute(_T("selectedtextcolor"), _T("#ff96cdcd"));
//				_curSelected->SetAttribute(_T("group"), _T("switch"));
//				_curSelected->SetAttribute(_T("selected"), _T("true"));
//
//				_optionsLayout->AddAt(dynamic_cast<COptionUI*>(new_Option), index_addOption);
//
//				//����tab���ݿؼ�
//				CHorizontalLayoutUI* new_Tab = new (std::nothrow)CHorizontalLayoutUI;
//				CLabelUI* new_Label = new (std::nothrow)CLabelUI;
//				if (!new_Tab || !new_Label) return;
//				new_Label->SetAttribute(_T("bkcolor"), _T("#FFFFFFFF"));
//				new_Label->SetAttribute(_T("text"), (LPCTSTR)tab_text.data());
//
//				//��ӵ�tab�ؼ�
//				new_Tab->Add(new_Label);
//				_tabLayout->Add(new_Tab);
//				_tabLayout->SelectItem(index_addOption);

				return;
			}
			if (strName == _curSelected->GetName())
				return;

			//ȡ��ѡ��֮ǰ��option
			_curSelected->Selected(false);
			_curSelected->SetAttribute(_T("bkcolor"), _T("#00000000"));

			//��������ѡ���option
			_curSelected = dynamic_cast<COptionUI*>(msg.pSender);
			_curSelected->Selected(true);
			_curSelected->SetAttribute(_T("bkcolor"), _T("#FF000000"));
			
			//�л�tab���ݿؼ�
#if defined _UNICODE
			std::wstring_view index_str(strName.GetData());
#else
			std::string_view index_str(strName.GetData());
#endif
			index_str.remove_prefix(6);//ʹviewֻ��������

			int index = std::stoi(index_str.data());

			_tabLayout->SelectItem(index);
		}
	}

	__super::Notify(msg);
}

void MainWndFrame::InitWindow()
{
	//��ȡ�ؼ�����
	_tabLayout = dynamic_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("TabLayoutMain")));
	_optionsLayout = dynamic_cast<CHorizontalLayoutUI*>(m_PaintManager.FindControl(_T("OptionsLayout")));
	_curSelected = dynamic_cast<COptionUI*>(m_PaintManager.FindControl(_T("Option0")));//��ʼ��ʱ��ѡ��Option0
}

UILIB_RESOURCETYPE MainWndFrame::GetResourceType() const
{
	return UILIB_RESOURCETYPE::UILIB_FILE;
}

LPCTSTR MainWndFrame::GetResourceID() const
{
	return MAKEINTRESOURCE(IDR_ZIPRES1);
}

CDuiString MainWndFrame::GetZIPFileName() const
{
	return _T("TabLayout.zip");
}


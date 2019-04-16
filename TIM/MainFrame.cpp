#include "stdafx.h"
#include "MainFrame.h"

CFrameWindowWnd::CFrameWindowWnd(){};
CFrameWindowWnd::~CFrameWindowWnd(){};

DUI_BEGIN_MESSAGE_MAP(CFrameWindowWnd, WindowImplBase)
DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
DUI_ON_MSGTYPE(DUI_MSGTYPE_SELECTCHANGED, OnSelectChanged)
DUI_END_MESSAGE_MAP()

LPCTSTR CFrameWindowWnd::GetWindowClassName() const {
	return _T("UIMainFrame");
}

CDuiString CFrameWindowWnd::GetSkinFolder() {
	return _T("");
}

CDuiString CFrameWindowWnd::GetSkinFile() {
	return _T("./res/tim.xml");
}

UINT CFrameWindowWnd::GetClassStyle() const { 
	return UI_CLASSSTYLE_FRAME | CS_DBLCLKS;
}

void CFrameWindowWnd::InitWindow() {
	CDuiString str;
	CListUI* pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("ListDemo2")));

	// 添加List列表内容，必须先Add(pListElement)，再SetText
	for (int i = 0; i < 100; i++)
	{
		CListTextElementUI* pListElement = new CListTextElementUI;
		pListElement->SetTag(i);
		pList->Add(pListElement);

		str.Format(_T("%d"), i);
		pListElement->SetText(0, str);
		pListElement->SetText(1, _T("haha"));
	}
}

void CFrameWindowWnd::Notify(TNotifyUI& msg) {
	CDuiString pSenderName = msg.pSender->GetName();
	TCHAR alert_msg[255] = { 0 };
	wsprintf(alert_msg, _T("操作控件名：%s"), pSenderName);
	OutputDebugString(alert_msg);
	TCHAR alert_msg2[255] = { 0 };
	wsprintf(alert_msg2, _T(" -> msg.sType %s\r\n"), msg.sType);
	OutputDebugString(alert_msg2);
	if (msg.sType == _T("itemselect")) {
		if (pSenderName == _T("ComboDemo")) {
			CComboUI *pCombo = static_cast<CComboUI*>(m_PaintManager.FindControl(_T("ComboDemo")));
			if (!pCombo)
				return;
			TCHAR alert_msg3[255] = { 0 };
			iComboIndex = pCombo->GetCurSel();
			wsprintf(alert_msg3, _T("Combo选中项：%d\r\n"), iComboIndex);
			OutputDebugString(alert_msg3);
		}
		else if (pSenderName == _T("ListDemo1")) {
			CListUI *pList = static_cast<CListUI*>(m_PaintManager.FindControl(_T("ListDemo1")));
			if (!pList)
				return;
			TCHAR alert_msg3[255] = { 0 };
			iListIndex = pList->GetCurSel();
			wsprintf(alert_msg3, _T("List选中项索引：%d\r\n"), iListIndex);
			OutputDebugString(alert_msg3);
			CListTextElementUI* pListElement = static_cast<CListTextElementUI*>(pList->GetItemAt(iListIndex));
			if (pListElement != NULL)
			{
				LPCTSTR pstr0 = pListElement->GetText(0);
				LPCTSTR pstr1 = pListElement->GetText(1);
				LPCTSTR pstr2 = pListElement->GetText(2);
				TCHAR alert_msg4[255] = { 0 };
				wsprintf(alert_msg4, _T("List选中项值：%s\r\n"), pstr0);
				OutputDebugString(alert_msg4);
			}
		}
	}
	WindowImplBase::Notify(msg);
}

// Tab 选项卡
void CFrameWindowWnd::OnSelectChanged(TNotifyUI& msg) {
	CDuiString pSenderName = msg.pSender->GetName();
	CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_PaintManager.FindControl(_T("tab")));
	TCHAR alert_msg[64] = { 0 };
	wsprintf(alert_msg, _T("Tab选中了%s\r\n"), pSenderName);
	OutputDebugString(alert_msg);

	if (pSenderName == _T("OptionDemo1"))
		pControl->SelectItem(0);
	else if (pSenderName == _T("OptionDemo2"))
		pControl->SelectItem(1);
	else if (pSenderName == _T("OptionDemo3"))
		pControl->SelectItem(2);
}

// All Click Event
void CFrameWindowWnd::OnClick(TNotifyUI& msg) {
	CDuiString pSenderName = msg.pSender->GetName();
	TCHAR alert_msg[64] = { 0 };
	wsprintf(alert_msg, _T("OnClick %s\r\n"), pSenderName);
	OutputDebugString(alert_msg);
	if (pSenderName == _T("openBtn")) {
		CEditUI *m_pEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editName")));

		ASSERT(m_pEdit != NULL);
		if (m_pEdit) {
			m_pEdit->SetVisible(false);
			CDuiString str = m_pEdit->GetText();
			CTextUI *m_pText = static_cast<CTextUI*>(m_PaintManager.FindControl(_T("username")));
			m_pText->SetText(str);
		}
	}
	else if (pSenderName == _T("helpBtn")) {
		CEditUI *m_pEdit = static_cast<CEditUI*>(m_PaintManager.FindControl(_T("editName")));

		ASSERT(m_pEdit != NULL);
		if (m_pEdit) {
			m_pEdit->SetVisible(true);
		}
	}
	else if (pSenderName == _T("closebtn")) {
		if (MessageBox(GetHWND(), TEXT("是否真的退出程序？"), TEXT("提示"), MB_YESNO | MB_ICONINFORMATION) == IDNO)
		{
			return;
		}
		PostQuitMessage(0);
	}
	else {
		WindowImplBase::OnClick(msg);
	}
}
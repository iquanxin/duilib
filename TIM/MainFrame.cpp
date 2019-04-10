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

UINT CFrameWindowWnd::GetClassStyle() const { 
	return CS_DBLCLKS; 
}

CDuiString CFrameWindowWnd::GetSkinFile() {
	return _T("./res/tim.xml");
}

CDuiString CFrameWindowWnd::GetSkinFolder() {
	return _T("");
}

CControlUI* CFrameWindowWnd::CreateControl(LPCTSTR pstrClass)
{
	return WindowImplBase::CreateControl(pstrClass);
}

LRESULT CFrameWindowWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;

	if (uMsg == WM_CREATE) {
		LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
		styleValue &= ~WS_CAPTION;
		::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

		m_pm.Init(m_hWnd);
		CDialogBuilder builder;
		CControlUI* pRoot = builder.Create(_T("./res/tim.xml"), (UINT)0, NULL, &m_pm);
		ASSERT(pRoot && "Failed to parse XML");
		m_pm.AttachDialog(pRoot);
		m_pm.AddNotifier(this); //添加控件等消息响应，这样消息就会传达到duilib的消息循环，我们可以在Notify函数里做消息处理
		return lRes;
	}
	else if (uMsg == WM_NCACTIVATE) {
		if (!::IsIconic(m_hWnd)) {
			return (wParam == 0) ? TRUE : FALSE;
		}
	}
	else if (uMsg == WM_NCCALCSIZE) {
		return 0;
	}
	else if (uMsg == WM_NCPAINT) {
		return 0;
	}

	if (m_pm.MessageHandler(uMsg, wParam, lParam, lRes)) return lRes;
	return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CFrameWindowWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
	if (wParam == SC_CLOSE) {
		::PostQuitMessage(0L);
		bHandled = TRUE;
		return 0;
	}
	BOOL bZoomed = ::IsZoomed(*this);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if (::IsZoomed(*this) != bZoomed) {
		CControlUI* pbtnMax = static_cast<CControlUI*>(m_pm.FindControl(_T("maxbtn")));         // max button
		CControlUI* pbtnRestore = static_cast<CControlUI*>(m_pm.FindControl(_T("restorebtn"))); // restore button

		// toggle status of max and restore button
		if (pbtnMax && pbtnRestore)
		{
			pbtnMax->SetVisible(TRUE == bZoomed);
			pbtnRestore->SetVisible(FALSE == bZoomed);
		}
	}
	return lRes;
}

void CFrameWindowWnd::Notify(TNotifyUI& msg) {
	CDuiString pSenderName = msg.pSender->GetName();
	TCHAR alert_msg[255] = { 0 };
	wsprintf(alert_msg, _T("操作控件名：%s"), pSenderName);
	OutputDebugString(alert_msg);
	TCHAR alert_msg2[255] = { 0 };
	wsprintf(alert_msg2, _T(" -> %s\r\n"), msg.sType);
	OutputDebugString(alert_msg2);
	if (pSenderName == _T("ComboDemo")) {
		if (msg.sType == _T("itemselect")) {
			CComboUI *pCombo = static_cast<CComboUI*>(m_pm.FindControl(_T("ComboDemo")));
			if (!pCombo)
				return;
			TCHAR alert_msg3[255] = { 0 };
			iComboIndex = pCombo->GetCurSel();
			wsprintf(alert_msg3, _T("Combo选中项：%d\r\n"), iComboIndex);
			OutputDebugString(alert_msg3);
		}
	}
	else if (pSenderName == _T("ListDemo1")) {
		if (msg.sType == _T("itemselect")) {
			CListUI *pList = static_cast<CListUI*>(m_pm.FindControl(_T("ListDemo1")));
			if (!pList)
				return;
			TCHAR alert_msg3[255] = { 0 };
			iListIndex = pList->GetCurSel();
			wsprintf(alert_msg3, _T("List选中项：%d\r\n"), iListIndex);
			OutputDebugString(alert_msg3);
			CListTextElementUI* pListElement = static_cast<CListTextElementUI*>(pList->GetItemAt(iListIndex));
			if (pListElement != NULL)
			{
				LPCTSTR pstr0 = pListElement->GetText(0);
				LPCTSTR pstr1 = pListElement->GetText(1);
				LPCTSTR pstr2 = pListElement->GetText(2);
				TCHAR alert_msg4[255] = { 0 };
				wsprintf(alert_msg4, _T("Lista选中项：%s\r\n"), pstr2);
				OutputDebugString(alert_msg4);
				//LPCTSTR pstr1 = pListElement->GetText(0);
				//LPCTSTR pstr2 = pListElement->GetText(1);

				//pListElement->SetText(0, _T("test1"));
				//pListElement->SetText(1, _T("test2"));
			}
		}
	}
	WindowImplBase::Notify(msg);
}

void CFrameWindowWnd::OnSelectChanged(TNotifyUI& msg) {
	CDuiString pSenderName = msg.pSender->GetName();
	CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("tab")));
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

void CFrameWindowWnd::OnClick(TNotifyUI& msg) {
	CDuiString pSenderName = msg.pSender->GetName();
	TCHAR alert_msg[64] = { 0 };
	wsprintf(alert_msg, _T("OnClick %s\r\n"), pSenderName);
	OutputDebugString(alert_msg);
	if (pSenderName == _T("openBtn")) {
		CEditUI *m_pEdit = static_cast<CEditUI*>(m_pm.FindControl(_T("editName")));

		ASSERT(m_pEdit != NULL);
		if (m_pEdit) {
			m_pEdit->SetVisible(false);
			::MessageBox(NULL, m_pEdit->GetText(), _T("提示"), NULL);
		}
		else {
			::MessageBox(NULL, _T("按钮不存在"), _T("提示"), NULL);
		}
	}
	else if (pSenderName == _T("helpBtn")) {
		::MessageBox(NULL, _T("求助按钮"), _T("提示"), NULL);
	}
	else if (pSenderName == _T("closebtn")) {
		if (MessageBox(GetHWND(), TEXT("是否真的退出程序？"), TEXT("提示"), MB_YESNO | MB_ICONINFORMATION) == IDNO)
		{
			return;
		}
		PostQuitMessage(0);
	}
	else if (pSenderName == _T("minbtn"))
	{
		SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, NULL);
	}
	else if (pSenderName == _T("maxbtn"))
	{
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, NULL);
	}
	else if (pSenderName == _T("restorebtn"))
	{
		SendMessage(WM_SYSCOMMAND, SC_RESTORE, NULL);
	}
	else {
		WindowImplBase::OnClick(msg);
	}
}
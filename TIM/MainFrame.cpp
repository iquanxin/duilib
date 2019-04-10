#include "stdafx.h"
#include "MainFrame.h"

CFrameWindowWnd::CFrameWindowWnd(){};
CFrameWindowWnd::~CFrameWindowWnd(){};

DUI_BEGIN_MESSAGE_MAP(CFrameWindowWnd, WindowImplBase)
DUI_ON_MSGTYPE(DUI_MSGTYPE_CLICK, OnClick)
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

//CControlUI* CFrameWindowWnd::CreateControl(LPCTSTR pstrClass)
//{
//	return NULL;
//}

LRESULT CFrameWindowWnd::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	// ��ʱ�����յ�WM_NCDESTROY���յ�wParamΪSC_CLOSE��WM_SYSCOMMAND
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

LRESULT CFrameWindowWnd::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) {
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
		m_pm.AddNotifier(this); //��ӿؼ�����Ϣ��Ӧ��������Ϣ�ͻᴫ�ﵽduilib����Ϣѭ�������ǿ�����Notify����������Ϣ����
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

void CFrameWindowWnd::Notify(TNotifyUI& msg) {
	CDuiString pSenderName = msg.pSender->GetName();
	if (msg.sType == _T("selectchanged")) {
		CDuiString    strName = msg.pSender->GetName();
		CTabLayoutUI* pControl = static_cast<CTabLayoutUI*>(m_pm.FindControl(_T("tabTest")));

		if (strName == _T("OptionDemo1"))
			pControl->SelectItem(0);
		else if (strName == _T("OptionDemo2"))
			pControl->SelectItem(1);
		else if (strName == _T("OptionDemo3"))
			pControl->SelectItem(2);
	}
	__super::Notify(msg);
}

void CFrameWindowWnd::OnClick(TNotifyUI& msg) {
	CDuiString pSenderName = msg.pSender->GetName();
	if (pSenderName == _T("openBtn")) {
		CEditUI * m_pHelpBtn = static_cast<CEditUI*>(m_pm.FindControl(_T("button1")));

		ASSERT(m_pHelpBtn != NULL);
		if (m_pHelpBtn) {
			//m_pHelpBtn->SetVisible(false);
			::MessageBox(NULL, m_pHelpBtn->GetText(), _T("��ʾ"), NULL);
		}
		else {
			::MessageBox(NULL, _T("��ť������"), _T("��ʾ"), NULL);
		}
	}
	else if (pSenderName == _T("helpBtn")) {
		::MessageBox(NULL, _T("������ť"), _T("��ʾ"), NULL);
	}
	else if (pSenderName == _T("closebtn")) {
		if (MessageBox(GetHWND(), TEXT("�Ƿ�����˳�����"), TEXT("��ʾ"), MB_YESNO | MB_ICONINFORMATION) == IDNO)
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
}
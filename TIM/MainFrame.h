#pragma once

class CFrameWindowWnd : public WindowImplBase {
public:
	CFrameWindowWnd();
	~CFrameWindowWnd();
	virtual LPCTSTR GetWindowClassName() const;
	virtual UINT GetClassStyle() const;
	virtual CDuiString GetSkinFolder();
	virtual CDuiString GetSkinFile();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	//virtual LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	//virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);
	//virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual void Notify(TNotifyUI& msg);
	//DUI_DECLARE_MESSAGE_MAP()
	virtual void OnClick(TNotifyUI& msg);

public:
	CPaintManagerUI m_pm;
};
#pragma once

class CFrameWindowWnd : public WindowImplBase
{
public:
	CFrameWindowWnd();
	~CFrameWindowWnd();

	virtual void InitWindow();

	virtual LPCTSTR GetWindowClassName() const;
	virtual CDuiString GetSkinFolder();
	virtual CDuiString GetSkinFile();
	virtual UINT GetClassStyle() const;

	virtual void Notify(TNotifyUI& msg);
	DUI_DECLARE_MESSAGE_MAP()
	virtual void OnClick(TNotifyUI& msg);
	virtual void OnSelectChanged(TNotifyUI& msg);

public:
	int iListIndex;
	int iComboIndex;
};
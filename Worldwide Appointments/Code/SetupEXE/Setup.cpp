#include <windows.h>
#include <tchar.h>
#include <shlwapi.h>
#include "resource.h"
#include "..\setup.h"

enum ErrorCodes
{
    RC_OK = 0,
    RC_NOAPPMGR,
    RC_FAILEDAPPMGRLAUNCH,
};

#define dimof(a) (sizeof(a) / sizeof((a)[0]))

static const TCHAR szRegKeyName[] = TEXT("Software\\")
                                      TEXT("Microsoft\\")
                                        TEXT("Windows\\")
                                          TEXT("CurrentVersion\\")
                                            TEXT("App Paths\\")
                                              TEXT("CEAppMgr.exe");

static HINSTANCE ghInst;

static int ShowMsg(HWND hWnd, UINT uMsgId, UINT uFlags)
{
    TCHAR szMsg[512], szCap[256];
    LoadString(ghInst, uMsgId, szMsg, dimof(szMsg));
    LoadString(ghInst, IDS_CAPTION, szCap, dimof(szCap));
    return (MessageBox(hWnd, szMsg, szCap, uFlags));
}

int WINAPI _tWinMain(HINSTANCE hInst, HINSTANCE /*hPrevInst*/,
    LPTSTR pszCmdLine, int nCmdShow)
{
    int rc;
    ghInst = hInst;

    // Set the debug flag, if specified
    LPCTSTR pszPrefixFlags = pszCmdLine;

    // Open the registry key that contains the CE AppMgr path
    TCHAR szValue[MAX_PATH];
    DWORD cbValue = sizeof(szValue);
    HKEY hKey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, szRegKeyName, 0, KEY_READ,
        &hKey) == ERROR_SUCCESS)
    {
        // Get the CE AppMgr path
        szValue[0] = TEXT('\0');
        RegQueryValueEx(hKey, NULL, NULL, NULL, (LPBYTE)szValue,
            &cbValue);
        RegCloseKey(hKey);
        TCHAR szCEAppMgrPath[MAX_PATH];
        ExpandEnvironmentStrings(szValue, szCEAppMgrPath,
            dimof(szCEAppMgrPath));

        // Build absolute path to the INI file
        // It should be in the same folder as this EXE file
        TCHAR szIniFilePath[MAX_PATH];
        GetModuleFileName(NULL, szIniFilePath, dimof(szIniFilePath));
        *PathFindFileName(szIniFilePath) = TEXT('\0');
        PathAppend(szIniFilePath, SZ_INIFILENAME);

        // Build the command line
        TCHAR szCmdLine[MAX_PATH * 2];
        wsprintf(szCmdLine, TEXT("%s \"%s\""), pszPrefixFlags,
            szIniFilePath);

        // Launch the CE App Mgr
        STARTUPINFO si;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        si.dwFlags = STARTF_USESHOWWINDOW;
        si.wShowWindow = (WORD)nCmdShow;
        PROCESS_INFORMATION pi;
        if (CreateProcess(szCEAppMgrPath, szCmdLine, NULL, NULL,
            FALSE, CREATE_DEFAULT_ERROR_MODE, NULL, NULL, &si, &pi))
        {
            CloseHandle(pi.hThread);
            CloseHandle(pi.hProcess);
            rc = RC_OK;
        }
        else
        {
            ShowMsg(NULL, IDS_ERROR_FAILEDTOLAUNCHAPPMGR,
                MB_ICONERROR|MB_OK);
            rc = RC_FAILEDAPPMGRLAUNCH;
        }
    }
    else
    {
        ShowMsg(NULL, IDS_ERROR_CEAPPMGRNOTFOUND,
            MB_ICONERROR|MB_OK);
        rc = RC_NOAPPMGR;
    }
    return (rc);
}

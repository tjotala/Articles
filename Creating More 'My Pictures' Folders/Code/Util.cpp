// Util.cpp : Utility functions
#include "StdAfx.h"
#include "ShellExt.h"
#include "Util.h"

int __cdecl ShowErrorMsg(HWND hParentWnd, UINT uFmtStrId,
    UINT uFlags, ...)
{
    HINSTANCE hResInst = _Module.GetResourceInstance();
    TCHAR szFormat[512];
    LoadString(hResInst, uFmtStrId, szFormat, dimof(szFormat));

    TCHAR szBuffer[1024];
    va_list Args;
    va_start(Args, uFlags);
    FormatMessage(FORMAT_MESSAGE_FROM_STRING, szFormat, 0, 0,
        szBuffer, dimof(szBuffer), &Args);
    va_end(Args);

    TCHAR szCap[256];
    LoadString(hResInst, IDS_ERROR_CAPTION, szCap, dimof(szCap));
    return (MessageBox(hParentWnd, szBuffer, szCap, uFlags));
}

static inline void MakeDesktopIniName(LPCTSTR pszFolderName,
    LPTSTR pszFileName)
{
    PathCombine(pszFileName, pszFolderName, TEXT("DESKTOP.INI"));
}

BOOL WINAPI IsMyPicsFolder(LPCTSTR pszFolderName)
{
    // Check the folder attributes
    BOOL rc = PathIsSystemFolder(pszFolderName, 0);
    if (rc)
    {
        // Check the existence and attributes of DESKTOP.INI
        TCHAR szFileName[MAX_PATH];
        MakeDesktopIniName(pszFolderName, szFileName);
        DWORD dwAttr = GetFileAttributes(szFileName);
        rc = (dwAttr != 0xffffffff);
        if (rc) // If exists...
        {
            rc = (dwAttr & FILE_ATTRIBUTE_HIDDEN) &&
                 (dwAttr & FILE_ATTRIBUTE_SYSTEM);
        }
    }
    return (rc);
}

BOOL WINAPI MakeMyPicsFolder(LPCTSTR pszFolderName)
{
    // Get path to the "My Pictures" folder
    TCHAR szSrcFolderName[MAX_PATH];
    BOOL rc = SUCCEEDED(SHGetSpecialFolderPath(NULL,
        szSrcFolderName, CSIDL_MYPICTURES, FALSE));
    if (rc)
    {
        // Copy the DESKTOP.INI file
        TCHAR szSrcFileName[MAX_PATH];
        MakeDesktopIniName(szSrcFolderName, szSrcFileName);
        TCHAR szDstFileName[MAX_PATH];
        MakeDesktopIniName(pszFolderName, szDstFileName);
        rc = CopyFile(szSrcFileName, szDstFileName, FALSE);
        if (rc)
        {
            rc = SetFileAttributes(szDstFileName,
                FILE_ATTRIBUTE_HIDDEN|FILE_ATTRIBUTE_SYSTEM);
            if (rc)
            {
                rc = PathMakeSystemFolder(pszFolderName);
                if (rc)
                {
                    // Try to expedite the shell view refresh
                    SHChangeNotify(SHCNE_CREATE|SHCNE_ATTRIBUTES,
                        SHCNF_PATH, szDstFileName, NULL);
                    SHChangeNotify(SHCNE_UPDATEDIR|SHCNE_ATTRIBUTES,
                        SHCNF_PATH, pszFolderName, NULL);
                }
            }
            if (!rc)
                DeleteFile(szDstFileName);
        }
    }
    return (rc);
}

BOOL WINAPI UnmakeMyPicsFolder(LPCTSTR pszFolderName)
{
    BOOL rc = PathUnmakeSystemFolder(pszFolderName);
    if (rc)
    {
        // Kill the DESKTOP.INI
        TCHAR szFileName[MAX_PATH];
        MakeDesktopIniName(pszFolderName, szFileName);
        rc = DeleteFile(szFileName);
        if (rc)
        {
            // Try to expedite the shell view refresh
            SHChangeNotify(SHCNE_DELETE, SHCNF_PATH, szFileName,
                NULL);
            SHChangeNotify(SHCNE_UPDATEDIR|SHCNE_ATTRIBUTES,
                SHCNF_PATH, pszFolderName, NULL);
        }
    }
    return (rc);
}

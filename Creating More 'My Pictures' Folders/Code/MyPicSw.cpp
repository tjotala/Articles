// MyPicSw.cpp : Implementation of DLL Exports.
#include "StdAfx.h"
#include "resource.h"
#include <initguid.h>
#include "ShellExt.h"
#include "Util.h"

CComModule _Module;

BEGIN_OBJECT_MAP(ObjectMap)
    OBJECT_ENTRY(CLSID_MyPicSwitch, CShellExt)
END_OBJECT_MAP()

EXTERN_C
BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason,
    LPVOID /*lpReserved*/)
{
    OSVERSIONINFO osvi;
    osvi.dwOSVersionInfoSize = sizeof(osvi);
    GetVersionEx(&osvi);
    if (osvi.dwPlatformId == VER_PLATFORM_WIN32_NT &&
        osvi.dwMajorVersion < 5)
        return (FALSE); // Bail if running WinNT 4.x or older
    if (osvi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS &&
        ((osvi.dwMajorVersion < 4) || 
         (osvi.dwMajorVersion == 4 && osvi.dwMinorVersion < 90)))
        return (FALSE); // Bail if running Win9x or older
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        _Module.Init(ObjectMap, hInstance);
        DisableThreadLibraryCalls(hInstance);
    }
    else
    if (dwReason == DLL_PROCESS_DETACH)
        _Module.Term();
    return (TRUE); // OK
}

STDAPI DllCanUnloadNow(void)
{
    return ((_Module.GetLockCount()==0) ? S_OK : S_FALSE);
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return (_Module.GetClassObject(rclsid, riid, ppv));
}

EXTERN_C
void CALLBACK RunDLL_CreateNewMyPicsFolder(HWND hParentWnd,
    HINSTANCE /*hInst*/, LPSTR pszCmdLine, int /*nCmdShow*/)
{
    BOOL rc = CreateDirectory(pszCmdLine, NULL);
    if (rc)
    {
        rc = MakeMyPicsFolder(pszCmdLine);
        if (!rc)
            RemoveDirectory(pszCmdLine);
    }
    if (!rc)
        ShowErrorMsg(hParentWnd, IDS_MSG_FAILED_TO_CREATE,
            MB_ICONWARNING|MB_OK, pszCmdLine);
}

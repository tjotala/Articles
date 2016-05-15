#pragma warning(disable : 4201) // nonstandard extension used
#pragma warning(disable : 4514) // unref'd inline function removed
#include <windows.h>
#include <tchar.h>
#include <ce_setup.h>
#include "resource.h"

#define dimof(a) (sizeof(a) / sizeof((a)[0]))

static const TCHAR szCalendarAppClassName[] = TEXT("Calendar");

static HINSTANCE ghInst;

EXTERN_C
BOOL WINAPI DllMain(HANDLE hInst, DWORD dwReason,
    LPVOID /*pReserved*/)
{
    if (dwReason == DLL_PROCESS_ATTACH)
    {
        ghInst = (HINSTANCE)hInst;
    }
    return (TRUE);
}

BOOL CheckCalendarApp(HWND hParentWnd, BOOL fProbeOnly = FALSE)
{
    // Find the Calendar app main window
    HWND hCalWnd = FindWindow(szCalendarAppClassName, NULL);
    if (hCalWnd != NULL)
    {
        // If we're just probing, return FALSE to indicate
        // that the Calendar app is still running
        if (fProbeOnly)
            return (FALSE);

        // Display the warning message
        TCHAR szMsg[256], szCap[256];
        LoadString(ghInst, IDS_WARNING_CALENDARRUNNING, szMsg,
            dimof(szMsg));
        LoadString(ghInst, IDS_CAPTION, szCap, dimof(szCap));
        int mbr = MessageBox(hParentWnd, szMsg, szCap,
            MB_ICONWARNING|MB_YESNOCANCEL);
        switch (mbr)
        {
            // Yes - try to kill the Calendar app
            case IDYES:
            {
                SendMessage(hCalWnd, WM_CLOSE, 0, 0);
                // Wait up to 5 seconds before giving up
                for (int i = 10; i; --i)
                {
                    if (CheckCalendarApp(hParentWnd, TRUE))
                        break;
                    // Sleep half a sec between each probe
                    Sleep(500);
                }

                // Complain if failed to kill Calendar app
                if (i == 0)
                {
                    LoadString(ghInst,
                        IDS_ERROR_FAILEDTOCLOSECALENDAR, szMsg,
                        dimof(szMsg));
                    mbr = MessageBox(hParentWnd, szMsg, szCap,
                        MB_ICONERROR|MB_OKCANCEL);
                    switch (mbr)
                    {
                        // OK - continue without killing
                        case IDOK:
                            break;
                        
                        // Cancel - quit without doing anything
                        case IDCANCEL:
                            return (FALSE);
                    }
                }
                break;
            }

            // No - don't kill it, just continue as is
            case IDNO:
                break;

            // Cancel - quit without doing anything
            case IDCANCEL:
                return (FALSE);
        }
    }

    // Return TRUE to indicate that it is OK to continue
    return (TRUE);
}

EXTERN_C
codeINSTALL_INIT Install_Init(HWND hParentWnd, BOOL /*fFirstCall*/,
    BOOL /*fPreviouslyInstalled*/, LPCTSTR /*pszInstallDir*/)
{
    // Ensure that Calendar app is not running, or kill it if it is
    if (CheckCalendarApp(hParentWnd))
        return (codeINSTALL_INIT_CONTINUE);
    return (codeINSTALL_INIT_CANCEL);
}

// This function seems to get called when it's already too late
// to close Calendar on the PsPC, but on HPC [Pro] it does get
// called before things get out of hand.
EXTERN_C
codeUNINSTALL_INIT Uninstall_Init(HWND hParentWnd,
    LPCTSTR /*pszInstallDir*/)
{
    // Ensure that Calendar app is not running, or kill it if it is
    if (CheckCalendarApp(hParentWnd))
        return (codeUNINSTALL_INIT_CONTINUE);
    return (codeUNINSTALL_INIT_CANCEL);
}

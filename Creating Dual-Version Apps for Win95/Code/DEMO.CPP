#include <windows.h>
#include "demo.h"
#include "ewv.h"

#if !defined(WM_STYLECHANGING) || !defined(WM_STYLECHANGED)
  #define WM_STYLECHANGING      0x007C
  #define WM_STYLECHANGED       0x007D
#endif // WM_STYLEC*

static void ShowMsg(HWND hParent, LPCSTR pszMsg)
{
    MessageBox(hParent, pszMsg, "Demo", MB_OK);
}

static void ShowStatus(HWND hDlg)
{
    char szBuffer[128];
    WORD wVer;
    DWORD dwStyle;

    GetTaskExpWinVer(GetCurrentTask(), &wVer);
    wsprintf(szBuffer, "%u.%02u", HIBYTE(wVer),
      LOBYTE(wVer));
    SetDlgItemText(hDlg, IDC_EXPWINVER, szBuffer);

    dwStyle = GetWindowLong(hDlg, GWL_STYLE);
    wsprintf(szBuffer, "%lu (0x%08lx)", dwStyle, dwStyle);
    SetDlgItemText(hDlg, IDC_STYLE, szBuffer);

    dwStyle = GetWindowLong(hDlg, GWL_EXSTYLE);
    wsprintf(szBuffer, "%lu (0x%08lx)", dwStyle, dwStyle);
    SetDlgItemText(hDlg, IDC_EXSTYLE, szBuffer);
}

extern "C" BOOL CALLBACK __export TestDlgProc(HWND hDlg,
  UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_INITDIALOG:
            SetDlgItemText(hDlg, IDC_TAG, LPCSTR(lParam));
            ShowStatus(hDlg);
            return (TRUE);

        case WM_STYLECHANGING:
            ShowMsg(hDlg, "WM_STYLECHANGING");
            break;

        case WM_STYLECHANGED:
            ShowMsg(hDlg, "WM_STYLECHANGED");
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam))
            {
                case IDC_CHANGE:
                    SetWindowLong(hDlg, GWL_STYLE,
                      GetWindowLong(hDlg, GWL_STYLE) ^
                      (WS_MINIMIZEBOX | WS_MAXIMIZEBOX)); 
                    ShowStatus(hDlg);
                    RedrawWindow(hDlg, NULL, NULL,
                      RDW_FRAME | RDW_INTERNALPAINT |
                      RDW_INVALIDATE);
                    return (TRUE);

                case IDOK:
                case IDCANCEL:
                    EndDialog(hDlg, 0);
                    return (TRUE);
            }
            break;
    }
    return (FALSE);
}

int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrevInst,
  LPSTR /*pszCmdLine*/, int /*nCmdShow*/)
{
    if (!IsWin95())
    {
        ShowMsg(NULL, "Not running on Win95!");
        return (1);
    }
    if (hPrevInst != NULL)
    {
        ShowMsg(NULL, "Single instance only!");
        return (2);
    }
        
    DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_TEST), NULL,
      TestDlgProc, LPARAM(LPCSTR("Marked as Win3x app")));

    SetModuleExpWinVer(hInst, 0x0400);
    SetTaskExpWinVer(GetCurrentTask(), 0x0400);

    DialogBoxParam(hInst, MAKEINTRESOURCE(IDD_TEST), NULL,
      TestDlgProc, LPARAM(LPCSTR("Marked as Win95 app")));

    SetModuleExpWinVer(hInst, 0x030a);
    SetTaskExpWinVer(GetCurrentTask(), 0x030a);

    return (0);
}


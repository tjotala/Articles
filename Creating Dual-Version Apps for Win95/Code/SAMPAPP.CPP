#include <windows.h>
#include "ewv.h"

int PASCAL WinMain(HINSTANCE hInst,
  HINSTANCE /*hPrevInst*/, LPSTR /*pszCmdLine*/,
  int /*nCmdShow*/)
{
    if (IsWin95())
    {
        if (GetModuleUsage(hInst) <= 1)
            SetModuleExpWinVer(hInst, 0x0400);
        SetTaskExpWinVer(GetCurrentTask(), 0x0400);
    }

    // do something else...

    if (IsWin95())
    {
        if (GetModuleUsage(hInst) <= 1)
            SetModuleExpWinVer(hInst, 0x030a);
        SetTaskExpWinVer(GetCurrentTask(), 0x030a);
    }
    return (0);
}


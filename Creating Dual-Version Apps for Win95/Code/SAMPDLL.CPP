#include <windows.h>
#include "ewv.h"

HINSTANCE g_hInstance;

int CALLBACK LibMain(HINSTANCE hInst, WORD /*wDataSeg*/,
  WORD /*cbHeap*/, LPSTR /*pszCmdLine*/)
{
    g_hInstance = hInst;
    if (IsWin95())
        SetModuleExpWinVer(g_hInstance, 0x0400);

    // do something else...
    return (1);
}

int CALLBACK WEP(int /*fExitType*/)
{
    // do something else...

    if (IsWin95())
        SetModuleExpWinVer(g_hInstance, 0x030a);
    return (1);
}


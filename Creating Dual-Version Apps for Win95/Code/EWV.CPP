#include <windows.h>
#include "ewv.h"

#define MAKEWORD(lo, hi)        ((WORD)(hi) * 256 +\
                                 (WORD)(lo))
#define BAD_PTR(p, cb)          (IsBadReadPtr((p), (cb)) ||\
                                 IsBadWritePtr((p), (cb)))

// undocumented function - KERNEL.133
extern "C" HMODULE WINAPI GetExePtr(HANDLE hModOrInst);

BOOL IsWin95()
{
    return (GetProcAddress(GetModuleHandle("KERNEL"),
      "GetVersionEx") != NULL);
}

BOOL GetModuleExpWinVer(HMODULE hModule, LPWORD pwVer)
{
    hModule = GetExePtr(hModule);
    LPBYTE pMDB = LPBYTE(MAKELP(hModule, 0));
    if (!BAD_PTR(pMDB, 0x40) &&
        pMDB[0x00] == 'N' && pMDB[0x01] == 'E' &&
        (pMDB[0x0c] & 0x10) == 0x00) // !Win32 module
    {
        *pwVer = MAKEWORD(pMDB[0x3e], pMDB[0x3f]);
        return (TRUE);
    }
    return (FALSE);
}

BOOL SetModuleExpWinVer(HMODULE hModule, WORD wVer)
{
    hModule = GetExePtr(hModule);
    LPBYTE pMDB = LPBYTE(MAKELP(hModule, 0));
    if (!BAD_PTR(pMDB, 0x40) &&
        pMDB[0x00] == 'N' && pMDB[0x01] == 'E' &&
        (pMDB[0x0c] & 0x10) == 0x00) // !Win32 module
    {
        pMDB[0x3e] = LOBYTE(wVer); // minor
        pMDB[0x3f] = HIBYTE(wVer); // major
        return (TRUE);
    }
    return (FALSE);
}

static BOOL SetQueueExpWinVer(HGLOBAL hQueue, WORD wVer)
{
    LPBYTE pMQ = LPBYTE(MAKELP(hQueue, 0));
    if (!BAD_PTR(pMQ, 0x44))
    {
        if (IsWin95())
        {
            pMQ[0x42] = LOBYTE(wVer); // minor
            pMQ[0x43] = HIBYTE(wVer); // major
        }
        else
        {
            pMQ[0x36] = LOBYTE(wVer); // minor
            pMQ[0x37] = HIBYTE(wVer); // major
        }
        return (TRUE);
    }
    return (FALSE);
}

BOOL GetTaskExpWinVer(HTASK hTask, LPWORD pwVer)
{
    LPBYTE pTDB = LPBYTE(MAKELP(hTask, 0));
    if (!BAD_PTR(pTDB, 0xfc) &&
        pTDB[0xfa] == 'T' && pTDB[0xfb] == 'D' &&
        (pTDB[0x16] & 0x10) == 0x00) // !Win32 task
    {
        *pwVer = MAKEWORD(pTDB[0x1a], pTDB[0x1b]);
        return (TRUE);
    }
    return (FALSE);
}

BOOL SetTaskExpWinVer(HTASK hTask, WORD wVer)
{
    LPBYTE pTDB = LPBYTE(MAKELP(hTask, 0));
    if (!BAD_PTR(pTDB, 0xfc) &&
        pTDB[0xfa] == 'T' && pTDB[0xfb] == 'D' &&
        (pTDB[0x16] & 0x10) == 0x00) // !Win32 task
    {
        WORD wSel = MAKEWORD(pTDB[0x20], pTDB[0x21]);
        if (SetQueueExpWinVer(HGLOBAL(wSel), wVer))
        {
            pTDB[0x1a] = LOBYTE(wVer); // minor
            pTDB[0x1b] = HIBYTE(wVer); // major
            return (TRUE);
        }
    }
    return (FALSE);
}


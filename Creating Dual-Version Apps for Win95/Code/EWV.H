#if !defined(__EWV_H__)
#define __EWV_H__

BOOL GetModuleExpWinVer(HMODULE hModule, LPWORD pwVer);
BOOL SetModuleExpWinVer(HMODULE hModule, WORD wVer);
BOOL GetTaskExpWinVer(HTASK hTask, LPWORD wVer);
BOOL SetTaskExpWinVer(HTASK hTask, WORD wVer);

BOOL IsWin95();

#endif // !__EWV_H__


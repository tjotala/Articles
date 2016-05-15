// Prototypes for the utility functions
#define dimof(a) (sizeof(a) / sizeof((a)[0]))
int __cdecl ShowErrorMsg(HWND hParentWnd, UINT uFmtStrId,
    UINT uFlags, ...);
BOOL WINAPI IsMyPicsFolder(LPCTSTR pszFolderName);
BOOL WINAPI MakeMyPicsFolder(LPCTSTR pszFolderName);
BOOL WINAPI UnmakeMyPicsFolder(LPCTSTR pszFolderName);

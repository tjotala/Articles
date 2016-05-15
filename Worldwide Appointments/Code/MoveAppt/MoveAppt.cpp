#include "Common.h"
#include <sipapi.h>
#include "POLWrap.h"

#define dimof(a) (sizeof(a) / sizeof((a)[0]))

#define COL_NAME                0 // Name of the city
#define COL_COUNTRY             1 // Country in which it resides

#if !defined(WIN32_PLATFORM_PSPC) // PsPC or PPC
#define SipShowIM(f)            (void)0 // do nothing
#endif

struct DlgData // Private data within the dialog box
{
    DlgData(HWND hWnd) : mApp(hWnd) { }
    COutlookApp mApp;           // Initialized in CePimCommand
    COutlookAppt mAppt;         // Initialized in CePimCommand
    COutlookCities mCities;     // Initialized in OnInitDialog
};

static HINSTANCE ghInst;

static int ShowMsg(HWND hWnd, UINT uMsgId, UINT uFlags)
{
    TCHAR szMsg[512], szCap[256];
    LoadString(ghInst, uMsgId, szMsg, dimof(szMsg));
    LoadString(ghInst, IDS_CAPTION, szCap, dimof(szCap));
    return (MessageBox(hWnd, szMsg, szCap, uFlags));
}

EXTERN_C BOOL WINAPI DllMain(HANDLE hInst, DWORD fdwReason,
    LPVOID /*pReserved*/)
{
    ghInst = (HINSTANCE)hInst;
    if (fdwReason == DLL_PROCESS_ATTACH)
        CoInitializeEx(NULL, COINIT_MULTITHREADED); // just in case
    else
    if (fdwReason == DLL_PROCESS_DETACH)
        CoUninitialize();
    return (TRUE);
}

static BOOL OnInitDialog(HWND hDlg, DlgData* pData)
{
    // Initialize the city list view control
    HWND hList = GetDlgItem(hDlg, IDC_CITYLIST);
    ListView_SetExtendedListViewStyle(hList, LVS_EX_FULLROWSELECT);
    TCHAR szHdr[256];
    LoadString(ghInst, IDS_COLHDR_NAME, szHdr, dimof(szHdr));
    LVCOLUMN lvc = { LVCF_FMT|LVCF_TEXT, LVCFMT_LEFT, 0, szHdr };
    ListView_InsertColumn(hList, COL_NAME, &lvc);
    LoadString(ghInst, IDS_COLHDR_COUNTRY, szHdr, dimof(szHdr));
    ListView_InsertColumn(hList, COL_COUNTRY, &lvc);
    RECT r;
    GetClientRect(hList, &r);
    r.right -= r.left;
    ListView_SetColumnWidth(hList, COL_NAME, r.right / 5 * 3);
    ListView_SetColumnWidth(hList, COL_COUNTRY, r.right / 5 * 2);
    pData->mCities = pData->mApp.GetCities();
    ListView_SetItemCount(hList, pData->mCities.GetCount());

    // Set the current city as initial selection
    COutlookCity CurCity = pData->mApp.GetCurrentCity();
    CComBSTR szName = CurCity.GetName();
    LVFINDINFO lvff = { LVFI_STRING, szName };
    int ii = ListView_FindItem(hList, -1, &lvff);
    ListView_EnsureVisible(hList, ii, FALSE);
    ListView_SetItemState(hList, ii, LVIS_SELECTED|LVIS_FOCUSED,
        LVIS_ALL);

    SipShowIM(SIPF_ON); // Show the input panel
    return (TRUE);
}

static BOOL OnGetDispInfo(HWND /*hDlg*/, DlgData* pData,
    NMLVDISPINFO* pDI)
{
    if (!(pDI->item.mask & LVIF_TEXT))
        return (FALSE);
    COutlookCity City = pData->mCities.GetCity(pDI->item.iItem + 1);
    CComBSTR szName;
    if (pDI->item.iSubItem == COL_NAME)
        szName = City.GetName();
    else
    if (pDI->item.iSubItem == COL_COUNTRY)
        City->get_Country(&szName);
    else
        return (FALSE);
    _tcsncpy(pDI->item.pszText, szName, pDI->item.cchTextMax);
    return (TRUE);
}

static BOOL OnFindItem(HWND hDlg, DlgData* pData, NMLVFINDITEM* pFI)
{
    if (!(pFI->lvfi.flags & (LVFI_STRING | LVFI_PARTIAL)))
        return (FALSE);
    int i = pData->mCities.FindCity(pFI->lvfi.psz);
    SetWindowLong(hDlg, DWL_MSGRESULT, i - 1);
    return (TRUE);
}

static void OnOK(HWND hDlg, DlgData* pData)
{
    // Get the current city
    COutlookCity CurCity = pData->mApp.GetCurrentCity();

    // Get the new city
    HWND hList = GetDlgItem(hDlg, IDC_CITYLIST);
    int i = ListView_GetNextItem(hList, -1, LVNI_SELECTED);
    COutlookCity NewCity = pData->mCities.GetCity(i + 1);

    // Move the appointment to the new time zone
    long lDeltaBias = NewCity.GetTimeZone().GetBias() -
                      CurCity.GetTimeZone().GetBias();
    DATE d;
    pData->mAppt->get_Start(&d);
    d += (DATE)lDeltaBias / (24 * 60);
    HRESULT hr = pData->mAppt->put_Start(d);

    // Save the changed appointment
    if (SUCCEEDED(hr))
        hr = pData->mAppt->Save();
    if (FAILED(hr))
        ShowMsg(hDlg, IDS_ERROR_FAILEDMOVE, MB_ICONERROR|MB_OK);
}

BOOL CALLBACK MoveDlgProc(HWND hDlg, UINT uMsg, WPARAM w, LPARAM l)
{
    DlgData* pData = (DlgData*)GetWindowLong(hDlg, DWL_USER);
    switch (uMsg)
    {
        case WM_INITDIALOG:
            SetWindowLong(hDlg, DWL_USER, l);
            pData = (DlgData*)l;
            return (OnInitDialog(hDlg, pData));

        case WM_NOTIFY:
            if (((NMHDR*)l)->idFrom == IDC_CITYLIST)
            {
                switch (((NMHDR*)l)->code)
                {
                    case LVN_GETDISPINFO:
                        return (OnGetDispInfo(hDlg, pData,
                            (NMLVDISPINFO*)l));
        
                    case LVN_ODFINDITEM:
                        return (OnFindItem(hDlg, pData,
                            (NMLVFINDITEM*)l));
                }
            }
            break;

        case WM_COMMAND:
            switch (LOWORD(w))
            {
                case IDOK:
                    OnOK(hDlg, pData);
                    // drops through to IDCANCEL handling
                case IDCANCEL:
                    SipShowIM(SIPF_OFF); // Hide the input panel
                    EndDialog(hDlg, LOWORD(w));
                    return (TRUE);
            }
            break;
    }
    return (FALSE);
}

EXTERN_C void WINAPI CePimCommand(HWND hWnd, UINT /*uType*/,
    UINT nData, HANDLE *rghData, LPVOID /*pReserved*/)
{
    if (nData != 1)
    {
        ShowMsg(hWnd, IDS_ERROR_SELNOTONE, MB_ICONWARNING|MB_OK);
        return;
    }
    DlgData dd(hWnd);
    if (dd.mApp == NULL)
    {
        ShowMsg(hWnd, IDS_ERROR_FAILEDLOGON, MB_ICONERROR|MB_OK);
        return;
    }
    if (FAILED(dd.mApp->GetItemFromOid(*(CEOID*)rghData,
        (IDispatch**)&dd.mAppt)))
    {
        ShowMsg(hWnd, IDS_ERROR_CANTFINDAPPT, MB_ICONERROR|MB_OK);
        return;
    }
    VARIANT_BOOL f;
    dd.mAppt->get_AllDayEvent(&f);
    if (f) // is all day event?
    {
        ShowMsg(hWnd, IDS_ERROR_ALLDAYEVENT, MB_ICONWARNING|MB_OK);
        return;
    }
    dd.mAppt->get_IsRecurring(&f);
    if (f) // is recurring appointment/event?
        if (ShowMsg(hWnd, IDS_WARNING_RECURRINGAPPT,
            MB_ICONWARNING|MB_YESNO) == IDNO)
            return;
    DialogBoxParam(ghInst, MAKEINTRESOURCE(IDD_MOVE), hWnd,
        MoveDlgProc, (LPARAM)&dd);
}

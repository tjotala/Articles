#include "Common.h"
#include <initguid.h> // causes POOM GUIDs to be declared locally
#include "POLWrap.h"

#if !defined(_tcsnicoll)
#define _tcsnicoll(sz1, sz2, cc) \
                                (CompareString(LOCALE_USER_DEFAULT,\
                                  NORM_IGNORECASE, sz1, cc, sz2,\
                                  cc) - 2)
#endif // !defined(_tcsnicoll)

COutlookApp::COutlookApp(HWND hWnd)
{
    HRESULT hr = CoCreateInstance(CLSID_Application, NULL,
        CLSCTX_INPROC_SERVER);
    if (FAILED(hr))
        return;
    hr = p->Logon((LONG)hWnd);
    if (FAILED(hr))
        Release();
}

COutlookCities COutlookApp::GetCities() const
{
    COutlookFolder Folder;
    HRESULT hr = p->GetDefaultFolder(olFolderCities, &Folder);
    COutlookCities Cities;
    if (SUCCEEDED(hr))
        Folder->get_Items(&Cities);
    return (Cities);
}

COutlookCity COutlookApp::GetCurrentCity() const
{
    long lCity;
    p->get_CurrentCityIndex(&lCity);
    COutlookCity City;
    if (lCity == olHomeCity)
        p->get_HomeCity(&City);
    else
        p->get_VisitingCity(&City);
    return (City);
}

COutlookCity COutlookCities::GetCity(int i) const
{
    COutlookCity City;
    p->Item(i, (IDispatch**)&City);
    return (City);
}

int COutlookCities::FindCity(LPCTSTR pszName) const
{
    int l = 1, r = GetCount(), cc = _tcslen(pszName);
    while (r >= l)
    {
        int i = (l + r) / 2;
        int c = _tcsnicoll(pszName, GetCity(i).GetName(), cc);
        if (c == 0)
        {
            // Search backwards until we hit first [partial] match
            for (--i; i >= 1; --i)
            {
                c = _tcsnicoll(pszName, GetCity(i).GetName(), cc);
                if (c != 0)
                    break;
            }
            return (++i);
        }
        if (c < 0)
            r = i - 1;
        else // c > 0
            l = i + 1;
    }
    return (0);
}

CComBSTR COutlookCity::GetName() const
{
    CComBSTR szName;
    p->get_Name(&szName);
    return (szName);
}

COutlookTimeZone COutlookCity::GetTimeZone() const
{
    long lTZ;
    HRESULT hr = p->get_TimezoneIndex(&lTZ);
    COutlookTimeZone TimeZone;
    if (SUCCEEDED(hr))
    {
        CComPtr<IPOutlookApp> pApp;
        p->get_Application(&pApp);
        pApp->GetTimeZoneFromIndex(lTZ, &TimeZone);
    }
    return (TimeZone);
}

#include <pimstore.h>
#include <cguid.h>
#include <atlbase.h>
extern CComModule _Module; // just to keep the compiler happy
#include <atlcom.h>

typedef CComPtr<IFolder> COutlookFolder;
typedef CComPtr<IAppointment> COutlookAppt;

class COutlookTimeZone : public CComPtr<ITimeZone>
{
public:
    long GetBias() const { long l; p->get_Bias(&l); return (l); }
};

class COutlookCity : public CComPtr<ICity>
{
public:
    CComBSTR GetName() const;
    COutlookTimeZone GetTimeZone() const;
};

class COutlookCities : public CComPtr<IPOutlookItemCollection>
{
public:
    int GetCount() const { int n; p->get_Count(&n); return (n); }
    COutlookCity GetCity(int i) const;
    int FindCity(LPCTSTR pszName) const;
};

class COutlookApp : public CComPtr<IPOutlookApp>
{
public:
    COutlookApp(HWND hWnd);
    ~COutlookApp() { if (p != NULL) p->Logoff(); }
    COutlookCities GetCities() const;
    COutlookCity GetCurrentCity() const;
};

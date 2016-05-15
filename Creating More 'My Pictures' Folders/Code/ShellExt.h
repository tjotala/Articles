// ShellExt.h : Declaration of the CShellExt
#ifndef __SHELLEXT_H_
#define __SHELLEXT_H_

#include "resource.h"
#include <shlobj.h>
#include <shlguid.h>

// {C64FC7E8-6F17-4612-B6C0-33F33944B09B}
DEFINE_GUID(CLSID_MyPicSwitch, 0xc64fc7e8, 0x6f17, 0x4612, 0xb6,
    0xc0, 0x33, 0xf3, 0x39, 0x44, 0xb0, 0x9b);

class ATL_NO_VTABLE CShellExt : 
    public CComObjectRootEx<CComSingleThreadModel>,
    public CComCoClass<CShellExt, &CLSID_MyPicSwitch>,
    public IShellExtInit, public IContextMenu
{
public:
    CShellExt()  : m_pDataObj(NULL), m_hDrop(NULL) { }
    virtual ~CShellExt() { CleanUp(); }

    DECLARE_NO_REGISTRY()
    DECLARE_NOT_AGGREGATABLE(CShellExt)
    DECLARE_PROTECT_FINAL_CONSTRUCT()

    BEGIN_COM_MAP(CShellExt)
        COM_INTERFACE_ENTRY(IShellExtInit)
        COM_INTERFACE_ENTRY(IContextMenu)
    END_COM_MAP()

public: // IShellExtInit
    STDMETHOD(Initialize)(LPCITEMIDLIST pidlFolder,
        LPDATAOBJECT lpdobj, HKEY hkeyProgID);

public: // IContextMenu
    STDMETHOD(QueryContextMenu)(HMENU hMenu, UINT iMenu,
        UINT idCmdFirst, UINT idCmdLast, UINT uFlags);
    STDMETHOD(InvokeCommand)(LPCMINVOKECOMMANDINFO lpici);
    STDMETHOD(GetCommandString)(UINT idCmd, UINT uType,
        UINT* pwReserved, LPSTR pszName, UINT cchMax);

protected:
    void CleanUp();

protected:
    LPDATAOBJECT m_pDataObj;
    HDROP m_hDrop;
    UINT m_nSelItems;
    UINT m_nMyPicsFolders;
};

#endif //__SHELLEXT_H_

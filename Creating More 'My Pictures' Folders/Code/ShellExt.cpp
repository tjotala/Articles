// ShellExt.cpp : Implementation of CShellExt
#include "StdAfx.h"
#include "ShellExt.h"
#include "Util.h"

void CShellExt::CleanUp()
{
    if (m_pDataObj != NULL)
    {
        m_pDataObj->Release();
        m_pDataObj = NULL;
    }
    if (m_hDrop != NULL)
    {
        GlobalFree(m_hDrop);
        m_hDrop = NULL;
    }
}

STDMETHODIMP CShellExt::Initialize(LPCITEMIDLIST /*pidlFolder*/,
    LPDATAOBJECT lpdobj, HKEY /*hkeyProgID*/)
{
    HRESULT hr = E_INVALIDARG;
    // We could be called multiple times during
    // the lifetime of this object
    CleanUp();
    if (lpdobj != NULL)
    {
        // Keep the IDataObject around
        m_pDataObj = lpdobj;
        m_pDataObj->AddRef();

        // Get the list of files in the CF_HDROP format
        FORMATETC fmte = { CF_HDROP, NULL, DVASPECT_CONTENT, -1,
            TYMED_HGLOBAL };
        STGMEDIUM medium;
        hr = m_pDataObj->GetData(&fmte, &medium);
        if (SUCCEEDED(hr))
            m_hDrop = reinterpret_cast<HDROP>(medium.hGlobal);
        else
            CleanUp();
    }
    return (hr);
}

STDMETHODIMP CShellExt::QueryContextMenu(HMENU hMenu,
    UINT iMenu, UINT idCmdFirst, UINT /*idCmdLast*/, UINT uFlags)
{
    // Only respond 
    if (((uFlags & 0x0000000f) == CMF_NORMAL) ||
        (uFlags & CMF_EXPLORE))
    {
        // Count the number of folders that have a image preview
        m_nSelItems = DragQueryFile(m_hDrop, 0xffffffff, NULL, 0);
        m_nMyPicsFolders = 0;
        for (UINT i = 0; i < m_nSelItems; ++i)
        {
            TCHAR szName[MAX_PATH];
            DragQueryFile(m_hDrop, i, szName, dimof(szName));
            if (IsMyPicsFolder(szName))
                m_nMyPicsFolders++;
        }

        // Add the new menu item along with a tri-state checkmark
        HINSTANCE hResInst = _Module.GetResourceInstance();
        TCHAR szMenuItem[128];
        LoadString(hResInst, IDS_MENUITEM_TEXT, szMenuItem,
            dimof(szMenuItem));
        MENUITEMINFO mii;
        ZeroMemory(&mii, sizeof(mii));
        mii.cbSize = sizeof(mii);
        mii.fMask = MIIM_CHECKMARKS|MIIM_ID|MIIM_STATE|MIIM_TYPE;
        mii.fType = MFT_STRING;
        mii.fState = MFS_ENABLED|MFS_CHECKED;
        mii.wID = idCmdFirst;
        LPCTSTR pszResId;
        if (m_nMyPicsFolders == 0)
            pszResId = MAKEINTRESOURCE(IDB_UNCHECKED);
        else
        if (m_nMyPicsFolders >= m_nSelItems)
            pszResId = MAKEINTRESOURCE(IDB_CHECKEDALL);
        else
            pszResId = MAKEINTRESOURCE(IDB_CHECKEDSOME);
        mii.hbmpChecked = LoadBitmap(hResInst, pszResId);
        mii.dwTypeData = szMenuItem;
        InsertMenuItem(hMenu, iMenu, TRUE, &mii);

        // Return the number of menu items we added
        return (1);
    }
    return (E_FAIL);
}

STDMETHODIMP CShellExt::InvokeCommand(LPCMINVOKECOMMANDINFO lpici)
{
    // We should look at lpici->lpVerb but we've only added one cmd
    for (UINT i = 0; i < m_nSelItems; ++i)
    {
        TCHAR szName[MAX_PATH];
        DragQueryFile(m_hDrop, i, szName, dimof(szName));
        if (PathIsDirectory(szName)) // Paranoia rules
        {
            // Tri-state switch: none->all, some->all, all->none
            UINT uErrMsgId = 0;
            if (m_nMyPicsFolders >= m_nSelItems)
            {
                if (!UnmakeMyPicsFolder(szName))
                    uErrMsgId = IDS_MSG_FAILED_TO_UNMAKE;
            }
            else
            if (!IsMyPicsFolder(szName))
            {
                if (!MakeMyPicsFolder(szName))
                    uErrMsgId = IDS_MSG_FAILED_TO_MAKE;
            }
            if (uErrMsgId != 0)
                ShowErrorMsg(lpici->hwnd, uErrMsgId,
                    MB_ICONWARNING|MB_OK, szName);
        }
    }
    return (S_OK);
}

STDMETHODIMP CShellExt::GetCommandString(UINT /*idCmd*/,
    UINT uType, UINT* /*pwReserved*/, LPSTR pszName, UINT cchMax)
{
    // We should look at idCmd but we've only added one cmd
    UINT uResId;
    if (uType == GCS_HELPTEXT)
        uResId = IDS_MENUITEM_HELP;
    else
    if (uType == GCS_VERB)
        uResId = IDS_MENUITEM_VERB;
    else
        return (E_NOTIMPL);
    HINSTANCE hResInst = _Module.GetResourceInstance();
    LoadString(hResInst, uResId, pszName, cchMax);
    return (S_OK);
}

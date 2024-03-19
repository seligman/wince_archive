// 240 80

#include <windows.h>
#include <commctrl.h>
#define INITGUID
#include <initguid.h>
#include <coguid.h>
#include <aygshell.h>
#include <sip.h>

#include "resource.h"

#include "MainWnd.h"
#include "KeyStrokeCE.h"
#include "main.h"

HINSTANCE hInst;

long g_DllCnt = 0;

#define KEY_GUID TEXT ("{E74C82A5-22A0-11d4-B859-00B0D040070E}")

static const TCHAR szCLSIDKeyStrokeCE[] = KEY_GUID;
static const GUID CLSID_KeyStrokeCE = { 0xe74c82a5, 0x22a0, 0x11d4, { 0xb8, 0x59, 0x0, 0xb0, 0xd0, 0x40, 0x7, 0xe } };
static const TCHAR szFriendlyName[] = TEXT ("KeyStrokeCE");

BOOL WINAPI DllMain (HANDLE hinstDLL, DWORD dwReason, LPVOID lpvReserved) {
    hInst = (HINSTANCE) hinstDLL;
    return TRUE;
}

STDAPI DllGetClassObject (REFCLSID rclsid, REFIID riid, LPVOID *ppv) {
    MyClassFactory *pcf;
    HRESULT hr;

    // See if caller wants us...
    if (IsEqualCLSID (rclsid, CLSID_KeyStrokeCE)) {

        // Create IClassFactory object.
        pcf = new MyClassFactory();
        if (pcf == NULL)
            return E_OUTOFMEMORY;

        // Call class factory's query interface method.
        hr = pcf->QueryInterface (riid, ppv);
        // This will cause an obj delete unless interface found
        pcf->Release();
        return hr;
    }
    return CLASS_E_CLASSNOTAVAILABLE;
}
//======================================================================
// DllCanUnloadNow - Exported function called when DLL can unload
//
STDAPI DllCanUnloadNow () {

    if (g_DllCnt)
        return S_FALSE;
    return S_OK;
}
//======================================================================
// DllRegisterServer - Exported function called to register the server
//
STDAPI DllRegisterServer () {
    TCHAR szName[MAX_PATH+2];
    DWORD dwDisp;
    HKEY hKey, hSubKey;
    INT rc, i;

    GetModuleFileName (hInst, szName, sizeof (szName));
    // Open the key.
    rc = RegCreateKeyEx (HKEY_CLASSES_ROOT, _T("CLSID\\") KEY_GUID, 0,
                         TEXT (""), 0, 0, NULL, &hKey, &dwDisp);
    if (rc != ERROR_SUCCESS)
        return E_FAIL;

    // Set the friendly name of the SIP.
    RegSetValueEx (hKey, TEXT (""), 0, REG_SZ, (PBYTE)szFriendlyName,
                   (lstrlen (szFriendlyName)+1) * sizeof (TCHAR));

    // Create subkeys.
    // Set the module name of the SIP.
    rc = RegCreateKeyEx (hKey, TEXT ("InProcServer32"), 0, TEXT (""),
                         0, 0, NULL, &hSubKey, &dwDisp);
    rc = RegSetValueEx (hSubKey, TEXT (""), 0, REG_SZ, (PBYTE)szName,
                        (lstrlen (szName)+1) * sizeof (TCHAR));
    RegCloseKey (hSubKey);

    // Set the default icon of the server.
    RegCreateKeyEx (hKey, TEXT ("DefaultIcon"), 0, TEXT (""),
                         0, 0, NULL, &hSubKey, &dwDisp);
    lstrcat (szName, TEXT (",0"));
    RegSetValueEx (hSubKey, TEXT (""), 0, REG_SZ, (PBYTE)szName,
                        (lstrlen (szName)+1) * sizeof (TCHAR));
    RegCloseKey (hSubKey);

    // Set the flag indicating this is a SIP.
    RegCreateKeyEx (hKey, TEXT ("IsSIPInputMethod"), 0, TEXT (""), 
                    0, 0, NULL, &hSubKey, &dwDisp);
    i = 1;
	TCHAR * szOne = _T("1");
    RegSetValueEx (hSubKey, TEXT (""), 0, REG_SZ, (PBYTE)szOne, (lstrlen (szOne)+1) * sizeof (TCHAR));
    RegCloseKey (hSubKey);

    RegCloseKey (hKey);
    return S_OK;
}
//======================================================================
// DllUnregisterServer - Exported function called to remove the server
// information from the registry
//
STDAPI DllUnregisterServer() {
    INT rc;
    rc = RegDeleteKey (HKEY_CLASSES_ROOT, _T("CLSID\\") KEY_GUID);
    if (rc == ERROR_SUCCESS)
        return S_OK;
    return E_FAIL;
}
//**********************************************************************
// MyClassFactory Object implimentation
//----------------------------------------------------------------------
// Object constructor
MyClassFactory::MyClassFactory () {
    m_lRef = 1;     //Set ref count to 1 on create
    return;
}
//----------------------------------------------------------------------
// Object destructor
MyClassFactory::~MyClassFactory () {
    return;
}
//----------------------------------------------------------------------
// QueryInterface - Called to see what interfaces this object supports
STDMETHODIMP MyClassFactory::QueryInterface (THIS_ REFIID riid, 
                                             LPVOID *ppv) {

    // If caller wants our IUnknown or IClassFactory object, 
    // return a pointer to the object.
    if (IsEqualIID (riid, IID_IUnknown) || 
        IsEqualIID (riid, IID_IClassFactory)) {

        *ppv = (LPVOID)this;     // return pointer to object.
        AddRef();                // Inc ref to prevent delete on return.
        return NOERROR;
    }
    *ppv = NULL;
    return (E_NOINTERFACE);
}
//----------------------------------------------------------------------
// AddRef - Increment object reference count.
STDMETHODIMP_(ULONG) MyClassFactory::AddRef (THIS) {
    ULONG cnt;

    cnt = (ULONG)InterlockedIncrement (&m_lRef);
    return cnt;
}
//----------------------------------------------------------------------
// Release - Decrement object reference count.
STDMETHODIMP_(ULONG) MyClassFactory::Release (THIS) {
    ULONG cnt;

    cnt = (ULONG)InterlockedDecrement (&m_lRef);
    if (cnt == 0)
        delete this;
    return cnt;
}
//----------------------------------------------------------------------
// LockServer - Called to tell the DLL not to unload even if use cnt 0
STDMETHODIMP MyClassFactory::LockServer (BOOL fLock) {
    if (fLock)
        InterlockedIncrement (&g_DllCnt);
    else
        InterlockedDecrement (&g_DllCnt);
    return NOERROR;
}
//----------------------------------------------------------------------
// CreateInstance - Called to have class factory object create other
// objects
STDMETHODIMP MyClassFactory::CreateInstance (LPUNKNOWN pUnkOuter, 
                                             REFIID riid, LPVOID *ppv) {
    MyIInputMethod *pMyIM;
    HRESULT hr;

    if (pUnkOuter)
        return (CLASS_E_NOAGGREGATION);

    if (IsEqualIID (riid, IID_IUnknown) || 
        IsEqualIID (riid, IID_IInputMethod)) {

        // Create file filter object.
        pMyIM = new MyIInputMethod();
        if (!pMyIM)
            return E_OUTOFMEMORY;

        // See if object exports the proper interface.
        hr = pMyIM->QueryInterface (riid, ppv);
        // This will cause an obj delete unless interface found.
        pMyIM->Release ();
        return hr;
    } 
    return E_NOINTERFACE;
}

//**********************************************************************
// MyIInputMethod Object implementation
//----------------------------------------------------------------------
// Object constructor
MyIInputMethod::MyIInputMethod () {

    m_lRef = 1;     //Set reference count to 1 on create.
    g_DllCnt++;
    return;
}
//----------------------------------------------------------------------
// Object destructor
MyIInputMethod::~MyIInputMethod () {
    g_DllCnt--;
    return;
}
//----------------------------------------------------------------------
// QueryInterface - Called to see what interfaces this object supports
STDMETHODIMP MyIInputMethod::QueryInterface (THIS_ REFIID riid, 
                                             LPVOID *ppv) {

    // If caller wants our IUnknown or IID_ICeFileFilter object, 
    // return a pointer to the object.
    if (IsEqualIID (riid, IID_IUnknown) || 
        IsEqualIID (riid, IID_IInputMethod)){

        // Return pointer to object.
        *ppv = (IInputMethod *)this;
        AddRef();                // Inc ref to prevent delete on return.
        return NOERROR;
    }
    *ppv = NULL;
    return (E_NOINTERFACE);
}
//----------------------------------------------------------------------
// AddRef - Increment object reference count.
STDMETHODIMP_(ULONG) MyIInputMethod::AddRef (THIS) {
    ULONG cnt;

    cnt = (ULONG)InterlockedIncrement (&m_lRef);
    return cnt;
}
//----------------------------------------------------------------------
// Release - Decrement object reference count.
STDMETHODIMP_(ULONG) MyIInputMethod::Release (THIS) {
    ULONG cnt;

    cnt = (ULONG)InterlockedDecrement (&m_lRef);
    if (cnt == 0) {
        delete this;
        return 0;
    }
    return cnt;
}
//----------------------------------------------------------------------
// Select - The IM has just been loaded into memory.
//
HRESULT STDMETHODCALLTYPE MyIInputMethod::Select (HWND hwndSip) {
    RECT rect;
    WNDCLASS wc;
    HBITMAP hBmp, hbmpMask;

    m_hwndParent = hwndSip;

    // Create image list for narrow (16x16) image.
    m_himlNarrow = ImageList_Create (16, 16, ILC_COLOR | ILC_MASK, 
                                     1, 0);
    hBmp = LoadBitmap (hInst, MAKEINTRESOURCE(IDB_NARROW));
    hbmpMask = LoadBitmap (hInst, MAKEINTRESOURCE(IDB_NARROW_MASK));
    ImageList_Add (m_himlNarrow, hBmp, hbmpMask);
    DeleteObject (hBmp);
    DeleteObject (hbmpMask);

    // Create image list for wide (32x16) image.
    m_himlWide = ImageList_Create (32, 16, ILC_COLOR | ILC_MASK, 1, 0);
    hBmp = LoadBitmap (hInst, MAKEINTRESOURCE(IDB_WIDE));
    hbmpMask = LoadBitmap (hInst, MAKEINTRESOURCE(IDB_WIDE_MASK));
    ImageList_Add (m_himlWide, hBmp, hbmpMask);
    DeleteObject (hBmp);
    DeleteObject (hbmpMask);

	m_pMainWnd = new CMainWnd();

    // Register SIP window class.
//    memset (&wc, 0, sizeof (wc));
//    wc.style = CS_DBLCLKS;
//    wc.lpfnWndProc = m_pMainWnd->MainWndProc;
//    wc.hInstance = hInst;                     // Owner handle
//    wc.hbrBackground = (HBRUSH) GetStockObject (WHITE_BRUSH);
//    wc.lpszClassName = MYSIPCLS;              // Window class name

    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = m_pMainWnd->MainWndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInst;
    wc.hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_MAINICON));
    wc.hCursor = NULL;
    wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = MYSIPCLS;

    if (RegisterClass (&wc) == 0) return E_FAIL;



    // Create SIP window.  
    GetClientRect (hwndSip, &rect);
    m_hwndMyWnd = CreateWindowEx (0, MYSIPCLS, TEXT (""), 
                  WS_VISIBLE | WS_CHILD | WS_BORDER, rect.left, 
                  rect.top, rect.right - rect.left, 
                  rect.bottom - rect.top, hwndSip, NULL, 
                  hInst, 0);

	m_pMainWnd->SetHinstance(hInst);
	m_pMainWnd->SetHwnd(m_hwndMyWnd);

    if (!IsWindow (m_hwndMyWnd))
        return E_FAIL;

    return S_OK;
}
//----------------------------------------------------------------------
// Deselect - The IM is about to be unloaded.
//
HRESULT STDMETHODCALLTYPE MyIInputMethod::Deselect (void) {

    // Clean up since we're about to be unloaded.
    DestroyWindow (m_hwndMyWnd);
    UnregisterClass (MYSIPCLS, hInst);
	delete (m_pMainWnd);
    ImageList_Destroy (m_himlNarrow);
    ImageList_Destroy (m_himlWide);
    return S_OK;
}
//----------------------------------------------------------------------
// Showing - The IM is about to be made visible.
//
HRESULT STDMETHODCALLTYPE MyIInputMethod::Showing (void) {
    return S_OK;
}
//----------------------------------------------------------------------
// Hiding - The IM is about to be hidden.
//
HRESULT STDMETHODCALLTYPE MyIInputMethod::Hiding (void) {
    return S_OK;
}
//----------------------------------------------------------------------
// GetInfo - The SIP wants info from the IM.
//
HRESULT STDMETHODCALLTYPE MyIInputMethod::GetInfo (
                                              IMINFO __RPC_FAR *pimi) {
    pimi->cbSize = sizeof (IMINFO);
    pimi->hImageNarrow = m_himlNarrow;
    pimi->hImageWide = m_himlWide;
    pimi->iNarrow = 0;
    pimi->iWide = 0;  
    pimi->fdwFlags = SIPF_DOCKED;

    pimi->rcSipRect.left = 0;
    pimi->rcSipRect.top = 0;
    pimi->rcSipRect.right = 80;
    pimi->rcSipRect.bottom = 80;

    SendMessage (m_hwndMyWnd, WM_USER_GETINFO, 1, (LPARAM) pimi);
    return S_OK;
}
//----------------------------------------------------------------------
// ReceiveSipInfo - The SIP is passing info to the IM.
//
HRESULT STDMETHODCALLTYPE MyIInputMethod::ReceiveSipInfo (
                                               SIPINFO __RPC_FAR *psi) {
    // Pass the SIP info data to the window.
    SendMessage (m_hwndMyWnd, WM_USER_GETINFO, 2, (LPARAM) psi);
    return S_OK;
}
//----------------------------------------------------------------------
// RegisterCallback - The SIP is providing the IM with the pointer to 
// the IIMCallback interface.
//
HRESULT STDMETHODCALLTYPE MyIInputMethod::RegisterCallback (
                                  IIMCallback __RPC_FAR *lpIMCallback) {
    m_pIMCallback = lpIMCallback;
    PostMessage (m_hwndMyWnd, WM_USER_GETINFO, 0, (LPARAM)m_pIMCallback);
    return S_OK;
}
//----------------------------------------------------------------------
// GetImData - An application is passing IM-specfic data to the IM.
// 
HRESULT STDMETHODCALLTYPE MyIInputMethod::GetImData (DWORD dwSize,
                                                     LPVOID pvImData) {
    return E_FAIL;
}
//----------------------------------------------------------------------
// SetImData - An application is querying IM-specfic data from the IM.
//
HRESULT STDMETHODCALLTYPE MyIInputMethod::SetImData (DWORD dwSize, 
                                                     LPVOID pvImData) {
    return S_OK;
}
//----------------------------------------------------------------------
// UserOptionsDlg - The SIP control panel applet is asking for a 
// configuration dialog box to be displayed.
//
HRESULT STDMETHODCALLTYPE MyIInputMethod::UserOptionsDlg (
                                                     HWND hwndParent) {
    MessageBox (hwndParent, TEXT ("There are no options at this time."),
                TEXT ("KeyStrokeCE"), MB_OK);
    return S_OK;
}

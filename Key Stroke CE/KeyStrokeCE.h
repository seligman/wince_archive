class MyClassFactory : public IClassFactory {

private:
	long m_lRef;

public:
	MyClassFactory();
	~MyClassFactory();

	STDMETHODIMP QueryInterface (THIS_ REFIID riid, LPVOID *ppv);
	STDMETHODIMP_(ULONG) AddRef (THIS);
	STDMETHODIMP_(ULONG) Release (THIS);

	STDMETHODIMP CreateInstance (LPUNKNOWN pUnkOuter, REFIID riid, LPVOID *ppv);
	STDMETHODIMP LockServer (BOOL fLock);
};

class MyIInputMethod : public IInputMethod {

private:
	long m_lRef;
	HWND m_hwndParent;
	HWND m_hwndMyWnd;
	HIMAGELIST m_himlWide;
    HIMAGELIST m_himlNarrow;
	IIMCallback *m_pIMCallback;
	CMainWnd *m_pMainWnd;

public:
	MyIInputMethod();
	~MyIInputMethod();

	STDMETHODIMP QueryInterface (THIS_ REFIID riid, LPVOID *ppvObj);
	STDMETHODIMP_(ULONG) AddRef (THIS);
	STDMETHODIMP_(ULONG) Release (THIS);

	HRESULT STDMETHODCALLTYPE Select (HWND hwndSip);
	HRESULT STDMETHODCALLTYPE Deselect (void);
	HRESULT STDMETHODCALLTYPE Showing (void);
	HRESULT STDMETHODCALLTYPE Hiding (void);
	HRESULT STDMETHODCALLTYPE GetInfo (IMINFO __RPC_FAR *pimi);
	HRESULT STDMETHODCALLTYPE ReceiveSipInfo (SIPINFO __RPC_FAR *psi);
	HRESULT STDMETHODCALLTYPE RegisterCallback (IIMCallback __RPC_FAR *lpIMCallback);
	HRESULT STDMETHODCALLTYPE GetImData (DWORD dwSize, LPVOID pvImData);
	HRESULT STDMETHODCALLTYPE SetImData (DWORD dwSize, LPVOID pvImData);
	HRESULT STDMETHODCALLTYPE UserOptionsDlg (HWND hwndParent);
};


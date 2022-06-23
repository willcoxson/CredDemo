// Provider.h : Declaration of the CProvider

#pragma once
#include "resource.h"       // main symbols



#include "CredDemo_i.h"
#include "Configuration.h"
#include <memory>



#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

using namespace ATL;

class CCredential;

// CProvider


class ATL_NO_VTABLE CProvider : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CProvider, &CLSID_Provider>,
	public ICredentialProvider
{
public:
	CProvider();
	~CProvider();

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CProvider)
	COM_INTERFACE_ENTRY(ICredentialProvider)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(SetUsageScenario)(CREDENTIAL_PROVIDER_USAGE_SCENARIO, DWORD);
	STDMETHOD(SetSerialization)(const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION*);
	STDMETHOD(Advise)(ICredentialProviderEvents*, UINT_PTR);
	STDMETHOD(UnAdvise)();
	STDMETHOD(GetFieldDescriptorCount)(DWORD*);
	STDMETHOD(GetFieldDescriptorAt)(DWORD, CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR**);
	STDMETHOD(GetCredentialCount)(DWORD*, DWORD*, BOOL*);
	STDMETHOD(GetCredentialAt)(DWORD, ICredentialProviderCredential**);

private:
	CREDENTIAL_PROVIDER_USAGE_SCENARIO m_cpus = CPUS_INVALID;
	DWORD m_dwUsageFlags = 0;

	CComPtr<ICredentialProviderEvents> m_lpEvents;
	ULONG_PTR m_ulCookie = 0;

	CComPtr<CCredential> m_pCredential;

	std::shared_ptr<Configuration> m_config;

};

OBJECT_ENTRY_AUTO(__uuidof(Provider), CProvider)

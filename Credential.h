#pragma once

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Single-threaded COM objects are not properly supported on Windows CE platform, such as the Windows Mobile platforms that do not include full DCOM support. Define _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA to force ATL to support creating single-thread COM object's and allow use of it's single-threaded COM object implementations. The threading model in your rgs file was set to 'Free' as that is the only threading model supported in non DCOM Windows CE platforms."
#endif

#include "common.h"
#include "scenario.h"
#include "Configuration.h"
#include "Utilities.h"
#include <memory>

using namespace ATL;

class ATL_NO_VTABLE CCredential :
	public CComObjectRootEx<CComSingleThreadModel>,
	public IConnectableCredentialProviderCredential
{
public:
	CCredential();
	~CCredential();

	BEGIN_COM_MAP(CCredential)
		COM_INTERFACE_ENTRY(IConnectableCredentialProviderCredential)
		COM_INTERFACE_ENTRY(ICredentialProviderCredential)
	END_COM_MAP()


	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

	static HRESULT CreateCredential(std::shared_ptr<Configuration> config, CCredential** ppCredential);

	// ICredentialProviderCredential
	STDMETHOD(Advise)(ICredentialProviderCredentialEvents* pcpce);
	STDMETHOD(UnAdvise)();
	STDMETHOD(SetSelected)(BOOL* pbSelected);
	STDMETHOD(SetDeselected)();
	STDMETHOD(GetFieldState)(DWORD dwIndex, CREDENTIAL_PROVIDER_FIELD_STATE* pcpfs, CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE* pcpfis);
	STDMETHOD(GetStringValue)(DWORD dwIndex, LPWSTR* psValue);
	STDMETHOD(GetBitmapValue)(DWORD dwIndex, HBITMAP* phBitmap);
	STDMETHOD(GetCheckboxValue)(DWORD dwIndex, BOOL* pbChecked, LPWSTR* psLabel);
	STDMETHOD(GetSubmitButtonValue)(DWORD dwIndex, DWORD* pdwNextTo);
	STDMETHOD(GetComboBoxValueCount)(DWORD dwIndex, DWORD*, DWORD*);
	STDMETHOD(GetComboBoxValueAt)(DWORD dwIndex, DWORD, LPWSTR*);
	STDMETHOD(SetStringValue)(DWORD dwIndex, LPCWSTR);
	STDMETHOD(SetCheckboxValue)(DWORD dwIndex, BOOL);
	STDMETHOD(SetComboBoxSelectedValue)(DWORD dwIndex, DWORD);
	STDMETHOD(CommandLinkClicked)(DWORD dwIndex);
	STDMETHOD(GetSerialization)(CREDENTIAL_PROVIDER_GET_SERIALIZATION_RESPONSE*, CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION*, LPWSTR*, CREDENTIAL_PROVIDER_STATUS_ICON*);
	STDMETHOD(ReportResult)(NTSTATUS, NTSTATUS, LPWSTR*, CREDENTIAL_PROVIDER_STATUS_ICON*);

	// IConnectableCredentialProviderCredential

	STDMETHOD(Connect)(IQueryContinueWithStatus* pContinue);
	STDMETHOD(Disconnect)();

	void Initialize(const FIELD_STATE_PAIR* pfsp, size_t count);

protected:
	HRESULT ReadFields();
	HRESULT ReadUsername();
	HRESULT ReadPassword();

private:
	CComPtr<ICredentialProviderCredentialEvents> m_lpCredentialEvents;


	secure_wstring m_FieldStrings[FID_COUNT];
	FIELD_STATE_PAIR m_FieldStates[FID_COUNT];

	std::shared_ptr<Configuration> m_config;

};


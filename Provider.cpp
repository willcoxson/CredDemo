// Provider.cpp : Implementation of CProvider

#include "pch.h"
#include "Provider.h"
#include "Credential.h"
#include "scenario.h"
#include "helpers.h"
#include "AutoUtilities.h"
#include "extras.h"
#include <LM.h>


// __FILE__ "  "   L" : " __LINE__



using namespace std;

CProvider::CProvider()
{
}

CProvider::~CProvider()
{
	START_METHOD;
}


// CProvider
HRESULT __stdcall CProvider::SetUsageScenario(CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus, DWORD dwFlags)
{
	START_COM_METHOD;
	m_cpus = cpus;
	m_dwUsageFlags = dwFlags;

	LOG_INFO(wstring(L"Usage scenario: ") + to_wstring(cpus));

	if (!m_config) m_config = std::make_shared<Configuration>(cpus, dwFlags);
	SET_LOG_LEVEL(6);

	// only want to test UAC so CPUS_CREDUI is the only one allowed
	if (cpus != CPUS_CREDUI)
		return E_NOTIMPL;

	return S_OK;

	END_COM_METHOD;
}

HRESULT __stdcall CProvider::SetSerialization(const CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION*)
{
	START_COM_METHOD;

	return E_NOTIMPL;
	
	END_COM_METHOD
}

STDMETHODIMP_(HRESULT __stdcall) CProvider::Advise(ICredentialProviderEvents* lpEvents, UINT_PTR ulCookie)
{
	START_COM_METHOD;

	m_lpEvents = lpEvents;
	m_ulCookie = ulCookie;
	return S_OK;

	END_COM_METHOD
}

STDMETHODIMP_(HRESULT __stdcall) CProvider::UnAdvise()
{
	START_COM_METHOD;

	if (m_lpEvents)
	{
		m_lpEvents.Release();
	}
	return S_OK;

	END_COM_METHOD
}

STDMETHODIMP_(HRESULT __stdcall) CProvider::GetFieldDescriptorCount(DWORD* pdwCount)
{
	START_COM_METHOD;

	if (pdwCount == NULL)
		return E_POINTER;

	*pdwCount = FID_COUNT;

	return S_OK;

	END_COM_METHOD
}

STDMETHODIMP_(HRESULT __stdcall) CProvider::GetFieldDescriptorAt(DWORD dwIndex, CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR** ppcpfd)
{
	START_COM_METHOD_FIELD_INDEX(dwIndex);

	if (ppcpfd == nullptr)
		return E_POINTER;
	*ppcpfd = nullptr;

	if (dwIndex >= FID_COUNT)
		return E_INVALIDARG;

	HRESULT hr = FieldDescriptorCoAllocCopy(g_FieldDescriptors[dwIndex], ppcpfd);
	return hr;

	END_COM_METHOD;
}

STDMETHODIMP_(HRESULT __stdcall) CProvider::GetCredentialCount(DWORD* pdwCount, DWORD* pdwDefault, BOOL* pbAutoLogonWithDefault)
{
	START_COM_METHOD;

	if (pdwCount == nullptr || pdwDefault == nullptr || pbAutoLogonWithDefault == nullptr)
		return E_INVALIDARG;

	*pdwCount = 1;
	*pdwDefault = CREDENTIAL_PROVIDER_NO_DEFAULT;
	*pbAutoLogonWithDefault = FALSE;

	return S_OK;
	END_COM_METHOD
}


std::wstring GetComputerDomain()
{
	wstring wsDomainName;
	LPWSTR pwstr = nullptr;
	NETSETUP_JOIN_STATUS join_status;

	if (NERR_Success == NetGetJoinInformation(nullptr, &pwstr, &join_status) && nullptr != pwstr )
	{
		wsDomainName = pwstr;
		NetApiBufferFree(pwstr);
	}
	return wsDomainName;
}

std::wstring GetComputerDnsDomain()
{
	WCHAR szBuf[MAX_PATH] = { 0 };
	DWORD dwBuf = _countof(szBuf);
	::GetComputerNameEx(ComputerNameDnsDomain, szBuf, &dwBuf);
	return szBuf;
}

STDMETHODIMP_(HRESULT __stdcall) CProvider::GetCredentialAt(DWORD dwIndex, ICredentialProviderCredential**  ppCredential)
{
	START_COM_METHOD;

	if (ppCredential == nullptr)
		return E_POINTER;

	*ppCredential = nullptr;

	if (dwIndex != 0)
		return E_INVALIDARG;

	HRESULT hr = E_FAIL;
	
	if (m_pCredential == nullptr)
	{
		hr = CCredential::CreateCredential(m_config, &m_pCredential);
		if (FAILED(hr))
			LOG_ERROR(L"Could not create credential.");
		if (SUCCEEDED(hr))
			m_pCredential->Initialize(g_FieldStatePairs, _countof(g_FieldStatePairs));

		auto domain = GetComputerDomain();
		m_config->credential.domain = domain;
	}

	if (m_pCredential)
	{
		hr = m_pCredential.QueryInterface(ppCredential);
		if (SUCCEEDED(hr))
			LOG_INFO(L"Returning Credential at index: " + to_wstring(dwIndex));
	}

	return hr;
	END_COM_METHOD
}

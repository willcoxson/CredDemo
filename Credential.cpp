#include "pch.h"
#include "Credential.h"
#include "scenario.h"
#include "AutoUtilities.h"
#include <atlstr.h>

using namespace std;

std::wstring to_wstring(FIELD_ID fid)
{
    switch (fid)
    {
#if USE_FID_LOGO == 1
    case FID_LOGO:
        return L"FID_LOGO";
#endif
#if USE_FID_LARGE_TEXT
case FID_LARGE_TEXT:
        return L"FID_LARGE_TEXT";
#endif
    case FID_SMALL_TEXT:
        return L"FID_SMALL_TEXT";
    case FID_PASSWORD:
        return L"FID_PASSWORD";
    case FID_USERNAME:
        return L"FID_USERNAME";
#if USE_FID_SUBMIT == 1
    case FID_SUBMIT:
        return L"FID_SUBMIT";
#endif
    }

    return L"ERROR BAD INDEX";
}



CCredential::CCredential()
{
#if USE_FID_LARGE_TEXT
    m_FieldStrings[FID_LARGE_TEXT] = L"Credential Test (l)";
#endif
    m_FieldStrings[FID_SMALL_TEXT] = L"Credential Test (s)";
}

CCredential::~CCredential()
{
    START_METHOD;
}

HRESULT CCredential::CreateCredential(std::shared_ptr<Configuration> config, CCredential** ppCredential)
{

    CComObject<CCredential>* pCred = nullptr;

    HRESULT hr;
    if (FAILED(hr = CComObject<CCredential>::CreateInstance(&pCred)))
        return hr;

    pCred->AddRef();

    *ppCredential = pCred;

    pCred->m_config = config;

    return hr;
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::Advise(ICredentialProviderCredentialEvents* pcpce)
{
    START_COM_METHOD;
    m_lpCredentialEvents = pcpce;
    return S_OK;
    END_COM_METHOD;
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::UnAdvise()
{
    START_COM_METHOD;
    m_lpCredentialEvents.Release();
    return S_OK;
    END_COM_METHOD;
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::SetSelected(BOOL* pbAutoLogon)
{
    START_COM_METHOD;

    *pbAutoLogon = FALSE; // not checking ... ours doesnt check
    HRESULT hr = S_OK;
    return hr;
    END_COM_METHOD;
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::SetDeselected()
{
    START_COM_METHOD;

    for (auto s : m_FieldStrings)
    {
        s.clear();
    }
    return S_OK;

    END_COM_METHOD;
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::GetFieldState(DWORD dwIndex, CREDENTIAL_PROVIDER_FIELD_STATE* pcpfs, CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE* pcpfis)
{
    START_COM_METHOD_FIELD_INDEX(dwIndex);
    if (dwIndex >= FID_COUNT || pcpfs == NULL || pcpfis == NULL)
        return E_INVALIDARG;

    const auto& fsp = g_FieldStatePairs[dwIndex];
    *pcpfs = fsp.cpfs;
    *pcpfis = fsp.cpfis;

    return S_OK;

    END_COM_METHOD
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::GetStringValue(DWORD dwIndex, LPWSTR* pszValue)
{
    START_COM_METHOD_FIELD_INDEX(dwIndex);

    if (dwIndex >= FID_COUNT || pszValue == nullptr)
        return E_INVALIDARG;


    HRESULT hr= SHStrDupW(m_FieldStrings[dwIndex].c_str(), pszValue);
    if (!FAILED(hr))
        LOG_DEBUG(wstring(L"String value: ") + *pszValue);

    return hr;

    END_COM_METHOD
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::GetBitmapValue(DWORD dwIndex, HBITMAP* phBitmap)
{
    START_COM_METHOD_FIELD_INDEX(dwIndex);

    if (phBitmap == nullptr)
        return E_POINTER;

    *phBitmap = nullptr;

#if USE_FID_LOGO == 1
    if (dwIndex != FID_LOGO)
       return E_INVALIDARG;
#else
    return E_INVALIDARG;
#endif

    HRESULT hr;

    HBITMAP hbmp{ nullptr };

    hbmp = LoadBitmap(_AtlBaseModule.GetModuleInstance(), MAKEINTRESOURCE(IDB_NEW_TILE));

    if (hbmp != NULL)
    {
        hr = S_OK;
        *phBitmap = hbmp;
        LOG_DEBUG(L"Returning BITMAP");
    }
    else
    {
        hr = HRESULT_FROM_WIN32(GetLastError());
    }

    return hr;
    END_COM_METHOD
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::GetCheckboxValue(DWORD dwIndex, BOOL* pbChecked, LPWSTR* psLabel)
{
    START_COM_METHOD;
    return E_INVALIDARG;
    END_COM_METHOD;
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::GetSubmitButtonValue(DWORD dwIndex, DWORD* pdwNextTo)
{
    START_COM_METHOD_FIELD_INDEX(dwIndex);
    if (!pdwNextTo)
        return E_POINTER;

    HRESULT hr = E_INVALIDARG;
#if USE_FID_SUBMIT == 1
    if (dwIndex == FID_SUBMIT)
    {
        *pdwNextTo = FID_PASSWORD;
        hr = S_OK;
    }
#endif
    return hr;

    END_COM_METHOD;
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::GetComboBoxValueCount(DWORD dwIndex, DWORD*, DWORD*)
{
    START_COM_METHOD;
    return E_INVALIDARG;
    END_COM_METHOD;
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::GetComboBoxValueAt(DWORD dwIndex, DWORD, LPWSTR*)
{
    START_COM_METHOD;
    return E_INVALIDARG;
    END_COM_METHOD;
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::SetStringValue(DWORD dwIndex, LPCWSTR pszValue)
{
    START_COM_METHOD_FIELD_INDEX(dwIndex);

    if (dwIndex >= FID_COUNT)
        return E_INVALIDARG;

    m_FieldStrings[dwIndex] = pszValue != nullptr ? pszValue : L"";
    return S_OK;

    END_COM_METHOD;
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::SetCheckboxValue(DWORD dwIndex, BOOL)
{
    START_COM_METHOD;
    return E_INVALIDARG;
    END_COM_METHOD;
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::SetComboBoxSelectedValue(DWORD dwIndex, DWORD)
{
    START_COM_METHOD;
    return E_INVALIDARG;
    END_COM_METHOD;
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::CommandLinkClicked(DWORD dwIndex)
{
    START_COM_METHOD;

    return E_INVALIDARG;

    END_COM_METHOD;
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::GetSerialization(CREDENTIAL_PROVIDER_GET_SERIALIZATION_RESPONSE* pcpgsr, CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION* pcpcs, LPWSTR*, CREDENTIAL_PROVIDER_STATUS_ICON*)
{
    START_COM_METHOD;
    *pcpgsr = CPGSR_RETURN_NO_CREDENTIAL_FINISHED;
    HRESULT hr = S_FALSE;


    wstring usernameToUse = m_config->credential.username;
    wstring domainToUse = m_config->credential.domain;
    auto passwordToUse = m_config->credential.password;

    LOG_INFO(wstring(L"Username: ") + usernameToUse);

    if (m_config->provider.cpus == CPUS_CREDUI)
    {
        *pcpgsr = CPGSR_RETURN_CREDENTIAL_FINISHED;

        hr = CredPackAuthentication(pcpgsr, pcpcs, m_config->provider.cpus, m_config->provider.credPackFlags,
            usernameToUse, passwordToUse, domainToUse);
    }


    return hr;
    END_COM_METHOD;
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::ReportResult(NTSTATUS, NTSTATUS, LPWSTR*, CREDENTIAL_PROVIDER_STATUS_ICON*)
{
    START_COM_METHOD;
    
    return E_NOTIMPL;

    END_COM_METHOD;
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::Connect(IQueryContinueWithStatus* pContinue)
{
    START_COM_METHOD;

    ReadFields();

    return S_OK;
    END_COM_METHOD;
}

STDMETHODIMP_(HRESULT __stdcall) CCredential::Disconnect()
{
    START_COM_METHOD;

    return S_OK;
    END_COM_METHOD;
}

void CCredential::Initialize(const FIELD_STATE_PAIR* pfsp, size_t count)
{
    for (size_t i = 0; i < count; ++i)
    {
        m_FieldStates[i] = pfsp[i];
    }
}


HRESULT CCredential::ReadFields()
{
    START_METHOD;
    switch (m_config->provider.cpus)
    {
    case CPUS_CREDUI:
    {
        ReadUsername();
        ReadPassword();
    } break;
    }
    END_METHOD_HR(S_OK);
}

HRESULT CCredential::ReadUsername()
{
    START_METHOD;

    wstring input(m_FieldStrings[FID_USERNAME].c_str());
    LOG_VERBOSE(L"Loading user/domain from GUI, raw: '" + input + L"'");
    wstring user_name, domain_name;

    auto const pos = input.find_first_of(L"\\", 0);
    if (pos == std::string::npos)
    {
        // only user input, copy string
        user_name = wstring(input);
    }
    else
    {
        // Actually split DOMAIN\USER
        user_name = wstring(input.substr(pos + 1, input.size()));
        domain_name = wstring(input.substr(0, pos));
    }

    auto& credData = m_config->credential;
    if (!user_name.empty())
    {
        wstring newUsername(user_name);
        LOG_VERBOSE(L"Changing user from '" + credData.username + L"' to '" + newUsername + L"'");
        credData.username = newUsername;
    }
    else
    {
        LOG_VERBOSE(L"Username is empty, keeping old value: '" + credData.username + L"'");
    }

    if (!domain_name.empty() || pos == 0)
    {
        wstring newDomain(domain_name);
        LOG_VERBOSE(L"Changing domain from '" + credData.domain + L"' to '" + newDomain + L"'");
        credData.domain = newDomain;
    }
    else
    {
        LOG_VERBOSE(L"Domain is empty, keeping old value: '" + credData.domain + L"'");
    }
    END_METHOD_HR(S_OK);
}


HRESULT CCredential::ReadPassword()
{
    START_METHOD;

    auto& credData = m_config->credential;
    secure_wstring newPassword(m_FieldStrings[FID_PASSWORD]);

    if (newPassword.empty())
    {
        LOG_VERBOSE("New password empty, keeping old value");
    }
    else
    {
        LOG_VERBOSE(L"Loading password from GUI, value:");
        credData.password = newPassword;
    }
    END_METHOD_HR(S_OK);
}
#pragma once

#include "common.h"
#include "Configuration.h"
#include <memory>

#define MAX_SIZE_DOMAIN 64

HRESULT CredPackAuthentication(
	__out CREDENTIAL_PROVIDER_GET_SERIALIZATION_RESPONSE*& pcpgsr,
	__out CREDENTIAL_PROVIDER_CREDENTIAL_SERIALIZATION*& pcpcs,
	__in CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus,
	__in DWORD credPackFlags,
	__in std::wstring username,
	__in SecureWString password,
	__in std::wstring domain);

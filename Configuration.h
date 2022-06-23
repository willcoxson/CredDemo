#pragma once

#include <vector>

#include "scenario.h"
#include "common.h"

struct Configuration
{

	Configuration(CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus, DWORD dwFlags)
	{
		provider.cpus = cpus;
		provider.credPackFlags = dwFlags;
	}

	struct PROVIDER_
	{

		CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus;
		DWORD credPackFlags;

	} provider;

	struct CREDENTIAL_
	{

		std::wstring username;
		secure_wstring password;
		std::wstring domain;

	} credential;
};


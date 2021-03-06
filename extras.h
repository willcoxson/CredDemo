#pragma once

#include <string>
#include <credentialprovider.h>

std::wstring to_wstring(CREDENTIAL_PROVIDER_USAGE_SCENARIO cpus)
{
    switch (cpus)
    {
    case CREDENTIAL_PROVIDER_USAGE_SCENARIO::CPUS_INVALID:
        return L"CPUS_INVALID";
    case CREDENTIAL_PROVIDER_USAGE_SCENARIO::CPUS_CREDUI:
        return L"CPUS_CREDUI";
    case CREDENTIAL_PROVIDER_USAGE_SCENARIO::CPUS_CHANGE_PASSWORD:
        return L"CPUS_CHANGE_PASSWORD";
    case CREDENTIAL_PROVIDER_USAGE_SCENARIO::CPUS_LOGON:
        return L"CPUS_LOGON";
    case CREDENTIAL_PROVIDER_USAGE_SCENARIO::CPUS_PLAP:
        return L"CPUS_PLAP";
    case CREDENTIAL_PROVIDER_USAGE_SCENARIO::CPUS_UNLOCK_WORKSTATION:
        return L"CPUS_UNLOCK_WORKSTATION";
    default:
        return L"ERROR CPUS";
    }
}
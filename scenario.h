#pragma once

#define USE_FID_LOGO 1
#define USE_FID_LARGE_TEXT 0
#define USE_FID_SUBMIT 0 // generally not needed for CREDUI ... because UAC or other dialogs have an OK button


enum FIELD_ID
{
#if USE_FID_LOGO == 1
	  FID_LOGO,
#endif
#if USE_FID_LARGE_TEXT == 1
    FID_LARGE_TEXT,
#endif
    FID_SMALL_TEXT,
	FID_USERNAME,
	FID_PASSWORD,
#if USE_FID_SUBMIT == 1
	FID_SUBMIT,
#endif
	FID_COUNT
};

struct FIELD_STATE_PAIR
{
	CREDENTIAL_PROVIDER_FIELD_STATE cpfs;
	CREDENTIAL_PROVIDER_FIELD_INTERACTIVE_STATE cpfis;
};

static const FIELD_STATE_PAIR g_FieldStatePairs[FID_COUNT] =
{
#if USE_FID_LOGO == 1
    { CPFS_DISPLAY_IN_BOTH, CPFIS_NONE },                   // FID_LOGO
#endif
#if USE_FID_LARGE_TEXT
    { CPFS_DISPLAY_IN_BOTH, CPFIS_NONE },                   // FID_LARGE_TEXT
#endif
    { CPFS_DISPLAY_IN_BOTH, CPFIS_NONE },                            // FID_SMALL_TEXT
    { CPFS_DISPLAY_IN_SELECTED_TILE, CPFIS_FOCUSED },       // FID_USERNAME   
    { CPFS_DISPLAY_IN_SELECTED_TILE, CPFIS_NONE },          // FID_PASSWORD
#if USE_FID_SUBMIT == 1
    { CPFS_DISPLAY_IN_SELECTED_TILE, CPFIS_NONE },       // FID_SUBMIT
#endif
};

static const CREDENTIAL_PROVIDER_FIELD_DESCRIPTOR g_FieldDescriptors[FID_COUNT] =
{
#if USE_FID_LOGO == 1
    { FID_LOGO, CPFT_TILE_IMAGE, L"Image" },
#endif
#if USE_FID_LARGE_TEXT == 1
    { FID_LARGE_TEXT, CPFT_LARGE_TEXT, L"LargeText" },
#endif
    { FID_SMALL_TEXT, CPFT_SMALL_TEXT, L"SmallText" },
    { FID_USERNAME, CPFT_EDIT_TEXT, L"Username" },
    { FID_PASSWORD, CPFT_PASSWORD_TEXT, L"Password" },
#if USE_FID_SUBMIT == 1
    { FID_SUBMIT, CPFT_SUBMIT_BUTTON, L"Submit" },
#endif
};

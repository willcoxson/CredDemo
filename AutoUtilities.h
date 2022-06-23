#pragma once

#include "EventsLogger.h"


#define START_COM_METHOD \
try { \
   START_METHOD

#define START_COM_METHOD_INDEX(x)\
try { \
	LOG_DEBUG(wstring(L"START" __FUNCTION__ " [") + to_wstring(x) + L"]"  )
	

#define END_COM_METHOD \
} catch (...) { \
	LOG_ERROR(L"Uncaught exception: " __FILE__ ); \
	return E_FAIL; \
}

std::wstring to_wstring(FIELD_ID fid);

#define START_COM_METHOD_FIELD_INDEX(x) \
try { \
	LOG_DEBUG(wstring(L"START" __FUNCTION__ " [") + to_wstring(static_cast<FIELD_ID>(x)) + L"]"  )

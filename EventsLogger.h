#pragma once

#include "common.h"

#undef LOG_ERROR
#define LOG_ERROR(message)

#undef LOG_WARNING
#define LOG_WARNING(message)

#undef LOG_INFO
#define LOG_INFO(message)

#undef LOG_DETAILED
#define LOG_DETAILED(message)

#undef LOG_VERBOSE
#define LOG_VERBOSE(message)

#undef LOG_DEBUG
#define LOG_DEBUG(message)

#undef SET_LOG_LEVEL
#define SET_LOG_LEVEL(n)

#undef START_METHOD
#define START_METHOD

#undef END_METHOD
#define END_METHOD

#undef END_METHOD_HR
#define END_METHOD_HR(hr) return hr

#pragma once

#define LOG_LEVEL_FATAL _T("FATAL")
#define LOG_LEVEL_ERROR _T("ERROR")
#define LOG_LEVEL_WARN _T("WARN")
#define LOG_LEVEL_INFO _T("INFO")
#define LOG_LEVEL_DEBUG _T("DEBUG")

#define LOG(LEVEL, FMT, ARGS) { CAtlString msg(_T("html5i ") LEVEL _T(" ")); msg.AppendFormat(FMT, ARGS); ::OutputDebugString(msg); }

#define LOG_FATAL(FMT, ...) LOG(LOG_LEVEL_FATAL, FMT, __VA_ARGS__)
#define LOG_ERROR(FMT, ...) LOG(LOG_LEVEL_ERROR, FMT, __VA_ARGS__)
#define LOG_WARN(FMT, ...) LOG(LOG_LEVEL_WARN, FMT, __VA_ARGS__)
#define LOG_INFO(FMT, ...) LOG(LOG_LEVEL_INFO, FMT, __VA_ARGS__)

#ifdef _DEBUG
#define LOG_DEBUG(FMT, ...) LOG(LOG_LEVEL_DEBUG, FMT, __VA_ARGS__)
#else
#define LOG_DEBUG(FMT, ...) 
#endif

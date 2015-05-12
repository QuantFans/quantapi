#ifndef QUANTDIGGER_UTIL_DEFINITION_H
#define QUANTDIGGER_UTIL_DEFINITION_H

#include <ctime>
#include <stdio.h>

#ifdef _WIN32			//vc 需采用自身提供的安全api，否则会有警告
#define snprintf _snprintf
#define sscanf	sscanf_s
#define vsnprintf(dst, size, fmt, ap) vsnprintf_s(dst, size, size, fmt, ap)
//#define strcat(dst,src) strcat_s(dst, strlen(dst), src)
//#define strcpy(dst,src) strcpy_s(dst, strlen(dst), src)

//tm* win32_localtime_t(const time_t* _t);

//#ifndef localtime
//#define localtime win32_localtime_t
//#endif // localtime

# endif // _WIN32	

#endif //QUANTDIGGER_UTIL_DEFINITION_H

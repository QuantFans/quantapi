#include "Functions.h" 
#include <iomanip>
#include <ctime>
#include "log_assert.h" 
#include "definition.h"
namespace QuantDigger {
namespace Util {

void ctpStrDate2Tm(const char* str, tm *t) {
    LOG_ASSERT(str && t);
    sscanf(str, "%4d" , &(t->tm_year));
    sscanf(str + 4 , "%2d" , &(t->tm_mon));
    sscanf(str + 6 , "%2d" , &(t->tm_mday));
    t->tm_year -= 1900;
    t->tm_mon -= 1;
}

void ctpStrTime2Tm(const char* str, tm *t) {
    LOG_ASSERT(str && t);
    sscanf(str, "%2d" , &(t->tm_hour));
    sscanf(str + 3, "%2d" , &(t->tm_min));
    sscanf(str + 6, "%2d" , &(t->tm_sec));
}

DateTime strDateTime2TimePoint(const char* str) {
    LOG_ASSERT(str);
    tm t;
    sscanf(str, "%4d" , &(t.tm_year));
    sscanf(str + 5 , "%2d" , &(t.tm_mon));
    sscanf(str + 8 , "%2d" , &(t.tm_mday));
    t.tm_year -= 1900;
    t.tm_mon -= 1;
    sscanf(str + 11, "%2d" , &(t.tm_hour));
    sscanf(str + 14, "%2d" , &(t.tm_min));
    sscanf(str + 17, "%2d" , &(t.tm_sec));
    return std::chrono::system_clock::from_time_t(mktime(&t));
}
    
void formatTime(const DateTime &dt, 
                char *buffer, 
                int n,
                const char* fmt) {
    using std::chrono::system_clock;
    DateTime temp = dt;
    int millisec = millisecondsOfDateTime(dt);
    /// @todo 不知道在windows平台上，是不是也是这样的。
    /// @note gcc 用负数表示毫秒！所以显示的时候要矫正时间，如果毫秒为负，则也该减去一秒。
    if(millisec < 0) {
       temp -= std::chrono::seconds(1); 
       millisec = 0-millisec;
    }
    LOG_ASSERT(buffer);
    std::time_t tt =  system_clock::to_time_t (temp);
	std::tm *ptm = NULL;
#ifdef WIN32
	ptm = new std::tm;
	localtime_s(ptm, &tt);
#else
	ptm = localtime(&tt);
#endif
    // std::put_time 函数在gcc4.8中还未实现
    snprintf(buffer, n, fmt, ptm->tm_year+1900, ptm->tm_mon+1,
             ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
#ifdef WIN32
	delete ptm;
#endif
}

void formatTimeWithMilliseconds(const DateTime &dt, 
                char *buffer, 
                int n,
                const char* fmt) {
    using std::chrono::system_clock;
    DateTime temp = dt;
    int millisec = millisecondsOfDateTime(dt);
    /// @todo 不知道在windows平台上，是不是也是这样的。
    /// @note gcc 用负数表示毫秒！所以显示的时候要矫正时间，如果毫秒为负，则也该减去一秒。
    if(millisec < 0) {
       temp -= std::chrono::seconds(1); 
       millisec = 0-millisec;
    }
    LOG_ASSERT(buffer);
    std::time_t tt =  system_clock::to_time_t (temp);
    std::tm *ptm =  localtime(&tt);
    // std::put_time 函数在gcc4.8中还未实现
    snprintf(buffer, n, fmt, ptm->tm_year+1900, ptm->tm_mon+1,
             ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, millisec);
}


void split(const std::string& str, std::vector<std::string>* tokens,
           char delimiter, bool trimEmpty)
{
    std::string::size_type pos, lastPos =  0;
    while(true)
    {
        pos = str.find_first_of(delimiter, lastPos);
        if(pos == std::string::npos)
        {
            pos = str.length();
            tokens->push_back(std::string(str.data()+lastPos, pos-lastPos));
            break;
        }
        else
        {
            if(pos != lastPos || !trimEmpty)
                tokens->push_back(std::string(str.data()+lastPos, pos-lastPos));
        }
        lastPos = pos + 1;
    }
};

std::vector<std::string> split(const std::string &str, char delimiter, bool trimEmpty) {
    std::vector<std::string> temp;
    split(str, &temp, delimiter, trimEmpty);
    return temp;
}

std::string formatString(const char *fmt, ...) {
    // 默认大小，可自己扩大。
    int size = 1024;
    std::string str;
    va_list ap;
    while (true) {
        str.resize(size);
        va_start(ap, fmt);
        int n = vsnprintf((char *)str.c_str(), size, fmt, ap);
        va_end(ap);
        if (n > -1 && n < size) {
            str.resize(n);
            return str;
        }
        if (n > -1)
            size = n+1;
        else
            size*=2;
    }
}

} /* Util */
} /* QuantDigger */

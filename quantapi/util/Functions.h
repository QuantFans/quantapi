/**
 * @file Functions.h
 * @brief 
 * @author WDJ(dingjie.wang@gmail.com)
 * @version 0.1
 * @date 2014-06-12
 */

#ifndef QUANTDIGGER_UTIL_FUNCTIONS_H

#define QUANTDIGGER_UTIL_FUNCTIONS_H
#include <chrono>
#include <cstring>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <string>
#include "log_assert.h"
#include "definition.h"
#include "Exceptions.h" 
namespace QuantDigger {
namespace Util {
typedef std::chrono::system_clock::time_point DateTime;

inline int lexical_cast(const std::string& arg)
{
    char* stop;
    int res = strtol( arg.c_str(), &stop, 10 );
    if ( *stop != 0 ) throw RuntimeException();
    return res;
}

inline std::string lexical_cast(const int& arg)
{
    char buffer[20]; 
    //            itoa( arg, buffer, 10 );
    sprintf(buffer, "%i", arg);
    return std::string( buffer );
}

//! an simple function convert other types to string, not very efficient, but good enough 
template < typename T >
inline std::string sth2string(T i){
    std::stringstream ss;
    ss<<i;
    return ss.str();
}

//! the inverse of #sth2string
template < typename T >
inline T string2sth(const std::string& str){
    T val;
    std::stringstream ss(str);
    ss>>val;
    return val;
}
    
class TimeSpan{
 public:
    inline void mark() { start_ = std::chrono::high_resolution_clock::now(); }
    /**
     * @brief   
     *
     * @tparam TimeUnit ������ʱ�䵥λ��
     */
    template <typename TimeUnit>
    int timeSpan() {
        return std::chrono::duration_cast<TimeUnit>(std::chrono::high_resolution_clock::now() - start_).count();
    }
    /** @brief �������뾫�ȼ���ĺ������� */
    float timeSpanHighResolution() {
        return timeSpan<std::chrono::nanoseconds>() / float(1000000);
    }

    template < typename TimeUnit>
    static int timeDiff(const std::chrono::high_resolution_clock::time_point &t1, 
                 const std::chrono::high_resolution_clock::time_point &t0) {
        return std::chrono::duration_cast<TimeUnit>(t1 - t0).count();            
    }


 private:
    std::chrono::high_resolution_clock::time_point start_;
};


/**
 * @brief �ַ�������ת��Ϊtm
 *
 * @param str �ַ�������(20140323)
 * @param t tm���ݽṹ
 */
void ctpStrDate2Tm(const char* str, tm *t);

/**
 * @brief �ַ���ʱ��ת��Ϊtm
 *
 * @param str �ַ���ʱ��(14:02:31)
 * @param t tm���ݽṹ
 */
void ctpStrTime2Tm(const char* str, tm *t);

/**
 * @brief �ַ�������ʱ��ת��Ϊtime_point
 *
 * @param str �ַ���ʱ��(2014-02-03 14:02:31)���ָ���ſ����⣬�ַ�����>=19
 * @param t tm���ݽṹ
 */
DateTime strDateTime2TimePoint(const char* str);

/**
 * @brief ��time_pointת��Ϊ�ַ���, ʱ���ȴ��굽��
 *
 * @param dt ʱ��
 * @param buffer �������
 * @param n ��С���ȣ�buffer�н��洢n-1���ַ���Ĭ�ϵĸ�ʽҪ��nΪ20��
 * @param fmt ת����ʽ
 */
void formatTime(const DateTime &dt, 
                char *buffer, 
                int n=20, 
                const char* fmt="%.4d-%.2d-%.2d %.2d:%.2d:%.2d");

inline std::string formatTime(const DateTime &dt) {
    char buffer[20];
    memset(buffer, 0, 20);
    formatTime(dt, buffer);
    return std::string(buffer);
}

void formatTimeWithMilliseconds(const DateTime &dt, 
                char *buffer, 
                int n=24, 
                const char* fmt="%.4d-%.2d-%.2d %.2d:%.2d:%.2d.%.3d");

inline std::string formatTimeWithMilliseconds(const DateTime &dt) {
    char buffer[24];
    memset(buffer, 0, 24);
    formatTimeWithMilliseconds(dt, buffer);
    return std::string(buffer);
}



void split(const std::string& str, std::vector<std::string>* tokens,
           char delimiter=' ', bool trimEmpty=false);

std::vector<std::string> split(const std::string &str, 
                               char delimiter=' ', 
                               bool trimEmpty=false);

inline int millisecondsOfDateTime(const DateTime &dt) {
    // �����������������Ϊ45Ϊ���з���������������Ҳ���������
    return std::chrono::duration_cast<std::chrono::milliseconds>(dt.time_since_epoch()).count() % 1000;
}

inline void parseDateTime(const DateTime &dt, int *year, int *month, int *day, int *hour, int *min, int *sec) {
    time_t t = std::chrono::system_clock::to_time_t(dt);
	tm *ttm = localtime(&t);
    *year = ttm->tm_year + 1900;
    *month = ttm->tm_mon + 1;
    *day = ttm->tm_mday;
    *hour = ttm->tm_hour;
    *min = ttm->tm_min;
    *sec = ttm->tm_sec;
}



/**
 * @brief ÿ���̶���ѭ�����������ѭ�����ȡ�
 */
class EveryDisplay{
    public:
        EveryDisplay(int every):every_(every), count_(0), display_(0){ }
        void every_display (){
            display_++;
            count_++;
            if(display_ >= every_){
                // output the number of edges dealed with every 1000
                std::cout<<count_<<std::endl;
                display_ = 0;
            }
        }
        void reset(){
            count_ = 0;
            display_ = 0;
        }
    private:
        double count_;
        double display_;
        double every_;
};

template< class MapType >
    void printMap(const MapType & m)
    {
        typedef typename MapType::const_iterator const_iterator;
        for( const_iterator iter =  m.begin(), iend =  m.end(); iter != iend; ++iter ) {
            std::cout << iter->first << "-->" << iter->second << std::endl;
        }
    }

template < typename T >
void rank(const std::vector<T> &input, std::map<T, int> *rst){
    std::set<T> temp;
    for(auto &v : input){
        temp.insert(v); 
    }
    int rank = 0;
    // T -> int (rank)
    for(auto &v : temp){
        rst->insert(make_pair(v, rank++));
    }

}

template < typename T >
void sortIndex(const std::vector<T> &in, 
                std::map<T, int> *out)
{
    LOG_ASSERT(out);
    out->clear();
    for (int i = 0; i < in.size(); i++) {
        out->insert(std::make_pair(in[i], i));
    }
}

std::string formatString(const char *fmt, ...);

//inline std::string stringFormat(const char *fmt, ...) {
//    char buffer[1024];
//    memset(buffer, 0, 1024);
//    va_list args;
//    va_start(args, fmt);
//    snprintf(buffer, 1024, fmt, args);
//    va_end(args);
//    return std::string(buffer);
//}


} /* Util */
} /* QuantDigger */
#endif /* end of include guard: QUANTDIGGER_UTIL_FUNCTIONS_H */

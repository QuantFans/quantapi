#include <ctime>
#include "datastruct.h"
#include "mapping.h"

extern tm g_today;

using namespace QuantApi;
using namespace std;
    
std::vector<DateTime> 
Contract::getTradingTime(const Contract &contract) {
    /// @todo 从配置文件中读取
    std::vector<system_clock::time_point> rst;
    tm tm1 = g_today;
    char *morning_open_t = "09:00:00";
    char *morning_close_t = "11:30:00";
    char *afternoon_open_t = "13:30:00";
    char *afternoon_close_t = "15:00:00";
    Util::ctpStrTime2Tm(morning_open_t, &tm1);
    rst.push_back(system_clock::from_time_t(mktime(&tm1)));
    Util::ctpStrTime2Tm(morning_close_t, &tm1);
    rst.push_back(system_clock::from_time_t(mktime(&tm1)));
    Util::ctpStrTime2Tm(afternoon_open_t, &tm1);
    rst.push_back(system_clock::from_time_t(mktime(&tm1)));
    Util::ctpStrTime2Tm(afternoon_close_t, &tm1);
    rst.push_back(system_clock::from_time_t(mktime(&tm1)));
    return rst;
}

std::vector<std::string> 
Contract::getStrTradingTime(const Contract &contract) {
    std::vector<string> rst;
    rst.push_back("09:00:00");
    rst.push_back("11:30:00");
    rst.push_back("13:30:00");
    rst.push_back("15:00:00");
    return rst;
}

std::string Contract::toString() const {
   return std::string(map2ReadableExchType(exch_type)) + "--" + code; 
}

std::chrono::milliseconds Contract::tickPeriod(const Contract &contract) {
    // 500ms
    return std::chrono::milliseconds(500);
}

Price Contract::commission(const Contract &c, Price p, Volume v) {
    return 0;
}

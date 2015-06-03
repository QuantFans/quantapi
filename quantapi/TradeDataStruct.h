#ifndef _TRADEDATASTRUCT_H

#define _TRADEDATASTRUCT_H
#include <cassert>
#include <chrono>
#include <vector>
#include <string>
#include <mutex>
#include <iostream>
#include "ctp/ThostFtdcUserApiStruct.h" 
#include "../util/Functions.h"
#include "mapping.h" 

#define INVALID_NUMBER -1
namespace QuantDigger {

typedef char ExchType;
typedef std::chrono::system_clock::time_point DateTime;
typedef float Price;
typedef float Volume;            // 如果为int, 则无法放入NumberSeries变量中．
typedef float Number;
typedef std::vector<Number>::size_type size_type;
typedef std::chrono::duration<size_type, std::ratio<1,10>> TriggerTimeUnit; ///< 以100毫秒为单位的周期大小

/**
 * @brief 合约标识类。
 */
struct Contract {
    typedef std::chrono::system_clock system_clock;
    Contract() { }
    Contract(ExchType et, const std::string &c) {
        exch_type = et;
        code = c;
    }

    /** @brief 可读性强的合约标识符 */
    std::string toString() const {
       return std::string(map2ReadableExchType(exch_type)) + "--" + code; 
    }

    /// @todo 哈希成整数比较快！
    std::string id() const {
        return exch_type + std::string("_") + code;
    }

    bool operator < (const Contract &other) const{
        if(exch_type < other.exch_type)
            return true;
        else if(exch_type > other.exch_type)
            return false;
        else if(code < other.code)
            return true;
        else return false;
    }

     /** @brief 获取合约的交易时间 */
    static std::vector<DateTime> getTradingTime(const Contract &contract);
    static std::vector<std::string> getStrTradingTime(const Contract &contract);
    static Price commission(const Contract &c, Price p, Volume v);

    /** @brief tick触发周期 */
    static std::chrono::milliseconds tickPeriod(const Contract &contract);

    std::string code;       ///< 合约编码
    ExchType    exch_type;  ///< 交易所编码
}; 


/**
 * @brief tick数据, 统一封装了股票、期权、期货。
 */
struct TickData {
    TickData():price(INVALID_NUMBER), volume(0) { };
    /** @brief CTP tick数据转化为自定义格式 */
    explicit TickData(const CThostFtdcDepthMarketDataField *ctp_tick) {
        using namespace std::chrono;
        assert(ctp_tick);
        // 时间格式转化
        tm tm1;
        Util::ctpStrDate2Tm(ctp_tick->TradingDay, &tm1); // 如20140323
        Util::ctpStrTime2Tm(ctp_tick->UpdateTime, &tm1); // 如14:02:43
        // tick数据复制
        dt = system_clock::from_time_t(mktime(&tm1)) + milliseconds(ctp_tick->UpdateMillisec);
        price = ctp_tick->LastPrice;
        contract.code = std::string(ctp_tick->InstrumentID);
        contract.exch_type = map2QDExchType(ctp_tick->ExchangeID);
        millisec = ctp_tick->UpdateMillisec;
        volume = ctp_tick->Volume;
    }

    bool operator < (const TickData &other) const{
        if(contract < other.contract)
            return true;
        else return false;
    }

    std::string toString() const {
        return Util::formatString("Contract: %s | Price: %f | DateTime: %s.%.3d",
                                  contract.toString().c_str(),
                                  price,
                                  Util::formatTime(dt).c_str(),
                                  millisec
                                  );
    }
    TickData(const TickData &other) {
        *this = other;
    }
    TickData& operator = (const TickData &other) {
        contract = other.contract;
        price = other.price;      
        volume = other.volume;
        dt = other.dt;
        millisec = other.millisec;  
        create_time = other.create_time;
        return *this;
    }
    Contract    contract;
    Price       price;            // 当其为0时，表示tick数据是无效的。
    Volume      volume;
    DateTime    dt;
    int         millisec;  
    DateTime    create_time;    ///< 用于性能追踪，跟踪数据的流转时间。
    std::mutex  locker;
    // union
};
    
} /* QuantDigger */
#endif /* end of include guard: _TRADEDATASTRUCT_H */

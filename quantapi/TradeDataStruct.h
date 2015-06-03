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
typedef float Volume;            // ���Ϊint, ���޷�����NumberSeries�����У�
typedef float Number;
typedef std::vector<Number>::size_type size_type;
typedef std::chrono::duration<size_type, std::ratio<1,10>> TriggerTimeUnit; ///< ��100����Ϊ��λ�����ڴ�С

/**
 * @brief ��Լ��ʶ�ࡣ
 */
struct Contract {
    typedef std::chrono::system_clock system_clock;
    Contract() { }
    Contract(ExchType et, const std::string &c) {
        exch_type = et;
        code = c;
    }

    /** @brief �ɶ���ǿ�ĺ�Լ��ʶ�� */
    std::string toString() const {
       return std::string(map2ReadableExchType(exch_type)) + "--" + code; 
    }

    /// @todo ��ϣ�������ȽϿ죡
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

     /** @brief ��ȡ��Լ�Ľ���ʱ�� */
    static std::vector<DateTime> getTradingTime(const Contract &contract);
    static std::vector<std::string> getStrTradingTime(const Contract &contract);
    static Price commission(const Contract &c, Price p, Volume v);

    /** @brief tick�������� */
    static std::chrono::milliseconds tickPeriod(const Contract &contract);

    std::string code;       ///< ��Լ����
    ExchType    exch_type;  ///< ����������
}; 


/**
 * @brief tick����, ͳһ��װ�˹�Ʊ����Ȩ���ڻ���
 */
struct TickData {
    TickData():price(INVALID_NUMBER), volume(0) { };
    /** @brief CTP tick����ת��Ϊ�Զ����ʽ */
    explicit TickData(const CThostFtdcDepthMarketDataField *ctp_tick) {
        using namespace std::chrono;
        assert(ctp_tick);
        // ʱ���ʽת��
        tm tm1;
        Util::ctpStrDate2Tm(ctp_tick->TradingDay, &tm1); // ��20140323
        Util::ctpStrTime2Tm(ctp_tick->UpdateTime, &tm1); // ��14:02:43
        // tick���ݸ���
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
    Price       price;            // ����Ϊ0ʱ����ʾtick��������Ч�ġ�
    Volume      volume;
    DateTime    dt;
    int         millisec;  
    DateTime    create_time;    ///< ��������׷�٣��������ݵ���תʱ�䡣
    std::mutex  locker;
    // union
};
    
} /* QuantDigger */
#endif /* end of include guard: _TRADEDATASTRUCT_H */

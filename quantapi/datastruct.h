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

#define INVALID_NUMBER -1
namespace QuantApi {

typedef char ExchType;
typedef std::chrono::system_clock::time_point DateTime;
typedef float Price;
typedef float Volume;            // 如果为int, 则无法放入NumberSeries变量中．
typedef float Number;
typedef std::vector<Number>::size_type size_type;
typedef std::chrono::duration<size_type, std::ratio<1,10>> TriggerTimeUnit; ///< 以100毫秒为单位的周期大小

/**
 * @brief 成交方式。
 */
enum PriceType {
    kLimit,
    kMarket,
    kMilliseconds,
};

/**
 * @brief 投资类型
 */
enum HedgeType {
    kSpeculation,   ///< 投机
    kArbitrage,     ///< 套利
    kHedge          ///< 套保
};


/**
 * @brief 订单状态。
 */
enum OrderStatus {
    kOpen,       ///< 未成交
    kFilled,     ///< 已成交
    kCancelled   ///< 已撤销
};

/**
 * @brief 开平仓方向。
 */
enum Direction {
    LONG,
    SHORT
};

/**
 * @brief 开平仓标志 
 */
enum TradeSide {
   kBuy = 1, ///< 多头开仓
   kShort,  ///< 空头开仓
   kCover, ///< 空头平仓
   kSell, ///< 多头平仓
   kCoverToday, ///< 空头平今
   kSellToday, ///< 多头平今
   kKai, ///< 开仓
   kPing, ///< 平仓
   kPingToday //平今
};

/**
* @brief 投资者持仓日期类型
*/
enum PositionDate {
	psdToday,	//今日持仓
	psdHistory  //历史持仓
};

struct LogonInfo {
    LogonInfo(const char *bid, const char *uid, const char *pwd, const char* webuser = NULL) 
            :broker_id(bid), user_id(uid), password(pwd), web_user(webuser) { }
    const char *broker_id;
    const char *user_id;
    const char *password;
    const char *web_user;
};

/**
 * @brief 操作状态。
 */
struct OperateStatus {
    const char* brokerId;
    const char* userId;
    int status;
    const char* errmsg;
    std::string requestId;  
};


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
    std::string toString() const;

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

	bool operator == (const Contract &other) const {
		return code == other.code && other.exch_type == exch_type;
	}

     /** @brief 获取合约的交易时间 */
    //static std::vector<DateTime> getTradingTime(const Contract &contract);
    static std::vector<std::string> getStrTradingTime(const Contract &contract);
    static Price commission(const Contract &c, Price p, Volume v);

    /** @brief tick触发周期 */
    static std::chrono::milliseconds tickPeriod(const Contract &contract);

    std::string code;       ///< 合约编码
    ExchType    exch_type;  ///< 交易所编码
    float long_margin_ratio = 1; ///< 多头保证金率
    float short_margin_ratio = 1; ///<  空头保证金率
    float price_tick = 0.01;   ///< 最小变动价位
    float volume_multiple; ///< 合约数量乘数
}; 


struct OrderID {
    OrderID(int l_id) : init_id(l_id), order_id(-1) { }
    OrderID() : init_id(-1), order_id(-1) { }

    bool operator == (int other) const {
        return (order_id==other || init_id==other) ? true : false;
    }

    operator int() const { return (order_id != -1 ? order_id : init_id); }
    
    bool operator!=(int other) const {
        return !(*this == other);
    }
    bool operator < (const OrderID &other) const{
        if (order_id != -1)
            return order_id < other.order_id;
        else 
            return init_id < other.init_id;
    }
    int init_id;                       ///< 初始标识。
    int order_id;                       ///< 交易所的订单编号。
};


struct Order {
    static int  order_id_fake_;
    static int  order_id_market_;
    static OrderID nextIDMarket();
    static OrderID nextIDFake();

    Order() { }
    //
    Order(const OrderID &_id, const Contract &c, TradeSide s, Direction d, 
          Price p, Volume v, const DateTime &_datetime, HedgeType h, PriceType deal)
            :id(_id), contract(c), side(s), direction(d), price(p), volume(v),
             datetime(_datetime), hedge_type(h), price_type(deal) { }
    bool operator < (const Order &other) const{ return id < other.id; }
    std::string toString() const;

    OrderID         id;                         ///< 订单编号，从１开始．
    Contract        contract;
    TradeSide       side;   ///< 开平仓标志
    Direction       direction;  ///< 多空方向
    PriceType       price_type;
    HedgeType       hedge_type;
    Price           price;
    DateTime        datetime;
    Volume          volume;
    size_t          milliseconds;               ///< 毫秒延迟．
    bool            islast;
    bool            canceled;                   //撤单状态
};


struct Transaction {
    OrderID         id;                     // 可能要换一个数据结构。    
    Contract        contract;
    TradeSide       side;
    Direction       direction;
    PriceType       price_type;
    HedgeType       hedge_type;
    Price           price;
    DateTime        datetime;
    Volume          volume;
    int             trader_id;
    bool            islast;
};


struct Position {
    Contract contract;
    Direction direction;
    HedgeType hedge_type;
	PositionDate positionDate;  ///< 持仓日期
    Volume volume;  ///< 今日持仓
    Volume yd_volume; ///< 上日持仓
    float use_margin; ///< 占用的保证金
    float margin_ratio; ///< 保证金率 
    float profit; //持仓盈亏
    float cost; //持仓成本
    bool  islast;// 是否是持仓的最后一条合约
};


struct Captial {
    float equity;   ///< 权益
    float available;    ///< 可用资金
    float curr_margin;  ///< 保证金
    float close_profit;     ///< 平仓盈亏
    float position_profit;  ///< 持仓盈亏
    float commission;   ///<  手续费
    float frozen_margin; ///< 冻结保证金
};

/**
 * @brief tick数据, 统一封装了股票、期权、期货。
 */
struct TickData {
    TickData():price(INVALID_NUMBER), volume(0) { };
    /** @brief CTP tick数据转化为自定义格式 */
    TickData(const CThostFtdcDepthMarketDataField *ctp_tick);

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
    Price       price = 0;            // 当其为0时，表示tick数据是无效的。
    unsigned long long volume = 0;
    DateTime    dt;
    int         millisec = 0;  
    DateTime    create_time;    ///< 用于性能追踪，跟踪数据的流转时间。
    std::mutex  locker;
    double      total_price = 0;
    Price       pre_close = 0;
    Price       open = 0;
    Price       high = 0;
    Price       low = 0;
    Price       average = 0;
    DateTime    provider_time;   
    // 买卖十档行情
    Price       buy01_price = 0;
    Price       buy02_price = 0;
    Price       buy03_price = 0;
    Price       buy04_price = 0;
    Price       buy05_price = 0;
    Price       buy06_price = 0;
    Price       buy07_price = 0;
    Price       buy08_price = 0;
    Price       buy09_price = 0;
    Price       buy10_price = 0;
    Volume      buy01_volume = 0;
    Volume      buy02_volume = 0;
    Volume      buy03_volume = 0;
    Volume      buy04_volume = 0;
    Volume      buy05_volume = 0;
    Volume      buy06_volume = 0;
    Volume      buy07_volume = 0;
    Volume      buy08_volume = 0;
    Volume      buy09_volume = 0;
    Volume      buy10_volume = 0;

    Price       sell01_price = 0;
    Price       sell02_price = 0;
    Price       sell03_price = 0;
    Price       sell04_price = 0;
    Price       sell05_price = 0;
    Price       sell06_price = 0;
    Price       sell07_price = 0;
    Price       sell08_price = 0;
    Price       sell09_price = 0;
    Price       sell10_price = 0;
    Volume      sell01_volume = 0;
    Volume      sell02_volume = 0;
    Volume      sell03_volume = 0;
    Volume      sell04_volume = 0;
    Volume      sell05_volume = 0;
    Volume      sell06_volume = 0;
    Volume      sell07_volume = 0;
    Volume      sell08_volume = 0;
    Volume      sell09_volume = 0;
    Volume      sell10_volume = 0;
};
    
} /* QuantApi */
#endif /* end of include guard: _TRADEDATASTRUCT_H */

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
typedef float Volume;            // ���Ϊint, ���޷�����NumberSeries�����У�
typedef float Number;
typedef std::vector<Number>::size_type size_type;
typedef std::chrono::duration<size_type, std::ratio<1,10>> TriggerTimeUnit; ///< ��100����Ϊ��λ�����ڴ�С

/**
 * @brief �ɽ���ʽ��
 */
enum PriceType {
    kLimit,
    kMarket,
    kMilliseconds,
};

/**
 * @brief Ͷ������
 */
enum HedgeType {
    kSpeculation,   ///< Ͷ��
    kArbitrage,     ///< ����
    kHedge          ///< �ױ�
};


/**
 * @brief ����״̬��
 */
enum OrderStatus {
    kOpen,       ///< δ�ɽ�
    kFilled,     ///< �ѳɽ�
    kCancelled   ///< �ѳ���
};

/**
 * @brief ��ƽ�ַ���
 */
enum Direction {
    LONG,
    SHORT
};

/**
 * @brief ��ƽ�ֱ�־ 
 */
enum TradeSide {
   kBuy = 1, ///< ��ͷ����
   kShort,  ///< ��ͷ����
   kCover, ///< ��ͷƽ��
   kSell, ///< ��ͷƽ��
   kCoverToday, ///< ��ͷƽ��
   kSellToday, ///< ��ͷƽ��
   kKai, ///< ����
   kPing, ///< ƽ��
   kPingToday //ƽ��
};

/**
* @brief Ͷ���ֲ߳���������
*/
enum PositionDate {
	psdToday,	//���ճֲ�
	psdHistory  //��ʷ�ֲ�
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
 * @brief ����״̬��
 */
struct OperateStatus {
    const char* brokerId;
    const char* userId;
    int status;
    const char* errmsg;
    std::string requestId;  
};


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
    std::string toString() const;

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

	bool operator == (const Contract &other) const {
		return code == other.code && other.exch_type == exch_type;
	}

     /** @brief ��ȡ��Լ�Ľ���ʱ�� */
    //static std::vector<DateTime> getTradingTime(const Contract &contract);
    static std::vector<std::string> getStrTradingTime(const Contract &contract);
    static Price commission(const Contract &c, Price p, Volume v);

    /** @brief tick�������� */
    static std::chrono::milliseconds tickPeriod(const Contract &contract);

    std::string code;       ///< ��Լ����
    ExchType    exch_type;  ///< ����������
    float long_margin_ratio = 1; ///< ��ͷ��֤����
    float short_margin_ratio = 1; ///<  ��ͷ��֤����
    float price_tick = 0.01;   ///< ��С�䶯��λ
    float volume_multiple; ///< ��Լ��������
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
    int init_id;                       ///< ��ʼ��ʶ��
    int order_id;                       ///< �������Ķ�����š�
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

    OrderID         id;                         ///< ������ţ��ӣ���ʼ��
    Contract        contract;
    TradeSide       side;   ///< ��ƽ�ֱ�־
    Direction       direction;  ///< ��շ���
    PriceType       price_type;
    HedgeType       hedge_type;
    Price           price;
    DateTime        datetime;
    Volume          volume;
    size_t          milliseconds;               ///< �����ӳ٣�
    bool            islast;
    bool            canceled;                   //����״̬
};


struct Transaction {
    OrderID         id;                     // ����Ҫ��һ�����ݽṹ��    
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
	PositionDate positionDate;  ///< �ֲ�����
    Volume volume;  ///< ���ճֲ�
    Volume yd_volume; ///< ���ճֲ�
    float use_margin; ///< ռ�õı�֤��
    float margin_ratio; ///< ��֤���� 
    float profit; //�ֲ�ӯ��
    float cost; //�ֲֳɱ�
    bool  islast;// �Ƿ��ǳֲֵ����һ����Լ
};


struct Captial {
    float equity;   ///< Ȩ��
    float available;    ///< �����ʽ�
    float curr_margin;  ///< ��֤��
    float close_profit;     ///< ƽ��ӯ��
    float position_profit;  ///< �ֲ�ӯ��
    float commission;   ///<  ������
    float frozen_margin; ///< ���ᱣ֤��
};

/**
 * @brief tick����, ͳһ��װ�˹�Ʊ����Ȩ���ڻ���
 */
struct TickData {
    TickData():price(INVALID_NUMBER), volume(0) { };
    /** @brief CTP tick����ת��Ϊ�Զ����ʽ */
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
    Price       price = 0;            // ����Ϊ0ʱ����ʾtick��������Ч�ġ�
    unsigned long long volume = 0;
    DateTime    dt;
    int         millisec = 0;  
    DateTime    create_time;    ///< ��������׷�٣��������ݵ���תʱ�䡣
    std::mutex  locker;
    double      total_price = 0;
    Price       pre_close = 0;
    Price       open = 0;
    Price       high = 0;
    Price       low = 0;
    Price       average = 0;
    DateTime    provider_time;   
    // ����ʮ������
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

#ifndef _MAPPING_H

#define _MAPPING_H
#include <string>
#include <string.h>
#include "../util/log_assert.h"
#include "../util/Exceptions.h"
#include "TradeDataStruct.h" 
namespace QuantDigger {
/**
 * @brief 成交方式。
 */
enum DealType {
    kLimit,
    kAny,
    kMilliseconds,
};

/**
 * @brief 订单状态。
 */
enum OrderStatus {
    kOpen,
    kFilled,
    kCancelled
};

/**
 * @brief 开平仓方向。
 */
enum Direction {
    Duo, 
    Kong
};

enum Action {
    Kai,
    Ping,
    TaoLiKai,
    TaoLiPi
};

typedef char ExchType;

/** @brief 把交易所编码映射到系统的交易所编码 */
inline ExchType map2QDExchType(const char* str_exch) throw (Util::InvalidParamException) {
    // 上海期货交易所
    if(strcmp(str_exch, "SHFE") == 0)
        return '1';
    // 郑州商品交易所
    if(strcmp(str_exch, "CZCE") == 0)
        return '2';
    // 大连商品交易所
    if(strcmp(str_exch, "DCE") == 0)
        return '3';
    // 中国金融期货交易所
    if(strcmp(str_exch, "CFFEX") == 0)
        return '4';
    throw Util::InvalidParamException("无效的编码: ", str_exch);
}

inline std::string mapFromQDExchType(ExchType c) throw (Util::InvalidParamException) {
    switch(c) {
        case '1': return "SHFE";
        case '2': return "CZCE";
        case '3': return "DCE";
        case '4': return "CFFEX"; 
        default: throw Util::InvalidParamException("无效的编码: ", &c);
    }
    return "";
}

/** @brief 把系统的交易所编码映射到交易所编码 */
inline const char* map2ReadableExchType(ExchType type) throw (Util::InvalidParamException) {
    switch(type) {
        case '1':
            return "上期";
        case '2':
            return "郑商";
        case '3':
            return "大商";
        case '4':
            return "中金";
        default: throw Util::InvalidParamException("无效的编码: ", &type);
    }
    return "";
}

inline const char* actionMapping(Action act) throw (Util::InvalidParamException) {
    switch(act) {
        case Kai: return "开仓";
        case Ping: return "平仓";
        default: throw Util::InvalidParamException("无效的编码: ", "%d", act);
    }
    return "";
}

inline const char* directionMapping(Direction direc) throw (Util::InvalidParamException) {
    switch(direc) {
        case Duo: return "多头";
        case Kong: return "空头";
        default: throw Util::InvalidParamException("无效的编码: ", "%d", direc);
    }
    return "";
}

inline const char* dealTypeMapping(DealType deal_type) throw (Util::InvalidParamException) {
    switch(deal_type) {
        case kAny: return "市价";
        case kMilliseconds: "限价";
        case kLimit: return "限价";
        default: throw Util::InvalidParamException("无效的编码: ", "%d", deal_type);
    }
    return "";
}

} /* QuantDigger */
#endif /* end of include guard: _MAPPING_H */

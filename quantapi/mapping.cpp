#include "../util/log_assert.h"
#include "mapping.h" 

namespace QuantApi {
    
/** @brief 把交易所编码映射到系统的交易所编码 */
ExchType map2QDExchType(const char* str_exch) throw (Util::InvalidParamException) {
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
    //上海证券交易所
    if(strcmp(str_exch, "SSE") == 0)
        return '5';
    //深圳证券交易所
    if(strcmp(str_exch, "SZSE") == 0)
        return '6';
    //测试专用交易所
    if(strcmp(str_exch, "CC") == 0)
        return '7';
    throw Util::InvalidParamException("无效的编码: ", str_exch);
}

std::string mapFromQDExchType(ExchType c) throw (Util::InvalidParamException) {
    switch(c) {
        case '1': return "SHFE";
        case '2': return "CZCE";
        case '3': return "DCE";
        case '4': return "CFFEX";
        case '5': return "SSE";
        case '6': return "SZSE";
        case '7': return "CC";
        default: throw Util::InvalidParamException("无效的编码: ", &c);
    }
    return "";
}

/** @brief 把系统的交易所编码映射到交易所编码 */
const char* map2ReadableExchType(ExchType type) throw (Util::InvalidParamException) {
    switch(type) {
        case '1':
            return "上期";
        case '2':
            return "郑商";
        case '3':
            return "大商";
        case '4':
            return "中金";
        case '5':
            return "上证";
        case '6':
            return "深证";
        default: throw Util::InvalidParamException("无效的编码: ", &type);
    }
    return "";
}

const char* tradesideMapping(TradeSide side) throw (Util::InvalidParamException) {
    switch(side) {
        case kKai: return "开仓";
        case kPing: return "平仓";
        default: throw Util::InvalidParamException("无效的编码: ", "%d", side);
    }
    return "";
}

const char* directionMapping(Direction direc) throw (Util::InvalidParamException) {
    switch(direc) {
        case LONG: return "多头";
        case SHORT: return "空头";
        default: throw Util::InvalidParamException("无效的编码: ", "%d", direc);
    }
    return "";
}

const char* priceTypeMapping(PriceType deal_type) throw (Util::InvalidParamException) {
    switch(deal_type) {
        case kMarket: return "市价";
        case kMilliseconds: "限价";
        case kLimit: return "限价";
        default: throw Util::InvalidParamException("无效的编码: ", "%d", deal_type);
    }
    return "";
}
} /* QuantApi */

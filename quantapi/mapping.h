#ifndef _MAPPING_H

#define _MAPPING_H
#include <string>
#include <string.h>
#include "../util/Exceptions.h"
#include "datastruct.h" 
namespace QuantApi {

/** @brief 把交易所编码映射到系统的交易所编码 */
ExchType map2QDExchType(const char* str_exch) throw (Util::InvalidParamException);

std::string mapFromQDExchType(ExchType c) throw (Util::InvalidParamException);

/** @brief 把系统的交易所编码映射到交易所编码 */
const char* map2ReadableExchType(ExchType type) throw (Util::InvalidParamException);

const char* actionMapping(TradeSide act) throw (Util::InvalidParamException);

const char* directionMapping(Direction direc) throw (Util::InvalidParamException);

const char* priceTypeMapping(PriceType deal_type) throw (Util::InvalidParamException);

} /* QuantApi */
#endif /* end of include guard: _MAPPING_H */

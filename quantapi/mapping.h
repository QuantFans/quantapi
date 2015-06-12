#ifndef _MAPPING_H

#define _MAPPING_H
#include <string>
#include <string.h>
#include "../util/Exceptions.h"
#include "datastruct.h" 
namespace QuantApi {

/** @brief �ѽ���������ӳ�䵽ϵͳ�Ľ��������� */
ExchType map2QDExchType(const char* str_exch) throw (Util::InvalidParamException);

std::string mapFromQDExchType(ExchType c) throw (Util::InvalidParamException);

/** @brief ��ϵͳ�Ľ���������ӳ�䵽���������� */
const char* map2ReadableExchType(ExchType type) throw (Util::InvalidParamException);

const char* actionMapping(TradeSide act) throw (Util::InvalidParamException);

const char* directionMapping(Direction direc) throw (Util::InvalidParamException);

const char* priceTypeMapping(PriceType deal_type) throw (Util::InvalidParamException);

} /* QuantApi */
#endif /* end of include guard: _MAPPING_H */

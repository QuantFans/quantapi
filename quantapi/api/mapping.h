#ifndef _MAPPING_H

#define _MAPPING_H
#include <string>
#include <string.h>
#include "../util/log_assert.h"
#include "../util/Exceptions.h"
#include "TradeDataStruct.h" 
namespace QuantDigger {
/**
 * @brief �ɽ���ʽ��
 */
enum DealType {
    kLimit,
    kAny,
    kMilliseconds,
};

/**
 * @brief ����״̬��
 */
enum OrderStatus {
    kOpen,
    kFilled,
    kCancelled
};

/**
 * @brief ��ƽ�ַ���
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

/** @brief �ѽ���������ӳ�䵽ϵͳ�Ľ��������� */
inline ExchType map2QDExchType(const char* str_exch) throw (Util::InvalidParamException) {
    // �Ϻ��ڻ�������
    if(strcmp(str_exch, "SHFE") == 0)
        return '1';
    // ֣����Ʒ������
    if(strcmp(str_exch, "CZCE") == 0)
        return '2';
    // ������Ʒ������
    if(strcmp(str_exch, "DCE") == 0)
        return '3';
    // �й������ڻ�������
    if(strcmp(str_exch, "CFFEX") == 0)
        return '4';
    throw Util::InvalidParamException("��Ч�ı���: ", str_exch);
}

inline std::string mapFromQDExchType(ExchType c) throw (Util::InvalidParamException) {
    switch(c) {
        case '1': return "SHFE";
        case '2': return "CZCE";
        case '3': return "DCE";
        case '4': return "CFFEX"; 
        default: throw Util::InvalidParamException("��Ч�ı���: ", &c);
    }
    return "";
}

/** @brief ��ϵͳ�Ľ���������ӳ�䵽���������� */
inline const char* map2ReadableExchType(ExchType type) throw (Util::InvalidParamException) {
    switch(type) {
        case '1':
            return "����";
        case '2':
            return "֣��";
        case '3':
            return "����";
        case '4':
            return "�н�";
        default: throw Util::InvalidParamException("��Ч�ı���: ", &type);
    }
    return "";
}

inline const char* actionMapping(Action act) throw (Util::InvalidParamException) {
    switch(act) {
        case Kai: return "����";
        case Ping: return "ƽ��";
        default: throw Util::InvalidParamException("��Ч�ı���: ", "%d", act);
    }
    return "";
}

inline const char* directionMapping(Direction direc) throw (Util::InvalidParamException) {
    switch(direc) {
        case Duo: return "��ͷ";
        case Kong: return "��ͷ";
        default: throw Util::InvalidParamException("��Ч�ı���: ", "%d", direc);
    }
    return "";
}

inline const char* dealTypeMapping(DealType deal_type) throw (Util::InvalidParamException) {
    switch(deal_type) {
        case kAny: return "�м�";
        case kMilliseconds: "�޼�";
        case kLimit: return "�޼�";
        default: throw Util::InvalidParamException("��Ч�ı���: ", "%d", deal_type);
    }
    return "";
}

} /* QuantDigger */
#endif /* end of include guard: _MAPPING_H */

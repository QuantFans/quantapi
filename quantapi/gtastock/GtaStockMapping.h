#ifndef GTASTOCKMAPPING_H_
#define GTASTOCKMAPPING_H_

#include <quantapi/datastruct.h>
#include <quantapi/mapping.h>
#include "QTSDataType.h" 

namespace QuantApi {
namespace Mapping {

typedef void(*Func)(const IFieldValue& iValue, TickData* tick);

struct FieldProcessor
{
    FieldProcessor(FieldID id, Func fun)
    {
        field_id = id;
        func = fun;
    }
    FieldID field_id;
    Func func;
};

//---------------------买入10档价格----------------------------------
inline void buyPrice01_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->buy01_price = dvalue;
    //std::cout << "buy01_price:" << dvalue << std::endl;
}

inline void buyPrice02_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->buy02_price = dvalue;
    //std::cout << "buy02_price:" << dvalue << std::endl;
}

inline void buyPrice03_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->buy03_price = dvalue;
    //std::cout << "buy03_price:" << dvalue << std::endl;
}

inline void buyPrice04_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->buy04_price = dvalue;
    //std::cout << "buy04_price:" << dvalue << std::endl;
}

inline void buyPrice05_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->buy05_price = dvalue;
    //std::cout << "buy05_price:" << dvalue << std::endl;
}

inline void buyPrice06_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->buy06_price = dvalue;
    //std::cout << "buy06_price:" << dvalue << std::endl;
}

inline void buyPrice07_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->buy07_price = dvalue;
    //std::cout << "buy07_price:" << dvalue << std::endl;
}

inline void buyPrice08_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->buy08_price = dvalue;
    //std::cout << "buy08_price:" << dvalue << std::endl;
}

inline void buyPrice09_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->buy09_price = dvalue;
    //std::cout << "buy09_price:" << dvalue << std::endl;
}

inline void buyPrice10_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->buy10_volume = dvalue;
    //std::cout << "buy10_price:" << dvalue << std::endl;
}
//------------------------买入10档分数-------------------------------
inline void buyVolume01_func(const IFieldValue& iValue, TickData* tick)
{
    //double dvalue;
    unsigned long long dvalue;
    //std::cout << iValue.GetFieldType() << std::endl;
    iValue.GetULonglong(dvalue);
    tick->buy01_volume = dvalue;
    //std::cout << "buy01_volume:" << tick->buy01_volume << std::endl;
}

inline void buyVolume02_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->buy02_volume = dvalue;
    //std::cout << "buy02_volume:" << dvalue << std::endl;
}

inline void buyVolume03_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->buy03_volume = dvalue;
    //std::cout << "buy03_volume:" << dvalue << std::endl;
}

inline void buyVolume04_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long  dvalue;
    iValue.GetULonglong(dvalue);
    tick->buy04_volume = dvalue;
    //std::cout << "buy04_volume:" << dvalue << std::endl;
}

inline void buyVolume05_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->buy05_volume = dvalue;
    //std::cout << "buy05_volume:" << dvalue << std::endl;
}

inline void buyVolume06_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->buy06_volume = dvalue;
    //std::cout << "buy06_volume:" << dvalue << std::endl;
}

inline void buyVolume07_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->buy07_volume = dvalue;
    //std::cout << "buy07_volume:" << dvalue << std::endl;
}

inline void buyVolume08_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->buy08_volume = dvalue;
    //std::cout << "buy08_volume:" << dvalue << std::endl;
}

inline void buyVolume09_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->buy09_volume = dvalue;
    //std::cout << "buy09_volume:" << dvalue << std::endl;
}

inline void buyVolume10_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->buy10_volume = dvalue;
    //std::cout << "buy10_volume:" << dvalue << std::endl;
}

//------------------卖出10档价格--------------------------------------------
inline void sellPrice01_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->sell01_price = dvalue;
    //std::cout << "sell01_price:" << dvalue << std::endl;
}

inline void sellPrice02_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->sell02_price = dvalue;
    //std::cout << "sell02_price:" << dvalue << std::endl;
}

inline void sellPrice03_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->sell03_price = dvalue;
    //std::cout << "sell03_price:" << dvalue << std::endl;
}

inline void sellPrice04_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->sell04_price = dvalue;
    //std::cout << "sell04_price:" << dvalue << std::endl;
}

inline void sellPrice05_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->sell05_price = dvalue;
    //std::cout << "sell05_price:" << dvalue << std::endl;
}

inline void sellPrice06_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->sell06_price = dvalue;
    //std::cout << "sell06_price:" << dvalue << std::endl;
}

inline void sellPrice07_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->sell07_price = dvalue;
    //std::cout << "sell07_price:" << dvalue << std::endl;
}

inline void sellPrice08_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->sell08_price = dvalue;
    //std::cout << "sell08_price:" << dvalue << std::endl;
}

inline void sellPrice09_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->sell09_price = dvalue;
    //std::cout << "sell09_price:" << dvalue << std::endl;
}

inline void sellPrice10_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->sell10_price = dvalue;
    //std::cout << "sell10_price:" << dvalue << std::endl;
}

//----------------------卖出10档份数---------------------------------
inline void sellVolume01_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->sell01_volume = dvalue;
    //std::cout << "sell01_volume:" << dvalue << std::endl;
}

inline void sellVolume02_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->sell02_volume = dvalue;
    //std::cout << "sell02_volume:" << dvalue << std::endl;
}

inline void sellVolume03_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->sell03_volume = dvalue;
    //std::cout << "sell03_volume:" << dvalue << std::endl;
}

inline void sellVolume04_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->sell04_volume = dvalue;
    //std::cout << "sell04_volume:" << dvalue << std::endl;
}

inline void sellVolume05_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->sell05_volume = dvalue;
    //std::cout << "sell05_volume:" << dvalue << std::endl;
}

inline void sellVolume06_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->sell06_volume = dvalue;
    //std::cout << "sell06_volume:" << dvalue << std::endl;
}

inline void sellVolume07_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->sell07_volume = dvalue;
    //std::cout << "sell07_volume:" << dvalue << std::endl;
}

inline void sellVolume08_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->sell08_volume = dvalue;
    //std::cout << "sell08_volume:" << dvalue << std::endl;
}

inline void sellVolume09_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->sell09_volume = dvalue;
    //std::cout << "sell09_volume:" << dvalue << std::endl;
}

inline void sellVolume10_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long dvalue;
    iValue.GetULonglong(dvalue);
    tick->sell10_volume = dvalue;
    //std::cout << "sell10_volume:" << dvalue << std::endl;
}

//--------------------------------------------------------------------
inline void packet_time_func(const IFieldValue& iValue, TickData* tick)
{
    long long PacketTimeStamp;
    iValue.GetLonglong(PacketTimeStamp);
    //std::cout << "Exchange TimeStamp:"  << PacketTimeStamp << std::endl;
    
    tick->create_time =  std::chrono::system_clock::now();
//    std::time_t tt = std::chrono::system_clock::to_time_t(tick->create_time);
//    std::tm* tm = std::localtime(&tt);
//    int now_hour = tm->tm_hour;

    std::string timeStamp = Util::sth2string(PacketTimeStamp);
    int year,month,day,hour,minute,second,milliseconds;
    sscanf(timeStamp.c_str(), "%4d", &year);
    sscanf(timeStamp.c_str()+4, "%2d", &month);
    sscanf(timeStamp.c_str()+6, "%2d", &day);
    sscanf(timeStamp.c_str()+8, "%2d", &hour);
    sscanf(timeStamp.c_str()+10, "%2d", &minute);
    sscanf(timeStamp.c_str()+12, "%2d", &second);
    sscanf(timeStamp.c_str()+14, "%3d", &milliseconds);

//    if (hour + 8 == now_hour)
//        hour += 8;
    
    char dt[20];
    sprintf(dt, "%.4d-%.2d-%.2d %.2d:%.2d:%.2d", year, month, day, hour, minute, second);
    
    tick->dt = Util::strDateTime2TimePoint(dt);
    tick->millisec = milliseconds; 
}

/*
inline void provider_time_func(const IFieldValue& iValue, TickData* tick)
{
    long long PacketTimeStamp;
    iValue.GetLonglong(PacketTimeStamp);
    std::cout << "Provider TimeStamp:"  << PacketTimeStamp << std::endl;
    std::string timeStamp = Util::sth2string(PacketTimeStamp);
    
    int year,month,day,hour,minute,second,milliseconds;
    sscanf(timeStamp.c_str(), "%4d", &year);
    sscanf(timeStamp.c_str()+4, "%2d", &month);
    sscanf(timeStamp.c_str()+6, "%2d", &day);
    sscanf(timeStamp.c_str()+8, "%2d", &hour);
    sscanf(timeStamp.c_str()+10, "%2d", &minute);
    sscanf(timeStamp.c_str()+12, "%2d", &second);
    sscanf(timeStamp.c_str()+14, "%3d", &milliseconds);
    
    char dt[20];
    sprintf(dt, "%.4d-%.2d-%.2d %.2d:%.2d:%.2d", year, month, day, hour, minute, second);
    
    tick->provider_time = Util::strDateTime2TimePoint(dt);
}
*/

inline void contract_func(const IFieldValue& iValue, TickData* tick)
{
    char code[SYMBOL_LEN];
    unsigned int len = SYMBOL_LEN;
    iValue.GetString(code, len);
    code[len] = 0;
    std::vector<std::string> c = Util::split(code, '.');
    tick->contract.code = c[0].c_str();
    tick->contract.exch_type = map2QDExchType(c[1].c_str());
    //std::cout << "     Contract:" << code << std::endl;
}

inline void preclose_func(const IFieldValue& iValue, TickData* tick) 
{
    double dvalue;
    iValue.GetDouble(dvalue); 
    tick->pre_close = dvalue;
    //std::cout << "YestodayClose:" << tick->pre_close << std::endl;
}

inline void open_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue); 
    tick->open = dvalue;
    //std::cout << "        open:" << tick->open << std::endl;
}

inline void high_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->high = dvalue;
    //std::cout << "       hight:" << tick->high << std::endl;
}

inline void low_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue); 
    tick->low = dvalue;
    //std::cout << "        low:" << tick->low << std::endl;
}

inline void price_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    iValue.GetDouble(dvalue);
    tick->price = dvalue;
    //std::cout << "       price:" << tick->price << std::endl;
}

inline void totalPrice_func(const IFieldValue& iValue, TickData* tick)
{
    double dvalue;
    //std::cout << iValue.GetFieldType() << std::endl;
    iValue.GetDouble(dvalue);
    tick->total_price = dvalue;
    //std::cout << "  totalPrice:" << tick->total_price << std::endl;
}

inline void volume_func(const IFieldValue& iValue, TickData* tick)
{
    unsigned long long lvalue;
    iValue.GetULonglong(lvalue);
    tick->volume = lvalue;
    //std::cout << " totalVolume:" << tick->volume << std::endl;
}

FieldProcessor processor[] = {
    FieldProcessor(FID_BuyPrice01, buyPrice01_func),
    FieldProcessor(FID_BuyPrice02, buyPrice02_func),
    FieldProcessor(FID_BuyPrice03, buyPrice03_func),
    FieldProcessor(FID_BuyPrice04, buyPrice04_func),
    FieldProcessor(FID_BuyPrice05, buyPrice05_func),
    FieldProcessor(FID_BuyPrice06, buyPrice06_func),
    FieldProcessor(FID_BuyPrice07, buyPrice07_func),
    FieldProcessor(FID_BuyPrice08, buyPrice08_func),
    FieldProcessor(FID_BuyPrice09, buyPrice09_func),
    FieldProcessor(FID_BuyPrice10, buyPrice10_func),

    FieldProcessor(FID_BuyVolume01, buyVolume01_func),
    FieldProcessor(FID_BuyVolume02, buyVolume02_func),
    FieldProcessor(FID_BuyVolume03, buyVolume03_func),
    FieldProcessor(FID_BuyVolume04, buyVolume04_func),
    FieldProcessor(FID_BuyVolume05, buyVolume05_func),
    FieldProcessor(FID_BuyVolume06, buyVolume06_func),
    FieldProcessor(FID_BuyVolume07, buyVolume07_func),
    FieldProcessor(FID_BuyVolume08, buyVolume08_func),
    FieldProcessor(FID_BuyVolume09, buyVolume09_func),
    FieldProcessor(FID_BuyVolume10, buyVolume10_func),

    FieldProcessor(FID_SellPrice01, sellPrice01_func),
    FieldProcessor(FID_SellPrice02, sellPrice02_func),
    FieldProcessor(FID_SellPrice03, sellPrice03_func),
    FieldProcessor(FID_SellPrice04, sellPrice04_func),
    FieldProcessor(FID_SellPrice05, sellPrice05_func),
    FieldProcessor(FID_SellPrice06, sellPrice06_func),
    FieldProcessor(FID_SellPrice07, sellPrice07_func),
    FieldProcessor(FID_SellPrice08, sellPrice08_func),
    FieldProcessor(FID_SellPrice09, sellPrice09_func),
    FieldProcessor(FID_SellPrice10, sellPrice10_func),

    FieldProcessor(FID_SellVolume01, sellVolume01_func),
    FieldProcessor(FID_SellVolume02, sellVolume02_func),
    FieldProcessor(FID_SellVolume03, sellVolume03_func),
    FieldProcessor(FID_SellVolume04, sellVolume04_func),
    FieldProcessor(FID_SellVolume05, sellVolume05_func),
    FieldProcessor(FID_SellVolume06, sellVolume06_func),
    FieldProcessor(FID_SellVolume07, sellVolume07_func),
    FieldProcessor(FID_SellVolume08, sellVolume08_func),
    FieldProcessor(FID_SellVolume09, sellVolume09_func),
    FieldProcessor(FID_SellVolume10, sellVolume10_func),

    FieldProcessor(FID_PacketTimeStamp, packet_time_func),
//    FieldProcessor(FID_LocalTimeStamp, provider_time_func),
    FieldProcessor(FID_Symbol, contract_func),
    FieldProcessor(FID_PreClosePrice, preclose_func),
    FieldProcessor(FID_OpenPrice, open_func),
    FieldProcessor(FID_HighPrice, high_func),
    FieldProcessor(FID_LowPrice, low_func),
    FieldProcessor(FID_LastPrice, price_func),
    FieldProcessor(FID_TotalAmount, totalPrice_func),
    FieldProcessor(FID_TotalVolume, volume_func)
};


inline void fromGtaStockTick(IQuotationData& realData, TickData* tick) 
{
    unsigned int len = 0;
    int count = realData.Count();
    int func_cnt = sizeof(processor)/sizeof(FieldProcessor);

    //std::cout << "===========count(" << count << ")============" << std::endl;
    for (int i = 0; i < count; i++)
    {
        const IFieldValue& iValue =  realData[i];
        FieldID field_id = iValue.GetFieldID(); 
        for(int j = 0; j < func_cnt; j++)
        {
            FieldProcessor proc = processor[j];
            if (field_id == proc.field_id)
            {
                proc.func(iValue, tick);
            }
        }
    }
}



} /*namespace Mapping*/
} /*namespace QuantApi*/

#endif

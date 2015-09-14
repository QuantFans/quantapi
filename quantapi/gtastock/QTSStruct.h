//////////////////////////////////////////////////////////////////////////////
/// @file       QTSStruct.h 
/// @brief      ������Ϣ�ṹ�嶨���ļ�
/// @copyright  Copyright (C), 2008-2014, GTA Information Tech. Co., Ltd.
/// @version    2.0
/// @date       2014.7.18
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_QTS_STRUCT_H_
#define GTA_QTS_STRUCT_H_
#include "QTSDataType.h"


#define DESTDLG_FILE        1      ///< TestDlg�ļ���ʽ
#define HIGH_FREQUENCY      2      ///< ��Ƶ�ļ���ʽ

#pragma pack(8)


/// ������λ��Ϣ�����ۡ���������3����Ϣ
struct  BuySellLevelInfo3
{
    double              Price;                  ///< �۸�,3λС��
    unsigned long long  Volume;                 ///< ��
    unsigned int        TotalOrderNo;           ///< ί�б���
};
/// ������λ��Ϣ�����ۡ�����Ϣ
struct  BuySellLevelInfo
{
    double              Price;                  ///< �۸�,3λС��
    unsigned long long  Volume;                 ///< ��
};

#define LEVEL_ONE   1               ///< һ������
#define LEVEL_FIVE  5               ///< �嵵����
#define LEVEL_TEN   10              ///< ʮ������
#define SETTLE_LEN  10              ///< ��������볤��
#define ORDER_LEVEL_FIFTY   50      ///< 50��ί��

/// �Ͻ�����̬����
struct SSEL1_Static
{
    char    Symbol[SYMBOL_LEN];     ///< ֤ȯ����
};
/// �Ͻ���L1ʵʱ����
struct SSEL1_Quotation
{
    char    Symbol[SYMBOL_LEN];     ///< ֤ȯ����
};

/// �Ͻ���L2��̬����
struct SSEL2_Static
{
    int                 LocalTimeStamp;                     ///< ���ݽ���ʱ��HHMMSSMMM
    long long           PacketTimeStamp;                    ///< ���ݰ�ͷʱ��YYYYMMDDHHMMSSMMM
    int                 Time;                               ///< ��������ʱ�䣬��ʶ�ӿ��б���¼����ʱ��HHMMSSMMM
    char                Symbol[SYMBOL_LEN];                 ///< ֤ȯ����, 
    char                ISINCode[12];                       ///< ISIN����, 
    char                SecurityName[SECURITY_NAME_LEN];    ///< ֤ȯ����, 
    char                SecurityEN[SECURITY_EN_LEN];        ///< Ӣ��֤ȯ����, 
    char                SymbolUnderlying[SYMBOL_LEN];       ///< ����֤ȯ����, 
    char                MarketType[6];                      ///< �г�����, ��ASHR����ʾA���г�����BSHR����ʾB���г�����CSHR����ʾ���ʰ��г���
    char                CFICode[6];                         ///< ֤ȯ���, ��E'��ʾ��Ʊ����EU����ʾ���𣻡�D����ʾծȯ����RWS����ʾȨ֤����FF����ʾ�ڻ���
    char                SecuritySubType[6];                 ///< ֤ȯ�����, �Զ�����ϸ֤ȯ���
    char                Currency[5];                        ///< ����, CNY = ����ң�HKD = �۱�
    long long           TradableMarketNo;                   ///< ����ͨ����������, Ԥ��
    long long           TradableNo;                         ///< ����ͨδ��������, Ԥ��
    long long           NonTradableNo;                      ///< ����ͨ����, Ԥ��
    int                 ListingDate;                        ///< ��������, ���Ͻ������ս������ڣ�YYYYMMDD
    unsigned int        SetNo;                              ///< ��Ʒ�����, ȡֵ��Χ��1��999,������������Ʒ��һ�ַ��鷽ʽ�������ڶ���������Ը��ؾ�����䡣��ֵ��һ���������ڲ���仯��
    unsigned int        BuyVolumeUnit;                      ///< ��������λ, �򶩵����걨���������Ǹ��ֶε���������
    unsigned int        SellVolumeUnit;                     ///< ��������λ, ���������걨���������Ǹ��ֶε���������
    unsigned int        DeclareVolumeFloor;                 ///< �걨������, �걨��������
    unsigned int        DeclareVolumeCeiling;               ///< �걨������, �걨��������
    double              PreClosePrice;                      ///< ���ռ�, 3λС����ǰ���̼۸����г�Ȩ��Ϣ��Ϊ��Ȩ��Ϣ������̼ۣ������ڻ����г�����ʵʱ���꣬ȡֵΪ0.010
    double              TickSize;                           ///< ��С���۵�λ, �걨�۸����С�䶯��λ
    char                UpDownLimitType;                    ///< �ǵ�����������, ��N����ʾ���׹���3.4.13�涨�����ǵ����������ͻ���Ȩ֤����취��22���涨����R'��ʾ���׹���3.4.15��3.4.16�涨�����ǵ����������ͣ���S����ʾ�ع��ǵ����������͡�
    double              PriceUpLimit;                       ///< �Ƿ��۸�, ����N�����ǵ������ƵĲ�Ʒ�����ֶε��ղ�����ģ�����ǰ���̼ۣ����������н��ײ�ƷΪ���мۣ����㣻����R�������ǵ������ƵĲ�Ʒ�����ֶ�ȡ����ʱ���ڲο��۸��������޼۸�
    double              PriceDownLimit;                     ///< �����۸�, ���㷽ʽ�ο��Ƿ����޼۸�
    double              XRRatio;                            ///< ��Ȩ����, ÿ���͹ɱ��������ڹ�ծԤ���в�Ʒ��Ϊ��֤�������
    double              XDAmount;                           ///< ��Ϣ���, ÿ�ɷֺ���
    char                CrdBuyUnderlying;                   ///< ���ʱ�ı�־, ��T����ʾ�����ʱ��֤ȯ����F����ʾ�������ʱ��֤ȯ��
    char                CrdSellUnderlying;                  ///< ��ȯ��ı�־, ��T����ʾ����ȭ���֤ȯ����F����ʾ������ȯ���֤ȯ��
    char                SecurityStatus[20];                 ///< ��Ʒ״̬��ʶ, ��0λ��Ӧ����N����ʾ�������У���1λ��Ӧ����D����ʾ��Ȩ����2λ��Ӧ����R'��ʾ��Ϣ����3λ��Ӧ����D����ʾ���������������ײ�Ʒ����S����ʾ���վ�ʾ��Ʒ����P����ʾ���������Ʒ��
};
/// �Ͻ���L2ʵʱ����
struct SSEL2_Quotation
{
    int                 LocalTimeStamp;         ///< ���ݽ���ʱ��HHMMSSMMM
    long long           PacketTimeStamp;        ///< ���ݰ�ͷʱ��YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< ��������ʱ��, ���¶���ʱ�䣨���룩;143025001 ��ʾ 14:30:25.001
    char                Symbol[SYMBOL_LEN];     ///< ֤ȯ����, 
    double              PreClosePrice;          ///< ���ռ�, 
    double              OpenPrice;              ///< ���̼�, 
    double              HighPrice;              ///< ��߼�, 
    double              LowPrice;               ///< ��ͼ�, 
    double              LastPrice;              ///< �ּ�, 
    double              ClosePrice;             ///< �����̼�, 
    char                TradeStatus[6];         ///< ��ǰƷ�ֽ���״̬, 
    unsigned long long  TotalNo;                ///< �ɽ�����, 
    unsigned long long  TotalVolume;            ///< �ɽ�����, ��Ʊ����;Ȩ֤����;ծȯ����
    double              TotalAmount;            ///< �ɽ��ܶ�, ��Ԫ��
    unsigned long long  TotalBuyOrderVolume;    ///< ί����������, ��Ʊ����;Ȩ֤����;ծȯ����
    double              WtAvgBuyPrice;          ///< ��Ȩƽ��ί���, ��Ԫ��
    double              BondWtAvgBuyPrice;      ///< ծȯ��Ȩƽ��ί���, ��Ԫ��
    unsigned long long  TotalSellOrderVolume;   ///< ί����������, 
    double              WtAvgSellPrice;         ///< ��Ȩƽ��ί����, ��Ԫ��
    double              BondWtAvgSellPrice;     ///< ծȯ��Ȩƽ��ί����, 
    double              IOPV;                   ///< ETF ��ֵ��ֵ, 
    int                 ETFBuyNo;               ///< ETF �깺����, 
    long long           ETFBuyVolume;           ///< ETF �깺��, 
    double              ETFBuyAmount;           ///< ETF �깺��, 
    int                 ETFSellNo;              ///< ETF ��ر���, 
    long long           ETFSellVolume;          ///< ETF �����, 
    double              ETFSellAmount;          ///< ETF ��ض�, 
    double              YTM;                    ///< ծȯ����������, 
    long long           TotalWarrantExecVol;    ///< Ȩִ֤�е�������, 
    double              WarrantDownLimit;       ///< Ȩ֤��ͣ�۸�, ��Ԫ��
    double              WarrantUpLimit;         ///< Ȩ֤��ͣ�۸�, ��Ԫ��
    int                 WithdrawBuyNo;          ///< ���볷������, 
    long long           WithdrawBuyVolume;      ///< ���볷����, 
    double              WithdrawBuyAmount;      ///< ���볷����, 
    int                 WithdrawSellNo;         ///< ������������, 
    long long           WithdrawSellVolume;     ///< ����������, 
    double              WithdrawSellAmount;     ///< ����������, 
    int                 TotalBuyNo;             ///< �����ܱ���, 
    int                 TotalSellNo;            ///< �����ܱ���, 
    int                 MaxBuyDuration;         ///< ����ɽ����ȴ�ʱ��, 
    int                 MaxSellDuration;        ///< �����ɽ����ȴ�ʱ��, 
    int                 BuyOrderNo;             ///< ��ί�м�λ��, 
    int                 SellOrderNo;            ///< ����ί�м�λ��, 
    unsigned int        SellLevelNo;            ///< ���̼�λ����, 10�����飬����ʱ����
    union
    {
        BuySellLevelInfo3    SellLevel[LEVEL_TEN];          ///< ʮ��������
        struct
        {
                double              SellPrice01;            ///< ������, 
                unsigned long long  SellVolume01;           ///< ������, 
                unsigned int        TotalSellOrderNo01;     ///< ������ί�б���, 
                double              SellPrice02;            ///< ������, 
                unsigned long long  SellVolume02;           ///< ������, 
                unsigned int        TotalSellOrderNo02;     ///< ������ί�б���, 
                double              SellPrice03;            ///< ������, 
                unsigned long long  SellVolume03;           ///< ������, 
                unsigned int        TotalSellOrderNo03;     ///< ������ί�б���, 
                double              SellPrice04;            ///< ������, 
                unsigned long long  SellVolume04;           ///< ������, 
                unsigned int        TotalSellOrderNo04;     ///< ������ί�б���, 
                double              SellPrice05;            ///< ������, 
                unsigned long long  SellVolume05;           ///< ������, 
                unsigned int        TotalSellOrderNo05;     ///< ������ί�б���, 
                double              SellPrice06;            ///< ������, 
                unsigned long long  SellVolume06;           ///< ������, 
                unsigned int        TotalSellOrderNo06;     ///< ������ί�б���, 
                double              SellPrice07;            ///< ������, 
                unsigned long long  SellVolume07;           ///< ������, 
                unsigned int        TotalSellOrderNo07;     ///< ������ί�б���, 
                double              SellPrice08;            ///< ������, 
                unsigned long long  SellVolume08;           ///< ������, 
                unsigned int        TotalSellOrderNo08;     ///< ������ί�б���, 
                double              SellPrice09;            ///< ������, 
                unsigned long long  SellVolume09;           ///< ������, 
                unsigned int        TotalSellOrderNo09;     ///< ������ί�б���, 
                double              SellPrice10;            ///< ������, 
                unsigned long long  SellVolume10;           ///< ������, 
                unsigned int        TotalSellOrderNo10;     ///< ������ί�б���, 
        };
    };
    unsigned int        SellLevelQueueNo01;                 ///< ��һ����ʾί�б���, Ϊ 0 ��ʾ����ʾ
    unsigned int        SellLevelQueue[ORDER_LEVEL_FIFTY];  ///< ��1������, ��Ƶ���ݱ��棬�ȴ涩������,ֻ��һ���д����ݣ�50��������ʱ����
    unsigned int        BuyLevelNo;                         ///< ���̼�λ����, 10�����飬����ʱ����
    union
    {
        BuySellLevelInfo3    BuyLevel[LEVEL_TEN];           ///< ʮ��������
        struct
        {
            double              BuyPrice01;                 ///< �����, 
            unsigned long long  BuyVolume01;                ///< ������, ��Ʊ����;Ȩ֤����;ծȯ����
            unsigned int        TotalBuyOrderNo01;          ///< ������ί�б���, 
            double              BuyPrice02;                 ///< �����, 
            unsigned long long  BuyVolume02;                ///< ������, 
            unsigned int        TotalBuyOrderNo02;          ///< ������ί�б���, 
            double              BuyPrice03;                 ///< �����, 
            unsigned long long  BuyVolume03;                ///< ������, 
            unsigned int        TotalBuyOrderNo03;          ///< ������ί�б���, 
            double              BuyPrice04;                 ///< �����, 
            unsigned long long  BuyVolume04;                ///< ������, 
            unsigned int        TotalBuyOrderNo04;          ///< ������ί�б���, 
            double              BuyPrice05;                 ///< �����, 
            unsigned long long  BuyVolume05;                ///< ������, 
            unsigned int        TotalBuyOrderNo05;          ///< ������ί�б���, 
            double              BuyPrice06;                 ///< �����, 
            unsigned long long  BuyVolume06;                ///< ������, 
            unsigned int        TotalBuyOrderNo06;          ///< ������ί�б���, 
            double              BuyPrice07;                 ///< �����, 
            unsigned long long  BuyVolume07;                ///< ������, 
            unsigned int        TotalBuyOrderNo07;          ///< ������ί�б���, 
            double              BuyPrice08;                 ///< �����, 
            unsigned long long  BuyVolume08;                ///< ������, 
            unsigned int        TotalBuyOrderNo08;          ///< ������ί�б���, 
            double              BuyPrice09;                 ///< �����, 
            unsigned long long  BuyVolume09;                ///< ������, 
            unsigned int        TotalBuyOrderNo09;          ///< ������ί�б���, 
            double              BuyPrice10;                 ///< �����, 
            unsigned long long  BuyVolume10;                ///< ������, 
            unsigned int        TotalBuyOrderNo10;          ///< ������ί�б���, 
        };
    };
    unsigned int        BuyLevelQueueNo01;                  ///< ��һ����ʾί�б���, Ϊ 0 ��ʾ����ʾ
    unsigned int        BuyLevelQueue[ORDER_LEVEL_FIFTY];   ///< ��1������, ��Ƶ���ݱ��棬�ȴ涩������,ֻ��һ���д����ݣ�50��������ʱ����

};
/// �Ͻ���L2ָ������
struct SSEL2_Index
{
    int                 LocalTimeStamp;         ///< ���ݽ���ʱ��HHMMSSMMM
    long long           PacketTimeStamp;        ///< ���ݰ�ͷʱ��YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< ��������ʱ��(����), 143025000 ��ʾ 14:30:25000
    int                 TradeTime;              ///< �ɽ�ʱ��(����),
    char                Symbol[SYMBOL_LEN];     ///< ֤ȯ����, 
    double              PreClosePrice;          ///< ���ռ�, 
    double              OpenPrice;              ///< ���̼�, 
    double              TotalAmount;            ///< �ɽ��ܶ�, 
    double              HighPrice;              ///< ��߼�, 
    double              LowPrice;               ///< ��ͼ�, 
    double              LastPrice;              ///< �ּ�, 
    unsigned long long  TotalVolume;            ///< �ɽ�����, ��
    double              ClosePrice;             ///< �����̼�, 
};
/// �Ͻ���L2��ʳɽ�
struct SSEL2_Transaction
{
    int                 LocalTimeStamp;         ///< ���ݽ���ʱ��HHMMSSMMM
    long long           PacketTimeStamp;        ///< ���ݰ�ͷʱ��YYYYMMDDHHMMSSMMM
    int                 TradeTime;              ///< �ɽ�ʱ��(����), 14302506 ��ʾ14:30:25.06
    unsigned int        RecID;                  ///< ҵ������, �� 1 ��ʼ���� TradeChannel����
    int                 TradeChannel;           ///< �ɽ�ͨ��, 
    char                Symbol[SYMBOL_LEN];     ///< ֤ȯ����, 
    double              TradePrice;             ///< �ɽ��۸�, 
    unsigned int        TradeVolume;            ///< �ɽ�����, ��Ʊ����;Ȩ֤����;ծȯ����
    double              TradeAmount;            ///< �ɽ����, 
    long long           BuyRecID;               ///< �򷽶�����, 
    long long           SellRecID;              ///< ����������, 
    char                BuySellFlag;            ///< �����̱�־, B �C ����,������;S �C ����,������;N �C δ֪
};
/// �Ͻ���L2���⼯�Ͼ���
struct SSEL2_Auction
{
    int                 LocalTimeStamp;         ///< ���ݽ���ʱ��HHMMSSMMM
    long long           PacketTimeStamp;        ///< ���ݰ�ͷʱ��YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< ��������ʱ��, 143025001 ��ʾ 14:30:25.001
    char                Symbol[SYMBOL_LEN];     ///< ֤ȯ����, 
    double              OpenPrice;              ///< ���⿪�̲ο���, 
    long long           AuctionVolume;          ///< ����ƥ����, 
    long long           LeaveVolume;            ///< ����δƥ����, 
    char                Side;                   ///< ��������, 0=��δƥ�������������ߵ�δƥ������Ϊ 0;1=����δƥ����������δƥ����=0;2=������δƥ��������δƥ����=0
};
/// �Ͻ���L2�г�����
struct SSEL2_Overview
{
    int                 LocalTimeStamp;         ///< ���ݽ���ʱ��HHMMSSMMM
    long long           PacketTimeStamp;        ///< ���ݰ�ͷʱ��YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< ��������ʱ��, 143025001 ��ʾ 14:30:25.001
    char                Symbol[SYMBOL_LEN];     ///< ֤ȯ����, 
    int                 MarketTime;             ///< �г�ʱ��, �ٷ�֮һ��
    int                 TradeDate;              ///< �г�����, 
};

/// �Ͻ���������Ȩ��̬����
struct SSEIOL1_Static
{
    int                 LocalTimeStamp;                     ///< ���ݽ���ʱ��HHMMSSMMM
    long long           PacketTimeStamp;                    ///< ���ݰ�ͷʱ��YYYYMMDDHHMMSSMMM
    char                Symbol[SYMBOL_LEN];                 ///< ֤ȯ���루��Լ���룩, ��Լ��Ȩ��Ʒ���룬8λ�ַ�;Ψһ��ʾ
    char                ContractID [19];                    ///< ��Լ���״��� , ��Լ���״���17λ��������˳���д��1����1����6λΪ���֣�ȡ���֤ȯ���룬�繤������601398��ȡ��601398����2����7λΪC(Call)����P(Put)���ֱ��ʾ�Ϲ���Ȩ�����Ϲ���Ȩ��3����8��9λ��ʾ������ݣ�4����10��11λ��ʾ�����·ݣ�5����12λ�ڳ���Ϊ��M������ʾ�·ݺ�Լ������Լ�״ε����󣬡�M���޸�Ϊ ��A�����Ա�ʾ�ú�Լ��������һ�Σ��緢���ڶ��ε�������A���޸�Ϊ��B������M���޸�Ϊ ��A�����Դ����ƣ�6����13��17λ��ʾ��Ȩ��Ȩ�۸�.����λ����
    char                SecurityName[SECURITY_NAME_LEN];    ///< ��Ȩ��Լ��ƣ�֤ȯ���ƣ� , 
    char                SymbolUnderlying[SYMBOL_LEN];       ///< ����֤ȯ����, 
    char                NameUnderlying[SECURITY_NAME_LEN];  ///< ����֤ȯ���� , 
    char                UnderlyingType [5];                 ///< ���֤ȯ���� , EBS �C ETF�� ASH �C A�� 
    char                OptionType;                         ///< ��Ȩ����, ��Ϊŷʽ��Ȩ�����ֶ�Ϊ��E������Ϊ��ʽ��Ȩ�����ֶ�Ϊ��A�� 
    char                CallOrPut;                          ///< �Ϲ��Ϲ� , �Ϲ������ֶ�Ϊ��C������Ϊ�Ϲ������ֶ�Ϊ��P�� 
    long long           ContractMultiplierUnit;             ///< ��Լ��λ , ������Ȩ��Ϣ������ĺ�Լ��λ, һ�������� 
    double              ExercisePrice;                      ///< ��Ȩ��Ȩ�� , ������Ȩ��Ϣ���������Ȩ��Ȩ�ۣ��Ҷ��룬��ȷ����;��Ȩ�۸������ȡ�������뷽ʽ����Ʊ������λС����ETF������λС����
    int                 StartDate;                          ///< �׸������� , ��Ȩ�׸�������,YYYYMMDD (��*10000+��*100+��)
    int                 EndDate;                            ///< ������� , ��Ȩ�������/��Ȩ�գ�YYYYMMDD 
    int                 ExerciseDate;                       ///< ��Ȩ��Ȩ�� , ��Ȩ��Ȩ�գ�YYYYMMDD 
    int                 DeliveryDate;                       ///< ��Ȩ������, ��Ȩ�����գ�Ĭ��Ϊ��Ȩ�յ���һ�������գ�YYYYMMDD
    int                 ExpireDate;                         ///< ��Ȩ������ , ��Ȩ�����գ�YYYYMMDD 
    char                Version;                            ///< ��Լ�汾�� , ��Ȩ��Լ�İ汾�š��¹Һ�Լ�ǡ�1�� 
    unsigned int        TotalLongPosition;                  ///< ��Լδƽ���� , ��λ�� ���ţ� 
    double              PreClosePrice;                      ///< ���ռ�, �������̼ۣ�������Ȩ��Ϣ��Ϊ����������̼۸��������յ��ļ��У���д�ο��۸񣩣��Ҷ��룬��ȷ���� 
    double              PreSettlePrice;                     ///< �����, ���ս���ۣ��Ҷ��룬��λ��Ԫ 
    double              PreClosePriceUnderlying;            ///< ������ռ�, ��Ȩ���֤ȯ��Ȩ��Ϣ�������ǰ���̼۸��Ҷ��룬��λ��Ԫ 
    char                UpDownLimitType;                    ///< �ǵ����������� , ��N����ʾ���׹���3.4.13�涨�����ǵ����������ͻ���Ȩ֤����취��22���涨 ��R����ʾ���׹���3.4.15��3.4.16�涨�����ǵ����������� 
    double              PriceUpLimit;                       ///< �Ƿ��۸�, ������Ȩ��ͣ�۸񣬾�ȷ���� 
    double              PriceDownLimit;                     ///< �����۸�, ������Ȩ��ͣ�۸񣬾�ȷ���� 
    double              MarginUnit;                         ///< ��λ��֤�� , ���ճ���һ�ź�Լ����Ҫ�ı�֤���� ������ȷ���� 
    double              MarginRatioParam1;                  ///< ��֤��������һ , ��֤������������λ��% 
    double              MarginRatioParam2;                  ///< ��֤���������� , ��֤������������λ��% 
    unsigned int        RoundLot;                           ///< ������ , һ�ֵ��ڼ��ź�Լ 
    long long           LmtOrdFloor;                        ///< �޼��걨���� , �����޼��걨���걨�������ޡ� 
    long long           LmtOrdCeiling;                      ///< �޼��걨���� , �����޼��걨���걨�������ޡ� 
    long long           MktOrdFloor;                        ///< �м��걨���� , �����м��걨���걨�������ޡ� 
    long long           MktOrdCeiling;                      ///< �м��걨���� , �����м��걨���걨�������ޡ� 
    double              TickSize;                           ///< ��С���۵�λ, ��λ��Ԫ����ȷ��0.1�壩
    char                SecurityStatusFlag[8];              ///< ��Ȩ��Լ״̬, ���ֶ�Ϊ8λ�ַ���������ÿλ��ʾ�ض��ĺ��壬�޶�������ո�
                                                            ///< ��1λ����0����ʾ�ɿ��֣���1����ʾ�����������֣��������ҿ��֣������뿪�֡�
                                                            ///< ��2λ����0����ʾδ����ͣ�ƣ���1����ʾ����ͣ�ơ�
                                                            ///< ��3λ����0����ʾδ�ٽ������գ���1����ʾ���뵽���ղ���10�������ա�
                                                            ///< ��4λ����0����ʾ����δ����������1����ʾ���10���������ں�Լ������������
                                                            ///< ��5λ����A����ʾ�����¹��Ƶĺ�Լ����E����ʾ�����ĺ�Լ����D����ʾ����ժ�Ƶĺ�Լ��
};
/// �Ͻ���������Ȩʵʱ����
struct SSEIOL1_Quotation
{
    int                 LocalTimeStamp;         ///< ���ݽ���ʱ��HHMMSSMMM
    long long           PacketTimeStamp;        ///< ���ݰ�ͷʱ��YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< ��������ʱ��, 143025001��ʾ 14:30:25.001;�����Ȩ��Լ�Ĳ�Ʒ����Ϊ��00000000�������ʾ����ʱ�䣬��ʽΪHHMMSSMMM;�гɽ�ʱ�Ż�仯
    char                Symbol[SYMBOL_LEN];     ///< ��Լ���루֤ȯ���룩, ��Ȩ��Լ�Ĳ�Ʒ����;Ψһ��ʾ
    double              PreSettlePrice;         ///< �����, 4 decimal places
    double              SettlePrice;            ///< �����, 4 decimal places
    double              OpenPrice;              ///< ���̼�, 4 decimal places
    double              HighPrice;              ///< ��߼� , 4 decimal places
    double              LowPrice;               ///< ��ͼ�, 4 decimal places
    double              LastPrice;              ///< �ּ�, 4 decimal places
    double              ClosePrice;             ///< ���̼�
    double              AuctionPrice;           ///< �������жϲο���, 4 decimal places
    long long           AuctionVolume;          ///< �������ж�����ƥ����, 
    unsigned long long  TotalPosition;          ///< �ֲ���, 
    unsigned int        SellLevelNo;            ///< ���̼�λ����, �嵵:����5���յ�λ��0���
    union
    {
        BuySellLevelInfo    SellLevel[LEVEL_FIVE];      ///< �嵵������
        struct  
        {
            double              SellPrice01;            ///< ������, ��10069<5ʱ������5  ����������֪�����Ϊ0
            unsigned long long  SellVolume01;           ///< ������, ��10069<5ʱ������5  ����������֪�����Ϊ0
            double              SellPrice02;            ///< ������, ��10069<5ʱ������5  ����������֪�����Ϊ0
            unsigned long long  SellVolume02;           ///< ������, ��10069<5ʱ������5  ����������֪�����Ϊ0
            double              SellPrice03;            ///< ������, ��10069<5ʱ������5  ����������֪�����Ϊ0
            unsigned long long  SellVolume03;           ///< ������, ��10069<5ʱ������5  ����������֪�����Ϊ0
            double              SellPrice04;            ///< ������, ��10069<5ʱ������5  ����������֪�����Ϊ0
            unsigned long long  SellVolume04;           ///< ������, ��10069<5ʱ������5  ����������֪�����Ϊ0
            double              SellPrice05;            ///< ������, ��10069<5ʱ������5  ����������֪�����Ϊ0
            unsigned long long  SellVolume05;           ///< ������, ��10069<5ʱ������5  ����������֪�����Ϊ0
        };
    };
    unsigned int            BuyLevelNo;                  ///< ���̼�λ����, �嵵:����5���յ�λ��0���
    union
    {
        BuySellLevelInfo    BuyLevel[LEVEL_FIVE];        ///< �嵵������
        struct  
        {
            double              BuyPrice01;             ///< �����, ��10068<5ʱ������5����������֪�����Ϊ0
            unsigned long long  BuyVolume01;            ///< ������, ��10068<5ʱ������5����������֪�����Ϊ0
            double              BuyPrice02;             ///< �����, ��10068<5ʱ������5����������֪�����Ϊ0
            unsigned long long  BuyVolume02;            ///< ������, ��10068<5ʱ������5����������֪�����Ϊ0
            double              BuyPrice03;             ///< �����, ��10068<5ʱ������5����������֪�����Ϊ0
            unsigned long long  BuyVolume03;            ///< ������, ��10068<5ʱ������5����������֪�����Ϊ0
            double              BuyPrice04;             ///< �����, ��10068<5ʱ������5����������֪�����Ϊ0
            unsigned long long  BuyVolume04;            ///< ������, ��10068<5ʱ������5����������֪�����Ϊ0
            double              BuyPrice05;             ///< �����, ��10068<5ʱ������5����������֪�����Ϊ0
            unsigned long long  BuyVolume05;            ///< ������, ��10068<5ʱ������5����������֪�����Ϊ0
        };
    };
    unsigned long long  TotalVolume;            ///< �ɽ�����, Trade volume of this security.�����Ȩ��Լ�Ĳ�Ʒ����Ϊ��00000000�������ʾ�������ڣ���ʽΪYYYYMMDD
    double              TotalAmount;            ///< �ɽ����, 2 decimal places
    char                SecurityPhaseTag[8];    ///< ����״̬,  ���ֶ�Ϊ4 λ�ַ���������ÿλ��ʾ�ض��ĺ��壬�޶�������ո񡣵�1 λ����S����ʾ����������ǰ��ʱ�Σ���C����ʾ���Ͼ���ʱ�Σ���T����ʾ��������ʱ�Σ���B����ʾ����ʱ�Σ���E����ʾ����ʱ�Σ���V����ʾ�������жϣ���P����ʾ��ʱͣ�ơ���2 λ����0����ʾδ����ͣ�ƣ���1����ʾ����ͣ�ơ�
};

/// �����̬����
struct SZSEL1_Static
{
    char    Symbol[SYMBOL_LEN];     ///< ֤ȯ����
};
/// ���L1ʵʱ����
struct SZSEL1_Quotation
{
    char    Symbol[SYMBOL_LEN];     ///< ֤ȯ����
};
/// ���������Ϣ
struct MiscFeeInfo
{
    short               MiscFeeType;            ///< ����������
    unsigned int        MiscFeeUnit;            ///< ������õ�λ
    double              MiscFeeAmount;          ///< ������ý��,6λС��
};
/// ��ѡ֤ȯ��Ϣ
struct AltSymbolInfo
{
    char                AltSymbol[SYMBOL_LEN];  ///< ��ѡ֤ȯ����
    char                AltSymbolSource[5];     ///< ��ѡ֤ȯ����Դ
};
/// ���L2��̬����
struct SZSEL2_Static
{
    int                 LocalTimeStamp;                     ///< ���ݽ���ʱ��HHMMSSMMM
    long long           PacketTimeStamp;                    ///< ���ݰ�ͷʱ��YYYYMMDDHHMMSSMMM
    unsigned int        RecID;                              ///< ��¼����
    char                Symbol[SYMBOL_LEN];                 ///< ֤ȯ����
    char                SecurityName[SECURITY_NAME_LEN];    ///< ֤ȯ����
    char                SecurityEN[SECURITY_EN_LEN];        ///< ֤ȯӢ�ļ��
    char                SymbolUnderlying[SYMBOL_LEN];       ///< ����֤ȯ����
    char                SymbolSource[5];                    ///< ֤ȯ����Դ
    unsigned int        AltSymbolNo;                        ///< ��ѡ֤ȯ�������
    union
    {
        AltSymbolInfo   AltSymbol[3];           ///< ��ѡ֤ȯ������Ϣ
        struct
        {
            char        AltSymbol1[SYMBOL_LEN]; ///< ��ѡ֤ȯ����
            char        AltSymbolSource1[5];    ///< ��ѡ֤ȯ����Դ
            char        AltSymbol2[SYMBOL_LEN]; ///< ��ѡ֤ȯ����
            char        AltSymbolSource2[5];    ///< ��ѡ֤ȯ����Դ
            char        AltSymbol3[SYMBOL_LEN]; ///< ��ѡ֤ȯ����
            char        AltSymbolSource3[5];    ///< ��ѡ֤ȯ����Դ
        };
    };
    char                IndustryType[5];        ///< ��ҵ����
    char                Currency[5];            ///< ����
    double              ParValue;               ///< ÿ����ֵ,3λС��
    unsigned long long  IssuedVolume;           ///< �ܷ�����
    unsigned long long  OutstandingShare;       ///< ��ͨ����
    double              PreYearEPS;             ///< ����ÿ������,4λС��
    double              YearEPS;                ///< ����ÿ������,4λС��
    double              NAV;                    ///< ����T-1���ۼƾ�ֵ,4λС��
    unsigned int        MiscFeeNo;              ///< ������������
    union
    {
        MiscFeeInfo         MiscFee[3];         ///< �������Ϣ
        struct
        {
            short               MiscFeeType1;               ///< ����������
            unsigned int        MiscFeeUnit1;               ///< ������õ�λ
            double              MiscFeeAmount1;             ///< ������ý��,6λС��
            short               MiscFeeType2;               ///< ����������
            unsigned int        MiscFeeUnit2;               ///< ������õ�λ
            double              MiscFeeAmount2;             ///< ������ý��,6λС��
            short               MiscFeeType3;               ///< ����������
            unsigned int        MiscFeeUnit3;               ///< ������õ�λ
            double              MiscFeeAmount3;             ///< ������ý��,6λС��
        };
    };
    int                 IssueDate;              ///< ��������YYYYMMDD,��20140821Ϊ2014��8��21��
    char                BondType;               ///< ծȯ����
    double              CouponRate;             ///< Ʊ������,6λС��
    double              ConversionPrice;        ///< ��Ȩ�۸�,3λС��
    char                OptionType;             ///< ��ʽ/ŷʽ/��Ľ��ʽ
    char                CallOrPut;              ///< Call/Put��־
    char                WarrantClearingType;    ///< Ȩ֤���㷽ʽ
    double              ConversionRatio;        ///< ��Ȩ����,4λС��
    int                 ConversionBeginDate;    ///< ��Ȩ��ʼ����YYYYMMDD,��20140821Ϊ2014��8��21��
    int                 ConversionEndDate;      ///< ��Ȩ��������YYYYMMDD,��20140821Ϊ2014��8��21��
    int                 InterestAccrualDate;    ///< ��Ϣ��YYYYMMDD,��20140821Ϊ2014��8��21��
    int                 MaturityDate;           ///< ���ڽ�����YYYYMMDD,��20140821Ϊ2014��8��21��
    unsigned int        RoundLot;               ///< ���׵�λ
    unsigned int        BuyVolumeUnit;          ///< ��������λ
    unsigned int        SellVolumeUnit;         ///< ��������λ
    unsigned int        DeclareVolumeCeiling;   ///< ÿ������
    char                TradeMethod;            ///< ���׷���
    double              TickSize;               ///< �۸�λ,3λС��
    char                PriceLimitType;         ///< �޼۲�������
    double              AuctionPriceLimit;      ///< ���Ͼ����޼۲���,3λС��
    double              ContTradePriceLmt;      ///< ���������޼۲���,3λС��
    double              PriceUpLimit;           ///< �Ƿ��۸�,3λС��
    double              PriceDownLimit;         ///< �����۸�,3λС��
    double              BlockPriceUpLmt;        ///< ���ǵ�֤ͣȯ���ڽ��׳����ս�����߼���ļ۸�����,3λС��
    double              BlockPriceDownLmt;      ///< ���ǵ�֤ͣȯ���ڽ��׳����ս�����ͼ���ļ۸�����,3λС��
    double              ContractMultiplier;     ///< ծȯ�ۺϻع���׼ȯ����,3λС��
    double              GageRate;               ///< ����Ʒ������,2λС��
    char                CrdBuyUnderlying;       ///< ����������
    char                CrdSellUnderlying;      ///< ��ȯ�������
    unsigned int        ParticipateIndexNo;    ///< ����ָ������
    char                MarketMakerFlag;        ///< �����̱�־
    char                CFICode[6];             ///< ֤ȯ���
    char                SecuritySubType[6];     ///< ֤ȯ�����
    char                SecurityTypeID;         ///< ֤ȯ����
    unsigned int        StatusID;               ///< ����״̬
    char                XRXDFlag;               ///< ��Ȩ��Ϣ��־
    char                TradingMechanism;       ///< ��Ʒ��������
    char                CrdPriceCheckType;      ///< ��ۼ�鷽ʽ
    char                NetVotingFlag;          ///< ����ͶƱ��־
    char                ShrstrurefmFlag;        ///< �ɸ�״̬��־
    char                OfferingFlag;           ///< �Ƿ���ҪԼ�չ��ڡ��Ƿ���ת���ڣ���תծ�����Ƿ�����Ȩ�ڣ�Ȩ֤��  
};
/// ���L2֤ȯ״̬
struct SZSEL2_Status
{
    int                 LocalTimeStamp;         ///< ���ݽ���ʱ��HHMMSSMMM
    long long           PacketTimeStamp;        ///< ���ݰ�ͷʱ��YYYYMMDDHHMMSSMMM
    char                Symbol[SYMBOL_LEN];     ///< ֤ȯ����
    char                SecurityTag[5];         ///< �ɽ�֤ȯ���ǰ׺
    char                TradeStage;             ///< ֤ȯ����״̬
    char                CrdBuyStatus;           ///< ��ǰ�������뿪��״̬
    char                CrdSellStatus;          ///< ��ǰ��ȯ��������״̬
    char                SubScribeStatus;        ///< �Ƿ������깺�����Ż��𣩡�������ת�ɣ���תծ����������Ȩ��Ȩ֤��
    char                RedemptionStatus;       ///< �Ƿ�������أ����Ż��𣩡���������ۣ���תծ��
    char                WarrantCreated;         ///< �����Ƿ��д��跢��
    char                WarrantDropped;         ///< �����Ƿ���ע������
};
/// ���L2ʵʱ����
struct SZSEL2_Quotation
{
    int                 LocalTimeStamp;         ///< ���ݽ���ʱ��HHMMSSMMM
    long long           PacketTimeStamp;        ///< ���ݰ�ͷʱ��YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< ��������ʱ��HHMMSSMMM����Ӧtag10178
    char                Symbol[SYMBOL_LEN];     ///< ֤ȯ����
    double              PreClosePrice;          ///< �������̼�,3λС��
    double              OpenPrice;              ///< ���̼�,3λС��
    double              HighPrice;              ///< ��߼�,3λС��
    double              LowPrice;               ///< ��ͼ�,3λС��
    double              LastPrice;              ///< �ּ�,3λС��
    unsigned long long  TotalNo;                ///< �ɽ�����
    unsigned long long  TotalVolume;            ///< �ɽ�����
    double              TotalAmount;            ///< �ɽ��ܽ��,3λС��
    unsigned long long  TotalPosition;          ///< ��Լ�ֲ���
    double              PERatio1;               ///< ��ӯ�� 1,2λС��
    double              PERatio2;               ///< ��ӯ�� 2,2λС��
    char                CloseFlag;              ///< ���б�־
    unsigned long long  TotalSellOrderVolume;   ///< ί��������������Ч���۷�Χ�ڣ�
    double              WtAvgSellPrice;         ///< ��Ȩƽ�������۸���Ч���۷�Χ�ڣ�,3λС��
    unsigned int        SellLevelNo;            ///< ������λ�����۸��ɵ����ߣ�
    union
    {
        BuySellLevelInfo3    SellLevel[LEVEL_TEN];       ///< ʮ��������
        struct
        {
            double              SellPrice01;            ///< ������,3λС��
            unsigned long long  SellVolume01;           ///< ������
            unsigned int        TotalSellOrderNo01;     ///< ����λ��ί�б���
            double              SellPrice02;            ///< ������
            unsigned long long  SellVolume02;           ///< ������
            unsigned int        TotalSellOrderNo02;     ///< ����λ��ί�б���
            double              SellPrice03;            ///< ������
            unsigned long long  SellVolume03;           ///< ������
            unsigned int        TotalSellOrderNo03;     ///< ����λ��ί�б���
            double              SellPrice04;            ///< ������
            unsigned long long  SellVolume04;           ///< ������
            unsigned int        TotalSellOrderNo04;     ///< ����λ��ί�б���
            double              SellPrice05;            ///< ������
            unsigned long long  SellVolume05;           ///< ������
            unsigned int        TotalSellOrderNo05;     ///< ����λ��ί�б���
            double              SellPrice06;            ///< ������
            unsigned long long  SellVolume06;           ///< ������
            unsigned int        TotalSellOrderNo06;     ///< ����λ��ί�б���
            double              SellPrice07;            ///< ������
            unsigned long long  SellVolume07;           ///< ������
            unsigned int        TotalSellOrderNo07;     ///< ����λ��ί�б���
            double              SellPrice08;            ///< ������
            unsigned long long  SellVolume08;           ///< ������
            unsigned int        TotalSellOrderNo08;     ///< ����λ��ί�б���
            double              SellPrice09;            ///< ������
            unsigned long long  SellVolume09;           ///< ������
            unsigned int        TotalSellOrderNo09;     ///< ����λ��ί�б���
            double              SellPrice10;            ///< ������
            unsigned long long  SellVolume10;           ///< ������
            unsigned int        TotalSellOrderNo10;     ///< ����λ��ί�б���
        };
    };
    unsigned int        SellLevelQueueNo01;                 ///< ��һ����ʾί�б���
    unsigned int        SellLevelQueue[ORDER_LEVEL_FIFTY];  ///< ��һ��ί��������50�ʣ����㲹0
    unsigned long long  TotalBuyOrderVolume;                ///< ί��������������Ч���۷�Χ�ڣ�
    double              WtAvgBuyPrice;                      ///< ��Ȩƽ������۸���Ч���۷�Χ�ڣ�,3λС��
    unsigned int        BuyLevelNo;                         ///< ����λ�����۸��ɸ����ͣ�
    union
    {
        BuySellLevelInfo3    BuyLevel[LEVEL_TEN];       ///< ʮ��������
        struct
        {
            double              BuyPrice01;             ///< �����,3λС��
            unsigned long long  BuyVolume01;            ///< ������
            unsigned int        TotalBuyOrderNo01;      ///< ���λ��ί�б���
            double              BuyPrice02;             ///< �����
            unsigned long long  BuyVolume02;            ///< ������
            unsigned int        TotalBuyOrderNo02;      ///< ���λ��ί�б���
            double              BuyPrice03;             ///< �����
            unsigned long long  BuyVolume03;            ///< ������
            unsigned int        TotalBuyOrderNo03;      ///< ���λ��ί�б���
            double              BuyPrice04;             ///< �����
            unsigned long long  BuyVolume04;            ///< ������
            unsigned int        TotalBuyOrderNo04;      ///< ���λ��ί�б���
            double              BuyPrice05;             ///< �����
            unsigned long long  BuyVolume05;            ///< ������
            unsigned int        TotalBuyOrderNo05;      ///< ���λ��ί�б���
            double              BuyPrice06;             ///< �����
            unsigned long long  BuyVolume06;            ///< ������
            unsigned int        TotalBuyOrderNo06;      ///< ���λ��ί�б���
            double              BuyPrice07;             ///< �����
            unsigned long long  BuyVolume07;            ///< ������
            unsigned int        TotalBuyOrderNo07;      ///< ���λ��ί�б���
            double              BuyPrice08;             ///< �����
            unsigned long long  BuyVolume08;            ///< ������
            unsigned int        TotalBuyOrderNo08;      ///< ���λ��ί�б���
            double              BuyPrice09;             ///< �����
            unsigned long long  BuyVolume09;            ///< ������
            unsigned int        TotalBuyOrderNo09;      ///< ���λ��ί�б���
            double              BuyPrice10;             ///< �����
            unsigned long long  BuyVolume10;            ///< ������
            unsigned int        TotalBuyOrderNo10;      ///< ���λ��ί�б���
        };
    };
    unsigned int        BuyLevelQueueNo01;                  ///< ��һ����ʾί�б���
    unsigned int        BuyLevelQueue[ORDER_LEVEL_FIFTY];   ///< ��һ��ί��������50�ʣ����㲹0
};
/// ���L2ָ������
struct SZSEL2_Index
{
    int                 LocalTimeStamp;         ///< ���ݽ���ʱ��HHMMSSMMM
    long long           PacketTimeStamp;        ///< ���ݰ�ͷʱ��YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< ��������ʱ��HHMMSSMMM����Ӧtag10178
    char                Symbol[SYMBOL_LEN];     ///< ֤ȯ����
    double              PreClosePrice;          ///< ǰ����ָ��,4λС��
    double              OpenPrice;              ///< ����ָ��,4λС��
    double              HighPrice;              ///< ���ָ��,4λС��
    double              LowPrice;               ///< ���ָ��,4λС��
    double              LastPrice;              ///< ����ָ��,4λС��
    double              TotalAmount;            ///< ���������Ӧָ���ĳɽ����,3λС��
    unsigned long long  TotalNo;                ///< ���������Ӧָ���ĳɽ�����
    unsigned long long  TotalVolume;            ///< ���������Ӧָ���Ľ�������
    char                CloseFlag;              ///< ���б�־
};
/// ���L2���ί��
struct SZSEL2_Order
{
    int                 LocalTimeStamp;         ///< ���ݽ���ʱ��HHMMSSMMM
    long long           PacketTimeStamp;        ///< ���ݰ�ͷʱ��YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< ί��ʱ��HHMMSSMMM����Ӧtag8500
    unsigned int        SetID;                  ///< ֤ȯ������
    unsigned int        RecID;                  ///< ί������
    char                Symbol[SYMBOL_LEN];     ///< ֤ȯ����
    double              OrderPrice;             ///< ί�м۸�,3λС��
    unsigned int        OrderVolume;            ///< ί������
    char                OrderType;              ///< ί�����
    char                OrderCode;              ///< ί�д���
};
/// ���L2��ʳɽ�
struct SZSEL2_Transaction
{
    int                 LocalTimeStamp;         ///< ���ݽ���ʱ��HHMMSSMMM
    long long           PacketTimeStamp;        ///< ���ݰ�ͷʱ��YYYYMMDDHHMMSSMMM
    int                 Time;                   ///< �ɽ�ʱ��HHMMSSMMM����Ӧtag10013
    unsigned int        SetID;                  ///< ֤ȯ������
    unsigned int        RecID;                  ///< �ɽ�����
    unsigned int        BuyOrderID;             ///< ��ί������
    unsigned int        SellOrderID;            ///< ����ί������
    char                Symbol[SYMBOL_LEN];     ///< ֤ȯ����
    double              TradePrice;             ///< �ɽ��۸�,3λС��
    unsigned int        TradeVolume;            ///< �ɽ�����
    char                TradeCode;              ///< �ɽ�����
    char                TradeType;              ///< �ɽ����
};
/// �н���L2ʵʱ����
struct CFFEXL2_Quotation
{
    int                 LocalTimeStamp;              ///< ����ʱ�� 
    int                 TradeDate;                   ///< �ɽ����� YYYYMMDD ͳһΪ���׹������ڣ���������������ѭ��ԭ��
    int                 Time;                        ///< ��������ʱ�� �����ֶκϳ�һ����HHMMSSMMM
    char                Symbol[SYMBOL_LEN];          ///< ֤ȯ����
    double              PreClosePrice;               ///< ���ռ� ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
    double              PreSettlePrice;              ///< ����� ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
    double              OpenPrice;                   ///< ���̼� ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
    double              HighPrice;                   ///< ��߼� ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
    double              LowPrice;                    ///< ��ͼ� ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
    double              TradePrice;                  ///< ���¼� ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
    double              ClosePrice;                  ///< ���̼� ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
    double              SettlePrice;                 ///< ����� ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
    double              PriceUpLimit;                ///< ��ͣ�� ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
    double              PriceDownLimit;              ///< ��ͣ�� ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
    unsigned long long  PreTotalPosition;            ///< ��ֲ���
    unsigned long long  TotalPosition;               ///< �ֲ���
    double              PreDelta;                    ///< ����ʵ�� ǰһ�նԳ�ֵ
    double              Delta;                       ///< ����ʵ�� �Գ�ֵ����Ȩ�۸�仯/�ڻ��۸�仯
    char                SettleGroupID[SETTLE_LEN];   ///< ���������
    unsigned int        SettleID;                    ///< ������
    unsigned long long  TotalVolume;                 ///< �ܳɽ���
    double              TotalAmount;                 ///< �ܳɽ��� ��ЧС��λΪ3λ
    union
    {
        BuySellLevelInfo    SellLevel[LEVEL_FIVE];   ///< �嵵������
        struct
        {
            double              SellPrice01;         ///< ����һ ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
            unsigned long long  SellVolume01;        ///< ����һ
            double              SellPrice02;         ///< ���۶� ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
            unsigned long long  SellVolume02;        ///< ������
            double              SellPrice03;         ///< ������ ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
            unsigned long long  SellVolume03;        ///< ������
            double              SellPrice04;         ///< ������ ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
            unsigned long long  SellVolume04;        ///< ������
            double              SellPrice05;         ///< ������ ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
            unsigned long long  SellVolume05;        ///< ������
        };
    };
    union
    {
        BuySellLevelInfo    BuyLevel[LEVEL_FIVE];    ///< �嵵������
        struct
        {
            double              BuyPrice01;          ///< ���һ ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
            unsigned long long  BuyVolume01;         ///< ����һ
            double              BuyPrice02;          ///< ��۶� ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
            unsigned long long  BuyVolume02;         ///< ������
            double              BuyPrice03;          ///< ����� ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
            unsigned long long  BuyVolume03;         ///< ������
            double              BuyPrice04;          ///< ����� ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
            unsigned long long  BuyVolume04;         ///< ������
            double              BuyPrice05;          ///< ����� ָ����ЧС��λΪ2λ����ծ��ЧС��λΪ3λ
            unsigned long long  BuyVolume05;         ///< ������
        };
    };
};
/// �н���L2��̬����
typedef CFFEXL2_Quotation CFFEXL2_Static;
/// ֣������̬����
struct CZCEL1_Static
{
    char    Symbol[SYMBOL_LEN];     ///< ֤ȯ����
};
/// ֣����ʵʱ����
struct CZCEL1_Quotation
{
    char    Symbol[SYMBOL_LEN];     ///< ֤ȯ����
};
/// ��������̬����
struct DCEL1_Static
{
    char    Symbol[SYMBOL_LEN];     ///< ֤ȯ����
};
/// ������L1�������
struct DCEL1_Quotation
{
    char    Symbol[SYMBOL_LEN];     ///< ֤ȯ����
};
/// ������L1�����������
struct DCEL1_ArbiQuotation
{
    char    Symbol[SYMBOL_LEN];     ///< ֤ȯ����
};
/// ������L2��̬����
struct DCEL2_Static
{
    char    Symbol[SYMBOL_LEN];     ///< ֤ȯ����
};
/// ������L2�����������
struct DCEL2_Quotation
{
    char    Symbol[SYMBOL_LEN];     ///< ֤ȯ����
};
/// ������L2���������������
struct DCEL2_ArbiQuotation
{
    char    Symbol[SYMBOL_LEN];     ///< ֤ȯ����
};
/// ������L2ʵʱ�����
struct DCEL2_RealTimePrice
{
    char    Symbol[SYMBOL_LEN];     ///< ֤ȯ����
};
/// ������L2ί��ͳ������
struct DCEL2_OrderStatistic
{
    char    Symbol[SYMBOL_LEN];     ///< ֤ȯ����
};
/// ������L2�ּ۳ɽ�������
struct DCEL2_MarchPriceQty
{
    char    Symbol[SYMBOL_LEN];     ///< ֤ȯ����
};
/// ��������̬����
struct SHFEL1_Static
{
    char    Symbol[SYMBOL_LEN];     ///< ֤ȯ����
};

/// ������ʵʱ����
struct SHFEL1_Quotation
{
    char    Symbol[SYMBOL_LEN];     ///< ֤ȯ����

};

/// ֤ȯ����
struct StockSymbol
{
    char    Symbol[SYMBOL_LEN + MARKET_TAG_LEN];        ///< ��ѯ�����б��صĹ�Ʊ���룬���г���־
};

/// ��������ַ
struct ServerState
{
    MsgType msgType;            ///< ��Ϣ����
    char    IP[16];             ///< ��������ַ��127.0.0.1
    unsigned short   Port;      ///< �˿�
    bool    Connected;          ///< ����״̬��true-�����У�false-δ����
};

#pragma pack()





#endif // GTA_QTS_STRUCT_H_

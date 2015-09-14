///
/// @file    OutputData.h
/// @brief   �·����ݽṹ
///

#ifndef _OUTPUT_DATA_H
#define _OUTPUT_DATA_H

// ��������V1.5�汾�ַ�����ʹ�ã�1.5��1.7�ַ������������ṹ�岻ͬ
#define OLD_DISTRISERVER
#ifdef _WIN32
#include <windows.h>
#else
typedef unsigned char      BYTE;
typedef unsigned short int WORD;
typedef unsigned int       DWORD;
typedef unsigned int       UINT;
typedef long long          LONGLONG;
typedef long long          __int64;
typedef unsigned long long UINT64;
typedef int                INT;
typedef __int64            INT64;
typedef unsigned int UINT32, *PUINT32;
typedef unsigned long       ULONG;
typedef unsigned short      UINT16;
typedef unsigned char UINT8, *PUINT8;
#endif
#pragma pack(1)

/// �н�����ָ�ڻ���������ṹ. 
typedef struct _ZJS_Future_Output
{
    char    szStockNo[6];           ///< �ڻ����� 
    double  dChg;                   ///< �ǵ� 
    double  dChgPct;                ///< �ǵ��� 
    double  dVolume;                ///< �������� 
    double  dAmount;                ///< �ɽ��ܽ�� 
    double  dLastTrade;             ///< �ɽ��� 
    double  dLastVolume;            ///< ˲�� 
    double  dUpB;                   ///< ��ͣ�� 
    double  dLowB;                  ///< ��ͣ�� 
    double  dHigh;                  ///< ������� 
    double  dLow;                   ///< ������� 
    double  dYclose;                ///< ���� 
    double  dOpen;                  ///< ���� 
    double  dAvgPrice;              ///< ���� 
    double  dPriceGap;              ///< �n�� 
    double  dBuyprice1;             ///< ���һ 
    double  dBuyprice2;             ///< ��۶� 
    double  dBuyprice3;             ///< ����� 
    double  dBuyprice4;             ///< ����� 
    double  dBuyprice5;             ///< ����� 
    double  dBuyvol1;               ///< ����һ 
    double  dBuyvol2;               ///< ������ 
    double  dBuyvol3;               ///< ������ 
    double  dBuyvol4;               ///< ������ 
    double  dBuyvol5;               ///< ������ 
    double  dSellprice1;            ///< ����һ 
    double  dSellprice2;            ///< ���۶� 
    double  dSellprice3;            ///< ������ 
    double  dSellprice4;            ///< ������ 
    double  dSellprice5;            ///< ������ 
    double  dSellvol1;              ///< ����һ 
    double  dSellvol2;              ///< ������ 
    double  dSellvol3;              ///< ������ 
    double  dSellvol4;              ///< ������ 
    double  dSellvol5;              ///< ������ 
    double  dPreOpenInterest;       ///< ��ֲ��� 
    double  dOpenInterest;          ///< �ֲ��� 
    double  dSettlementPrice;       ///< ������
    char    szTradingDay[9];        ///< �������� YYYYMMDD
    char    szUpdateTime[9];        ///< ����ʱ�� HH:MM:SS
    double  dPreSettlementPrice;    ///< ���ս���� 
    // �����ֶ�
    char    szSettlementGroupID[9]; ///< ���������
    int     nSettleID;              ///< ������
    double  dClosePrice;            ///< ������
    double  dPreDelta;              ///< ����ʵ��
    double  dCurrDelta;             ///< ����ʵ��
    int     nUpdateMillisec;        ///< ����޸ĺ���
}ZJS_Future_Output;

/// �н�����ָ��Ȩ��������ṹ. 
typedef struct _CFIO_Output
{
    char    szStockNo[31];          ///< ��Ȩ���� 
    int     dVolume;                ///< �������� 
    double  dAmount;                ///< �ɽ��ܽ�� 
    double  dLastTrade;             ///< �ɽ���
    double  dUpB;                   ///< ��ͣ�� 
    double  dLowB;                  ///< ��ͣ�� 
    double  dHigh;                  ///< ������� 
    double  dLow;                   ///< ������� 
    double  dYclose;                ///< ���� 
    double  dOpen;                  ///< ����
    double  dPreOpenInterest;       ///< ��ֲ��� 
    double  dOpenInterest;          ///< �ֲ��� 
    double  dSettlementPrice;       ///< ������
    char    szTradingDay[9];        ///< �������� YYYYMMDD
    char    szUpdateTime[9];        ///< ����ʱ�� HH:MM:SS
    int     nUpdateMillisec;        ///< ����޸ĺ���
    double  dPreSettlementPrice;    ///< ���ս���� 
    char    szSettlementGroupID[9]; ///< ���������
    int     nSettleID;              ///< ������
    double  dClosePrice;            ///< ������
    double  dPreDelta;              ///< ����ʵ��
    double  dCurrDelta;             ///< ����ʵ��
    double  dBuyprice1;             ///< ���һ 
    int     dBuyvol1;               ///< ����һ 
    double  dBuyprice2;             ///< ��۶� 
    int     dBuyvol2;               ///< ������ 
    double  dBuyprice3;             ///< ����� 
    int     dBuyvol3;               ///< ������ 
    double  dBuyprice4;             ///< ����� 
    int     dBuyvol4;               ///< ������ 
    double  dBuyprice5;             ///< ����� 
    int     dBuyvol5;               ///< ������ 
    double  dSellprice1;            ///< ����һ 
    int     dSellvol1;              ///< ����һ 
    double  dSellprice2;            ///< ���۶� 
    int     dSellvol2;              ///< ������ 
    double  dSellprice3;            ///< ������ 
    int     dSellvol3;              ///< ������ 
    double  dSellprice4;            ///< ������ 
    int     dSellvol4;              ///< ������ 
    double  dSellprice5;            ///< ������ 
    int     dSellvol5;              ///< ������ 
}CFIO_Output;

/// ֣����Ʒ�ڻ���������ṹ. 
typedef struct _ZZ_Future_Output
{
    char    szInstrumentID[20];     ///< ��Լ���� 
    double  dPreClosePrice;         ///< ǰ���̼۸� 
    double  dPreSettlePrice;        ///< ǰ����۸� 
    double  dOpenPrice;             ///< ���̼� 
    double  dBidPrice;              ///< ����۸� 
    DWORD   dwBidSize;              ///< �������� 
    double  dAskPrice;              ///< ������ 
    DWORD   dwAskSize;              ///< �������� 
    double  dClosePrice;            ///< ���¼� 
    DWORD   dwOpenInterest;         ///< �ֲ��� 
    double  dHighPrice;             ///< ��߼� 
    double  dLowPrice;              ///< ��ͼ� 
    double  dClosePrice2;           ///< ���̼� 
    double  dSettlePrice;           ///< ���ս������� 
    double  dClearPrice;            ///< ����� 
    double  dAveragePrice;          ///< ���� 
    double  dListHighPrice;         ///< ��ʷ��߳ɽ��۸� 
    double  dListLowPrice;          ///< ��ʷ��ͳɽ��۸� 
    double  dUpperLimit;            ///< ��ͣ�� 
    double  dLowerLimit;            ///< ��ͣ�� 
    DWORD   dwTotalVolume;          ///< �ܳɽ��� 
    DWORD   dwTradingDate;          ///< ���� 
    DWORD   dwTradingTime;          ///< ʱ�� 
    DWORD   dwTransaction;          ///< �ɽ����� 
}ZZ_Future_Output;
#pragma pack()

/// ������Ʒ�ڻ���������ṹ. 
typedef struct _DL_Future_Output
{
    WORD        wSize;
    BYTE        btQuotFlag;         ///< 1:BastQuot, 2:ArbiBastQuot 

    char        szTradingDate[8];   ///< �������� 
    char        szContractID[20];   ///< ��Լ�� 
    UINT        nID;                ///< ������ 
    char        szContractName[40]; ///< ��Լ���� 
    double      dClosePrice;        ///< ���¼� 
    double      dHighPrice;         ///< ��߼� 
    double      dLowPrice;          ///< ��ͼ� 
    UINT        nTotalVolum;        ///< ���³ɽ��� 
    UINT        nPrevTotalVolume;   ///< �ɽ��� 
    double      dTurnover;          ///< �ɽ��� 
    UINT        nPrevOpenInterest;  ///< ��ʼ�ֲ��� 
    UINT        nOpenInterest;      ///< �ֲ��� 
    INT         nInterestChg;       ///< �ֲ����仯 
    double      dClearPrice;        ///< ������ 
    double      dListLowPrice;      ///< ��ʷ��ͼ� 
    double      dListHighPrice;     ///< ��ʷ��߼� 
    double      dUpperLimit;        ///< ��ͣ�� 
    double      dLowerLimit;        ///< ��ͣ�� 
    double      dLastClearPrice;    ///< ���ս���� 
    double      dClosePrice3;       ///< �������̼� 
    double      dBidPrice;          ///< ����� 
    UINT        nBidSize;           ///< ������ 
    UINT        nBidImplyQty;       ///< �����Ƶ��� 
    double      dAskPrice;          ///< ������ 
    UINT        nAskSize;           ///< ������ 
    UINT        nAskImplyQty;       ///< �����Ƶ��� 
    double      dAveragePrice;      ///< ���վ��� 
    char        szTradingTime[12];  ///< ����ʱ�� 
    double      dOpenPrice;         ///< ���̼� 
    double      dClosePrice2;       ///< ���̼� 
}DL_Future_Output;  //size:248

/// �Ϻ���Ʒ�ڻ���������ṹ. 
typedef struct _SH_SFX_Output
{
    char    TradingDay[9];          ///< ������ 
    char    SettlementGroupID[9];   ///< ��������� 
    int     SettlementID;           ///< ������ 
    double  LastPrice;              ///< ���¼� 
    double  PreSettlementPrice;     ///< ����� 
    double  PreClosePrice;          ///< ������ 
    double  PreOpenInterest;        ///< ��ֲ��� 
    double  OpenPrice;              ///< ���� 
    double  HighestPrice;           ///< ��߼� 
    double  LowestPrice;            ///< ��ͼ� 
    int     Volume;                 ///< ���� 
    double  Turnover;               ///< �ɽ���� 
    double  OpenInterest;           ///< �ֲ��� 
    double  ClosePrice;             ///< ������ 
    double  SettlementPrice;        ///< ����� 
    double  UpperLimitPrice;        ///< ��ͣ��� 
    double  LowerLimitPrice;        ///< ��ͣ��� 
    double  PreDelta;               ///< ����ʵ�� 
    double  CurrDelta;              ///< ����ʵ�� 
    char    UpdateTime[9];          ///< ����޸�ʱ�� 
    int     UpdateMillisec;         ///< ����޸ĺ��� 
    char    InstrumentID[31];       ///< ��Լ���� 
    double  BidPrice1;              ///< �����һ 
    int     BidVolume1;             ///< ������һ 
    double  AskPrice1;              ///< ������һ 
    int     AskVolume1;             ///< ������һ 
    double  BidPrice2;              ///< ����۶� 
    int     BidVolume2;             ///< �������� 
    double  AskPrice2;              ///< �����۶� 
    int     AskVolume2;             ///< �������� 
    double  BidPrice3;              ///< ������� 
    int     BidVolume3;             ///< �������� 
    double  AskPrice3;              ///< �������� 
    int     AskVolume3;             ///< �������� 
    double  BidPrice4;              ///< ������� 
    int     BidVolume4;             ///< ��������     
    double  AskPrice4;              ///< ��������     
    int     AskVolume4;             ///< �������� 
    double  BidPrice5;              ///< ������� 
    int     BidVolume5;             ///< �������� 
    double  AskPrice5;              ///< �������� 
    int     AskVolume5;             ///< �������� 
    DWORD   dwTransaction;          ///< �ɽ����� 
    char    ActionDay[9];           ///< ҵ�������� YYYYMMDD
}SH_SFX_Output;

#pragma pack(1)
/// �����������ṹ. 
typedef struct _STSendTradeInfo
{
    char szStockCode[16];                           ///< ��Ʊ���� 
    char szStockName[64];                           ///< ��Ʊ���� 
    DWORD dwDate;                                   ///< YYYYMMDD 
    DWORD dwTime;                                   ///< HHMMSS 
    float fHighPrice;                               ///< ��߼� 
    float fLowPrice;                                ///< ��ͼ� 
    float fDifferencePrice;                         ///< �ǵ� 
    float fDiffRate;                                ///< �ǵ��� 
    float fPrice;                                   ///< �ɽ��� 
    float fAveragePrice;                            ///< ���� 
    LONGLONG llLastVol;                             ///< ���� 
    float fOpenPrice;                               ///< ���̼� 
    float fClosePrice;                              ///< ���̼� 
    float fPreClosePrice;                           ///< ���ռ� 
    LONGLONG llTotalMoney;                          ///< ��������ɽ���� 
    LONGLONG llTotalAmount;                         ///< ��������ɽ��� 
    float fNominalPrice;                            ///< ���̼� 
    char cNominalPriceType;                         ///< ���̼����� 
    float fIndicativeEquilibriumPrice;              ///< �ο�ƽ��۸� 
    LONGLONG llIndicativeEquilibriumVolume;         ///< �ο�ƽ��ɽ��� 
    char cPublicTradeType;                          ///< �������� 

    char cOrderSide;                                ///< �������� 

    DWORD   Sv10;       ///< ����10
    DWORD   Sv9;        ///< ����9
    DWORD   Sv8;        ///< ����8
    DWORD   Sv7;        ///< ����7
    DWORD   Sv6;        ///< ����6
    DWORD   Sv5;        ///< ����5
    DWORD   Sv4;        ///< ����4
    DWORD   Sv3;        ///< ����3
    DWORD   Sv2;        ///< ����2
    DWORD   Sv1;        ///< ����1

    float   S10;        ///< ����10
    float   S9;         ///< ����9
    float   S8;         ///< ����8
    float   S7;         ///< ����7
    float   S6;         ///< ����6
    float   S5;         ///< ����5
    float   S4;         ///< ����4
    float   S3;         ///< ����3
    float   S2;         ///< ����2
    float   S1;         ///< ����1

    DWORD   Bv10;       ///< ����10
    DWORD   Bv9;        ///< ����9
    DWORD   Bv8;        ///< ����8
    DWORD   Bv7;        ///< ����7
    DWORD   Bv6;        ///< ����6
    DWORD   Bv5;        ///< ����5
    DWORD   Bv4;        ///< ����4
    DWORD   Bv3;        ///< ����3
    DWORD   Bv2;        ///< ����2
    DWORD   Bv1;        ///< ����1

    float   B10;        ///< ���10
    float   B9;         ///< ���9
    float   B8;         ///< ���8
    float   B7;         ///< ���7
    float   B6;         ///< ���6
    float   B5;         ///< ���5
    float   B4;         ///< ���4
    float   B3;         ///< ���3
    float   B2;         ///< ���2
    float   B1;         ///< ���1

    LONGLONG llVolumeSum;    ///< �Զ����̳ɽ���  (PublicTradeTypeΪ' 'ֵ���ۻ��ɽ���) 
    LONGLONG llAmountSum;    ///< �Զ����̳ɽ���   ÿ���Զ����̳ɽ���*�ɽ��� 

#ifdef _WIN32
    _STSendTradeInfo()
    {
        memset(this, 0, sizeof(STSendTradeInfo));
    }
#endif
}STSendTradeInfo;

/// ��۳�ʼ����������ṹ. 
typedef struct _STSendBaseStockInfo
{
    char  szStockCode[16];            ///< ��Ʊ���� 
    char  szStockName[64];            ///< ��Ʊ���� 
    char  szStockShortName[64];       ///< ��Ʊ��� 
    float fPreClosePrice;             ///< �����̼� 
    char  cPreCloseType;              ///< ���������� 
    long  lLotSize;                   ///< ÿ�ֹ��� 
    char  cShortSellFlag;             ///< ���ձ�־ 'Y' 'N' 
    char  cSuspensionFlag;            ///< ͣ�Ʊ�־ 'Y' 'N' 
    char  cIntraDayShortsellingFlag;  ///< �������ձ�־ 'Y' 'N' 
    char  cListingStatus;             ///< ����״̬ 'L','D','P' 
    DWORD dwMarketCode;               ///< �г����� 
    char  cInstrumentType;            ///< 1:��BOND��,2:��BWRT��3:��EQTY�� 4:��TRST��5:��WRNT 
    WORD  wCurrencyUnit;              ///< ���ҵ�λ 
    char  szCurrencyCode[4];          ///< ���Ҵ��� 
    char  szSpreadTableCode[2];       ///< ��λ����� 
    char  szReserve[24];              ///< ���� 
#ifdef _WIN32
    _STSendBaseStockInfo() 
    {
        memset(this, 0, sizeof(STSendBaseStockInfo));
    }
#endif
}STSendBaseStockInfo;

/// ���SP�������������ṹ. 
typedef struct _STSendSPTableInfo
{
    WORD  wSPCode;                  ///< Spread Table Code 
    char  spreadTableCode[2];       ///< Spread Table Code    X(2) 
    float priceFrom;                ///< Price From            B(4) 
    WORD  numberOfItems;            ///< Number of Items        B(2) 
    /// �������ṹ.
    struct STItemTable
    {
        float priceTo;              ///< Price To            B(4) 
        float SpreadValue;          ///< Spread Value        B(2) 
    };                   ///< Item Table (max 52) 
    // ���numberOfItems��STItemTable.
}STSendSPTableInfo;

/// �Ϻ� Level1��ʼ��������ṹ. 
typedef struct _SH_Level1_Output
{
    char    szStockNo[6];   ///< ��Ʊ���� 
    char    szName[8];      ///< ��Ʊ���� 
    char    szDate[9];      ///< �ɽ����� 
    char    szTime[9];      ///< �ɽ�ʱ�� 
    float   fLasttrade;     ///< �ɽ��� 
    double  dVolume;        ///< �������� 
    double  dAmount;        ///< �ɽ��ܽ�� 
    float   fpTrans;        ///< �ɽ����� 
    float   fOpen;          ///< ���̼۸� 
    float   fYClose;        ///< ���� 
    float   fBuyprice1;     ///< ���һ 
    float   fBuyprice2;     ///< ��۶� 
    float   fBuyprice3;     ///< ����� 
    float   fBuyprice4;     ///< ����� 
    float   fBuyprice5;     ///< ����� 
    float   fBuyvol1;       ///< ����һ 
    float   fBuyvol2;       ///< ������ 
    float   fBuyvol3;       ///< ������ 
    float   fBuyvol4;       ///< ������ 
    float   fBuyvol5;       ///< ������ 
    float   fSellprice1;    ///< ����һ 
    float   fSellprice2;    ///< ���۶� 
    float   fSellprice3;    ///< ������ 
    float   fSellprice4;    ///< ������ 
    float   fSellprice5;    ///< ������ 
    float   fSellvol1;      ///< ����һ 
    float   fSellvol2;      ///< ������ 
    float   fSellvol3;      ///< ������ 
    float   fSellvol4;      ///< ������ 
    float   fSellvol5;      ///< ������ 
    float   fLow;           ///< ������� 
    float   fHigh;          ///< ������� 
    float   fPE;            ///< ��ӯ��p/e (price/earning) ratio ,  
}SH_Level1_Output, SH_Level1_Output_Ex;
/// �Ϻ�L2���Ϻ�L1���õ���ǰ���ݽṹ. 
typedef struct _SH_L2_Reference_Output
{
    char    Symbol[10];                 ///< ֤ȯ���� 
    char    SecurityID[7];              ///< ֤ȯ���� 
    char    SecurityIDSource[5];        ///< ֤ȯ����Դ 
    char    szSecurityAltID[7];         ///< ��ѡ֤ȯ���� 
    char    szSecurityAltIDSource[4];   ///< ��ѡ֤ȯ����Դ 
    char    szCFICode[5];               ///< ֤ȯ��� 
    char    SecurityExchange[7];        ///< ���������� 
    char    SecuritySubType[5];         ///< ֤ȯ����� 
    double  ContractMultiplier;         ///< ծȯ�ۺϳɻع���׼ȯ�ı���  3dec 
    char    SecurityDesc[20];           ///< ֤ȯ���� 
    double  PreClosePx;                 ///< �����̼� 
    char    RoundLot[5];                ///< ���׵�λ 
    DWORD   InterestAccrualDate;        ///< ��Ϣ�� (20050708) 
    double  price;                      ///< ���Ѓr 
    char    IndustryClassification[5];  ///< ��ҵ���� 
    char    Currency[5];                ///< ���� 
    double  ShareFaceValue;             ///< ÿ����ֵ 
    UINT64  OutstandingShares;          ///< �ܷ����� 
    UINT64  PublicFloatShareQuantity;   ///< ��ͨ���� 
    int     SecurityTradingStatus;      ///< ����״̬ 
    char    CorporateAction[5];         ///< ��Ȩ��Ϣ��־ 
    DWORD   MaturityDate;               ///< ����/������ 
    char    CouponRate[2];              ///< A = annually, H = half-yearly 
    DWORD   CouponPaymentDate;          ///< ��Ϣ�� 
    DWORD   LastInterestPaymentDate;    ///< ��һ�����۸�Ϣ�� 
    DWORD   NextInterestPaymentDate;    ///< ��һ�����۸�Ϣ�� 
    double  ConversionPrice;            ///< ��Ȩ/ת�ɼ۸� 
    char    Residualmaturity[13];       ///< ʣ��ʱ�� 
    double  AccruedInterestAmt;         ///< Ӧ����Ϣ 
    char    BondType[2];                ///< ծȯ���� 
    char    American_European[2];       ///< ��ʽ/ŷʽ 
    char    CallOrPut[2];               ///< Call/Put��־ 
    char    Underlying[7];              ///< ����֤ȯ,Ϊ����֤ȯ���� 
    char    Issuer[20];                 ///< ���л��� 
    double  CVRatio;                    ///< ��Ȩ����   4dec 
    double  _CouponRate;                ///< Ʊ������   6dec 
    DWORD   ConversionPeriod;           ///< ��Ȩʱ�� 
    double  InterestRate;               ///< ��������  6dec 
    char    szStateID[8];               ///< ͣ�Ʊ�־ 
    float   fUpperLmtPrc;               ///< ��ͣ�� 
    float   fLowerLmtPrc;               ///< ��ͣ�� 
}SH_L2_Reference_Output;

/// ���� Level1��ʼ����Ϣ����ṹ. 
typedef struct  _SZ_Init_Output
{
    char   chDate[9];   ///< �ɽ����� 
    char   chTime[9];   ///< �ɽ�ʱ�� 
    char   XXZQDM[6];   ///< 1֤ȯ���� 
    char   XXZQJC[8];   ///< 2֤ȯ��� 
    char   XXJCQZ[4];   ///< 3֤ȯ���ǰ׺ 
    char   XXYWJC[20];  ///< 4Ӣ�ļ�� 
    char   XXJCZQ[6];   ///< 5����֤ȯ 
    char   XXISIN[12];  ///< 6ISIN ���� 
    char   XXHYZL[3];   ///< 7��ҵ���� 
    char   XXHBZL[2];   ///< 8�������� 
    float  XXMGMZ;      ///< 9ÿ����ֵ 
    double XXZFXL;      ///< 10�ܷ����� 
    double XXLTGS;      ///< 11��ͨ���� 
    double XXSNLR;      ///< 12����ÿ������ 
    double XXBNLR;      ///< 13����ÿ������ 
    double XXLJJZ;      ///< 14����ݶ��ۼƾ�ֵ 
    float  XXJSFL;      ///< 15���ַ��� 
    float  XXYHSL;      ///< 16ӡ��˰�� 
    float  XXGHFL;      ///< 17�������� 
    char   XXSSRQ[8];   ///< 18�������� 
    char   XXQXRQ[8];   ///< 19ծȯ��Ϣ�� 
    char   XXDJRQ[8];   ///< 20����/������ 
    float  XXJYDW;      ///< 21���׵�λ 
    float  XXBLDW;      ///< 22��������λ 
    float  XXSLDW;      ///< 23��������λ 
    double XXMBXL;      ///< 24ÿ��ί������ 
    float  XXJGDW;      ///< 25�۸�λ 
    float  XXJHCS;      ///< 26���Ͼ����޼۲��� 
    float  XXLXCS;      ///< 27���������޼۲��� 
    float  XXXJXZ;      ///< 28�޼۲������� 
    double XXZTJG;      ///< 29��ͣ�۸� 
    double XXDTJG;      ///< 30��ͣ�۸� 
    double XXJGSX;      ///< 31���ڽ��׼۸�����2 
    double XXJGXX;      ///< 32���ڽ��׼۸�����2 
    float  XXZHBL;      ///< 33ծȯ�ۺϱ��� 
    float  XXDBZSL;     ///< 34������������ 
    char   XXRZBD;      ///< 35���ʱ�ı�־ 
    char   XXRQBD;      ///< 36��ȯ��ı�־ 
    char   XXCFBZ;      ///< 37�ɷݹɱ�־ 
    char   XXZSBZ;      ///< 38�����̱�־ 
    char   XXSCDM[2];   ///< 39�����г����� 
    char   XXZQLB[4];   ///< 40֤ȯ��� 
    char   XXZQJB;      ///< 41֤ȯ���� 
    char   XXZQZT;      ///< 42֤ȯ״̬ 
    char   XXJYLX;      ///< 43�������� 
    char   XXJYJD;      ///< 44��Ʒ���׽׶� 
    char   XXTPBZ;      ///< 45��ͣ���ױ�־ 
    char   XXRZZT;      ///< 46���ʽ���״̬ 
    char   XXRQZT;      ///< 47��ȯ����״̬ 
    char   XXRQJX;      ///< 48��ȯ�����۸����� 
    char   XXWLTP;      ///< 49����ͶƱ��־ 
    char   XXYWZT[8];   ///< 50����ҵ��״̬ 
    char   XXGXSJ[6];   ///< 51��¼����ʱ�� 
    char   XXMARK[12];  ///< 52�����ֶ� 
    char   XXBYBZ;      ///< 53���ñ�־ 
}SZ_Init_Output;

/// ���� Level1��ʼ��������ṹ. 
typedef struct _SZ_Level1_Output
{
    char    szStockNo[6];   ///< ��Ʊ���� 
    char    szName[8];      ///< ��Ʊ���� 
    char    szDate[9];      ///< �ɽ����� 
    char    szTime[9];      ///< �ɽ�ʱ�� 
    float   fLasttrade;     ///< �ɽ��� 
    double  dVolume;        ///< �������� 
    double  dAmount;        ///< �ɽ��ܽ�� 
    float   fpTrans;        ///< �ɽ����� 
    float   fOpen;          ///< ���̼۸� 
    float   fYClose;        ///< ���� 
    float   fBuyprice1;     ///< ���һ 
    float   fBuyprice2;     ///< ��۶� 
    float   fBuyprice3;     ///< ����� 
    float   fBuyprice4;     ///< ����� 
    float   fBuyprice5;     ///< ����� 
    float   fBuyvol1;       ///< ����һ 
    float   fBuyvol2;       ///< ������ 
    float   fBuyvol3;       ///< ������ 
    float   fBuyvol4;       ///< ������ 
    float   fBuyvol5;       ///< ������ 
    float   fSellprice1;    ///< ����һ 
    float   fSellprice2;    ///< ���۶� 
    float   fSellprice3;    ///< ������ 
    float   fSellprice4;    ///< ������ 
    float   fSellprice5;    ///< ������ 
    float   fSellvol1;      ///< ����һ 
    float   fSellvol2;      ///< ������ 
    float   fSellvol3;      ///< ������ 
    float   fSellvol4;      ///< ������ 
    float   fSellvol5;      ///< ������ 
    float   fLow;           ///< ������� 
    float   fHigh;          ///< ������� 
    float   fPE;            ///< ��ӯ��p/e (price/earning) ratio ,  
    float   PE1;            ///< ��ӯ��1(HQSYL1) 
    double  HQJSD1;         ///< �۸�����1 
    double  HQJSD2;         ///< �۸�����2 
    double  HQHYCC;         ///< ��Լ�ֲ��� 
}SZ_Level1_Output;

/// ���ʵʱ�������. 
typedef struct _FOREX_Contract_Output
{
    char szExchangeID[4];         ///< ���ID 
    char cDataType;               ///< �������� 
    char cDataGategory;           ///< �������ࣨ��̬�����У��̺� 
    char cDataMode;               ///< ����ģʽ 
    char szRemarkData[5];         ///< ��ע 
    char szSymbolCode[7];         ///< ���� 
    char szTermType[2];           ///< �������� 
    char szKoreaTradingDate[8];   ///< ������������ 
    char szKoreaTradingTime[6];   ///< ��������ʱ�� 
    char szTradingDate[8];        ///< �������� 
    char szTradingTime[6];        ///< ����ʱ�� 
    float fOpenPrice;             ///< ���̼� 
    float fHighPrice;             ///< ��߼� 
    float fLowPrice;              ///< ��ͼ� 
    float fClosePrice;            ///< ���̼� 
    float fChangePrice;           ///< �һ���     
    float fChangeRate;            ///< �һ��� 
    float fBidPrice1;             ///< ���� 
    char szBidTime[6];            ///< ����ʱ�� 
    float fAskPrice1;             ///< �ʼ� 
    char szAskTime[6];            ///< �ʼ�ʱ�� 
    char szContributorCode[4];    ///< �ɽ�����  
}FOREX_Contract_Output;

/// �Ϻ�L2�����λ��Ϣ 
typedef struct  _PriceLevel
{
    double size;      ///< �� 
    float  px;        ///< �� 
    int    numOrders; ///< ʵ�ʵ���ί�б��� 
}PriceLevel;

/// UA3202 �Ϻ�L2�г�����
typedef struct _SH_L2_MarketData
{
    char    MessageType[7];                      ///< ��Ϣ���� 
    int     DataTimeStamp;                       ///< ʱ�� HHMMSS
    int     DataStatus;                          ///< 
    char    SecurityID[7];                       ///< ֤ȯ���� 
    float   PreClosePx;                          ///< �����̼� 
    float   OpenPx;                              ///< ���̼� 
    float   HighPx;                              ///< ��߼� 
    float   LowPx;                               ///< ��ͼ� 
    float   LastPx;                              ///< �ּ� 
    float   ClosePx;                             ///< �������̼۸� 
    char    InstrumentStatus[8];                 ///< ��ǰƷ��״̬ 
    PriceLevel vecBidPriceLevel[10];             ///< vecBidPriceLevel 
    PriceLevel vecOfferPriceLevel[10];           ///< vecOfferPriceLevel 
    int         NumTrades;                       ///< �ɽ����� 
    double      TotalVolumeTrade;                ///< �ɽ����� 
    double      TotalValueTrade;                 ///< �ɽ��ܽ�� 
    double      TotalBidQty;                     ///< ί���������� 
    float       WeightedAvgBidPx;                ///< ��Ȩƽ��ί��۸�  
    float       AltWeightedAvgBidPx;             ///< ծȯ��Ȩƽ��ί��۸� 
    double      TotalOfferQty;                   ///< ί���������� 
    float       WeightedAvgOfferPx;              ///< ��Ȩƽ��ί���۸� 
    float       AltWeightedAvgOfferPx;           ///< ծȯ��Ȩƽ��ί���۸� 
    float       IOPV;                            ///< IOPV��ֵ��ֵ 
#ifndef OLD_DISTRISERVER
    int         ETFBuyNumber;                    //ETF�깺����------------new
    double      ETFBuyAmount;                    //ETF�깺����
    double      ETFBuyMoney;                     //ETF�깺���
    int         ETFSellNumber;                   //ETF��ر���
    double      ETFSellAmount;                   //ETF�������
    double      ETFSellMoney;                    //ETF��ؽ��   // new
#endif
    float       YieldToMaturity;                 ///< ���������� 
    double      TotalWarrantExecQty;             ///< Ȩִ֤�е������� 
    double      WarlowerPx;                      ///< Ȩ֤��ͣ�۸� 
    double      WarUpperPx;                      ///< Ȩ֤��ͣ�۸� 
#ifndef OLD_DISTRISERVER
    int         WithdrawBuyNumber;               //���볷������------------new
    double      WithdrawBuyAmount;               //���볷������
    double      WithdrawBuyMoney;                //���볷�����
    int         WithdrawSellNumber;              //���볷������
    double      WithdrawSellAmount;              //���볷������
    double      WithdrawSellMoney;               //���볷�����
    int         TotalBidNumber;                  //�����ܱ���
    int         TotalOfferNumber;                //�����ܱ���
    int         BidTradeMaxDuration;             //����ί�гɽ����ȴ�ʱ��
    int         OfferTradeMaxDuration;           //����ί�гɽ����ȴ�ʱ��
    int         NumBidOrders;                    //��ί�м�λ��
    int         NumOfferOrders;                  //����ί�м�λ��  //new
#endif
}SH_L2_MarketData;

/// ί�ж��У���UA3202����
typedef struct _SH_L2_OrderQueue
{
    char        MessageType[7];     ///< ��Ϣ���� 
    int         DataTimeStamp;      ///< ʱ�� 
    int         DataStatus;         ///< DataStatus 
    char        SecurityID[7];      ///< ֤ȯ���� 

    // ί�򶩵�����
    float       BidPrice;           ///< �۸� 
    int         BidNumOrders;       ///< ��ί�б��� 
    double      BidOrders[50];      ///< ί�ж��� 

    // ί����������
    float       OfferPrice;         ///< �۸� 
    int         OfferNumOrders;     ///< ��ί�б��� 
    double      OfferOrders[50];    ///< ί�ж��� 
}SH_L2_OrderQueue;

/// UA3107���⼯�Ͼ��� 
typedef struct _SH_L2_VirtualAuctionPrice
{
    char    MessageType[7];     ///< ��Ϣ���� 
    int     DataTimeStamp;      ///< ʱ�� 
    int     DataStatus;         ///< DataStatus 
    char    SecurityID[7];      ///< ֤ȯ���� 
    float   Price;              ///< ���⿪�̲ο��۸� 
    double  VirtualAuctionQty;  ///< ����ƥ���� 
    double  LeaveQty;           ///< ����δƥ���� 
    char    Side[2];            ///< �������� 
}SH_L2_VirtualAuctionPrice;

/// UA3113ָ������ 
typedef struct _SH_L2_Index
{
    char    MessageType[7];     ///< ��Ϣ���� 
    int     DataTimeStamp;      ///< ʱ�� 
    int     DataStatus;         ///< DataStatus 
    char    SecurityID[7];      ///< ֤ȯ���� 
    double  PreCloseIndex;      ///< ǰ����ָ�� 
    double  OpenIndex;          ///< ����ָ�� 
    double  Turnover;           ///< ���������Ӧָ���ĳɽ���� 
    double  HighIndex;          ///< ���ָ�� 
    double  LowIndex;           ///< ���ָ�� 
    double  LastIndex;          ///< ����ָ�� 
    int     TradeTime;          ///< �ɽ�ʱ�� 
    double  TotalVolumeTraded;  ///< �ɽ��� 
    double  CloseIndex;         ///< ��������ָ�� 
}SH_L2_Index;

/// UA3115�г����� 
typedef struct _SH_L2_NGTS_MarketOverview
{
    char MessageType[7]; ///< ��Ϣ���� 
    int  DataTimeStamp;  ///< ʱ�� 
    int  DataStatus;     ///< DataStatus 
    char SecurityID[7];  ///< ֤ȯ���� 
    int  OrigTime;       ///< ����ʱ�� 
    int  OrigDate;       ///< �������� 
}SH_L2_NGTS_MarketOverview;

/// UA3201��ʳɽ� 
typedef struct _SH_L2_NGTS_Transaction
{
    char    MessageType[7]; ///< ��Ϣ���� 
    int     DataStatus;     ///< DataStatus 
    int     TradeIndex;     ///< �ɽ���� 
    int     TradeChannel;   ///< �ɽ�ͨ�� 
    char    SecurityID[7];  ///< ֤ȯ���� 
    int     TradeTime;      ///< �ɽ�ʱ�䣨�ٷ�֮һ�룩 
    float   TradePrice;     ///< �ɽ��۸�(Ԫ) 
    float   TradeQty;       ///< �ɽ����� ��Ʊ���� Ȩ֤���� ծȯ���� 
    double  TradeMoney;     ///< �ɽ����(Ԫ) 
#ifndef OLD_DISTRISERVER
    INT64   TradeBuyNo;     /// �򷽶�����
    INT64   TradeSellNo;    /// ����������
    char    TradeBSFlag[6]; /// �����̱�־ new
#endif
}SH_L2_NGTS_Transaction;

//=============������Ȩ==========================
/// UA9502 �Ͻ���������Ȩ��̬����
typedef struct _SHIO_Static_Output
{
    //RFStreamID; // �ο��������� C5 �ο��������ͱ�ʶ����ȡֵ RF301��ʾ��Ȩ������Ϣ
    char        SecurityID[8];              ///< ��Ȩ��Լ�Ĳ�Ʒ���� C8 ��Լ��Ȩ��Ʒ���룬8λ�ַ�
    char        ContractID[19];             ///< ��Ȩ��Լ���� C19 
    char        SecuritySymbol[20];         ///< ��Ȩ��Լ��� C20
    char        UnderlyingSecurityID[6];    ///< ���֤ȯ���� C6
    char        UnderlyingSymbol[8];        ///< ����֤ȯ֤ȯ���� C8
    char        UnderlyingType[3];          ///< ���֤ȯ����C3 EBS �C ETF�� ASH �C A��
    char        OptionType;                 ///< ŷʽ��ʽ C1 ��Ϊŷʽ��Ȩ�����ֶ�Ϊ��E������Ϊ��ʽ��Ȩ�����ֶ�Ϊ��A��
    char        CallOrPut;                  ///< �Ϲ��Ϲ� C1 �Ϲ������ֶ�Ϊ��C������Ϊ�Ϲ������ֶ�Ϊ��P��
    __int64     ContractMultiplierUnit;     ///< ��Լ��λ N11  ������Ȩ��Ϣ������ĺ�Լ��λ, һ��������
    double      ExercisePrice;              ///< ��Ȩ��Ȩ�� N11(4) ������Ȩ��Ϣ���������Ȩ��Ȩ�ۣ��Ҷ��룬��ȷ����
    int         StartDate;                  ///< �׸������� C8 ��Ȩ�׸�������,YYYYMMDD
    int         EndDate;                    ///< ������� C8 ��Ȩ�������/��Ȩ�գ�YYYYMMDD
    int         ExerciseDate;               ///< ��Ȩ��Ȩ�� C8 ��Ȩ��Ȩ�գ�YYYYMMDD
    int         DeliveryDate;               ///< ��Ȩ������ C8 ��Ȩ�����գ�Ĭ��Ϊ��Ȩ�յ���һ�������գ�YYYYMMDD
    int         ExpireDate;                 ///< ��Ȩ������ C8 ��Ȩ�����գ�YYYYMMDD
    char        UpdateVersion;              ///< ��Լ�汾�� C1 ��Ȩ��Լ�İ汾�š��¹Һ�Լ�ǡ�1��
    __int64     TotalLongPosition;          ///< ��ǰ��Լδƽ���� N12 ��λ�� ���ţ�
    double      SecurityClosePx;            ///< ��Լǰ���̼� N11(4) �������̼ۣ�������Ȩ��Ϣ��Ϊ����������̼۸��������յ��ļ��У���д�ο��۸񣩣��Ҷ��룬��ȷ����
    double      SettlPrice;                 ///< ��Լǰ����� N11(4) ���ս���ۣ��Ҷ��룬��λ��Ԫ
    double      UnderlyingClosePx;          ///< ���֤ȯǰ���� N11(4) ��Ȩ���֤ȯ��Ȩ��Ϣ�������ǰ���̼۸��Ҷ��룬��λ��Ԫ
    char        PriceLimitType;             ///< �ǵ����������� C1 ��N����ʾ���׹���3.4.13�涨�����ǵ����������ͻ���Ȩ֤����취��22���涨 ��R����ʾ���׹���3.4.15��3.4.16�涨�����ǵ�����������
    double      DailyPriceUpLimit;          ///< �Ƿ����޼۸� N11(4) ������Ȩ��ͣ�۸񣬾�ȷ����
    double      DailyPriceDownLimit;        ///< �������޼۸� N11(4) ������Ȩ��ͣ�۸񣬾�ȷ����
    double      MarginUnit;                 ///< ��λ��֤�� N16(2) ���ճ���һ�ź�Լ����Ҫ�ı�֤����������ȷ����
    double      MarginRatioParam1;          ///< ��֤������������һ N6(2) ��֤������������λ��%
    double      MarginRatioParam2;          ///< ��֤�������������� N6(2) ��֤������������λ��%
    __int64     RoundLot;                   ///< ������ N12 һ�ֵ��ڼ��ź�Լ
    __int64     LmtOrdMinFloor;             ///< �����޼��걨���� N12 �����޼��걨���걨�������ޡ�
    __int64     LmtOrdMaxFloor;             ///< �����޼��걨���� N12 �����޼��걨���걨�������ޡ�
    __int64     MktOrdMinFloor;             ///< �����м��걨���� N12 �����м��걨���걨�������ޡ�
    __int64     MktOrdMaxFloor;             ///< �����м��걨���� N12 �����м��걨���걨�������ޡ�
    double      TickSize;                   ///< ��С���۵�λ N11(4) ��λԪ,��ȷ��0.1��
    char        SecurityStatususFlag[8];    ///< ��Ȩ��Լ״̬��Ϣ��ǩ C8 ���ֶ�Ϊ8λ�ַ���������ÿλ��ʾ�ض��ĺ��壬�޶�������ո�<br>
                                             /// ��1λ����0����ʾ�ɿ��֣���1����ʾ�����������֣��������ҿ��֣������뿪�֡�<br>
                                             /// ��2λ����0����ʾδ����ͣ�ƣ���1����ʾ����ͣ�ơ�<br>
                                             /// ��3λ����0����ʾδ�ٽ������գ���1����ʾ���뵽���ղ���10�������ա�<br>
                                             /// ��4λ����0����ʾ����δ����������1����ʾ���10���������ں�Լ������������<br>
                                             /// ��5λ����A����ʾ�����¹��Ƶĺ�Լ����E����ʾ�����ĺ�Լ����D����ʾ����ժ�Ƶĺ�Լ��
}SHIO_Static_Output;

/// �Ͻ���������Ȩ��λ��Ϣ
typedef struct 
{
    __int64     Size;   ///< ��
    double      Px;     ///< �ۣ�����4λС��
}PriceLevel_IO_Output;    

#define SHIO_LEVEL_1  5
#define SHIO_LEVEL_2  10

/// �Ͻ���������ȨL1����
typedef struct SHIO_Data_Output
{
    char                    SecurityID[8];                  ///< ��Լ����
    int                     DataTimeStamp;                  ///< ��������ʱ�� 143025��ʾ 14:30:25
    double                  PreSettlPrice;                  ///< �����ۣ�����4λС��
    double                  SettlPrice;                     ///< �����ۣ�����4λС��
    double                  OpenPx;                         ///< ���̼ۣ�����4λС��
    double                  HighPx;                         ///< ��߼ۣ�����4λС��
    double                  LowPx;                          ///< ��ͼۣ�����4λС��
    double                  LastPx;                         ///< �ּۣ�����4λС��
    double                  AuctionPrice;                   ///< �������жϲο��ۣ�����4λС��
    __int64                 AuctionQty;                     ///< �������жϼ��Ͼ�������ƥ����
    __int64                 Position;                       ///< �ֲ���
    int                     NoBidPriceLevel;                ///< ���̼�λ����
    PriceLevel_IO_Output    BidPriceLv[SHIO_LEVEL_1];       ///< ������
    int                     NoOfferPriceLevel;              ///< ���̼�λ����
    PriceLevel_IO_Output    OfferPriceLv[SHIO_LEVEL_1];     ///< ������
    __int64                 TotalVolumeTrade;               ///< �ɽ���
    double                  TotalValueTrade;                ///< �ɽ������2λ
    char                    TradingPhaseCode[8];            ///< ����״̬
    __int64                 PacketTime;                     ///< Step��ͷ��ʱ�䣬������ΪYYYYMMDD-HH:MM:SS,ת����ʱ��ΪYYYYMMDDHHMMSSMMM,��20140121100559111Ϊ2014-01-21 10:05:59.111
    double                  ClosePrice;                     ///< ���̼�

}SHIO_L1_Output;



//============�Ϻ��̶���������===================================
typedef struct _SH_L2_6301_Data
{
    char    MessageType[7];             ///< ��Ϣ����
    int     DataTimestamp;              ///< ���������ʱ��
    int     DataStatus;                 ///< 
    int     TradeIndex;                 ///< �ɽ����        
    int     TradeChannel;               ///< �ɽ�ͨ��
    char    SecurityID[7];              ///< ֤ȯ����
    char    Symbol[60];                 ///< ֤ȯ���
    int     TradeDate;                  ///< �ɽ�����
    int     TradeTime;                  ///< �ɽ�ʱ��
    float   TradeNetPrice;              ///< �ɽ�����
    float   AccruedInterestAmt;         ///< Ӧ����Ϣ
    float   TradeFullPrice;             ///< �ɽ�ȫ��
    float   YieldToMaturity;            ///< ����������
    INT64   TradeQty;                   ///< �ɽ�����
    INT64   TradeMoney;                 ///< �ɽ����
    char    TradeMethod[2];             ///< �ɽ���ʽ

}SH_L2_6301_Data;

typedef struct _STOrderQueue
{
    INT64   OrderNo;                    ///< �������
    int     AuctionTime;                ///< ����ʱ��
    char    Auctioneer[20];             ///< ���۷�
    INT64   OrderQty;                   ///< ����
    float   YieldToMaturity;            ///< ����������
}STOrderQueue;

typedef struct _SH_L2_6302_Data
{
    char            MessageType[7];     ///< ��Ϣ����
    int             DataTimeStamp;      ///< ���������ʱ��
    int             DataStatus;         ///< 
    char            SecurityID[7];      ///< ֤ȯ����
    char            Symbol[60];         ///< ֤ȯ���
    int             ImageStatus;        ///< ��������
    int             TradeTime;          ///< �ɽ�ʱ��
    float           PreClosePx;         ///< �����̼�
    float           PreWeightedAvgPx;   ///< ���ռ�Ȩƽ����
    float           OpenPx;             ///< ���̼�
    float           HighPx;             ///< ��߼�
    float           LowPx;              ///< ��ͼ�
    float           LastPx;             ///< �ּ�
    float           WeightedAvgPx;      ///< ���ռ�Ȩƽ����
    INT64           TotalNumTrades;     ///< �����ܳɽ�����
    INT64           TotalVolumeTrade;   ///< �ɽ�����
    INT64           TotalValueTrade;    ///< �ɽ��ܽ��
    float           PreCloseYield;      ///< ��������������
    float           PreWeightedAvgYield;///< ���ռ�Ȩƽ��������
    float           OpenYield;          ///< ���տ���������
    float           HighYield;          ///< �������������
    float           LowYield;           ///< �������������
    float           LastYield;          ///< ��������������
    float           WeightedAvgYield;   ///< ���ռ�Ȩƽ��������
    float           AccruedInterestAmt; ///< Ӧ����Ϣ
    PriceLevel      vecBidLevels[10];   ///< ʮ��������
    STOrderQueue    vecBidQueue[50];    ///< ��һ����
    PriceLevel      vecOfferLevels[10]; ///< ʮ��������
    STOrderQueue    vecOfferQueue[50];  ///< ��һ����
}SH_L2_6302_Data;

typedef struct _SH_L2_GdStatic
{
    char    SecurityID[7];              ///< ֤ȯ����
    char    Symbol[16];                 ///< ֤ȯ����        
    char    TradePro[3];                ///< ���ײ�Ʒ
    char    Property[2];                ///< ֤ȯ����
    char    Status[2];                  ///< ֤ȯ״̬
    char    PledgeCode[7];              ///< ��Ѻȯ����
    char    OpenTime[7];                ///< ����ʱ��
    char    CloseTime[7];               ///< ����ʱ��
    char    IssueStyle[2];              ///< ֤ȯ���з�ʽ
    INT64   Par;                        ///< ֤ȯ���
    INT64   Price;                      ///< ���м۸�
    char    InterestStyle[2];           ///< ��Ϣ����
    char    PayFre[2];                  ///< ��ϢƵ��
    INT64   FaceInterset;               ///< Ʊ������
    INT64   BaseInterest;               ///< ��������
    INT64   BaseMargin;                 ///< ��������
    int     DueTime;                    ///< ����
    int     IssueTotal;                 ///< ʵ�ʷ�������
    char    OpenDate[9];                ///< ���п�ʼ����
    char    CloseDate[9];               ///< ���н�������
    char    ListedDate[9];              ///< ��������
    char    DueDate[9];                 ///< ��������
    char    BondStyle[2];               ///< ��ծ����
    char    IssueMethod[2];             ///< ���з���
    char    SFKSC[2];                   ///< �Ƿ���г�
    char    NFZK[2];                    ///< �Ƿ�����
    INT64   ZZKED;                      ///< �����ն��
    INT64   JYSZKED;                    ///< ���������ն��
    INT64   ClosePrice;                 ///< �������̼�
    INT64   PreWeightedPrice;           ///< ���ռ�Ȩƽ����
}SH_L2_GdStatic;


//==============����L2============================
/// ���L2��λ��Ϣ
typedef struct _SZ_PriceLevel
{
    int     Size;
    float   Px;
}SZ_PriceLevel;


/// ����L2��������
typedef struct _SZ_L2_Snapshot
{
    int             DataTimeStamp;          ///< ʱ�� HHMMSSMMM
    char            SecurityID[7];          ///< ֤ȯ����
    float           PreClosePx;             ///< �����̼�
    float           OpenPx;                 ///< ���̼� 
    float           HighPx;                 ///< ��߼� 
    float           LowPx;                  ///< ��ͼ�
    float           LastPx;                 ///< �����
    double          TotalVolumeTrade;       ///< �ɽ�����
    double          TotalValueTrade;        ///< �ɽ��ܽ�� 
    UINT64          TotalLongPosition;      ///< ��Լ�ֲ���
    float           PERatio1;               ///< ��ӯ��1
    float           PERatio2;               ///< ��ӯ��2
    char            EndOfDayMaker[2];       ///< ���б�־    
    INT64           TotalOfferQty;          ///< ί����������
    double          WeightedAvgOfferPx;     ///< ��Ȩƽ�������۸�
    int             NumTrades;              ///< �ɽ�����
    SZ_PriceLevel   vecBidPriceLevel[10];   ///< 10��ί���λ
    UINT32          BidNumOrders;           ///<
    UINT32          BidNoOrders;            ///< ���λ��ʾί�б���
    UINT32          BidS01OrderQty[50];     ///< ��һ��ί����
    UINT64          TotalBidQty;            ///< ί����������
    double          WeightedAvgBidPx;       ///< ��Ȩƽ������۸� 
    SZ_PriceLevel   vecOfferPriceLevel[10]; ///< 10��ί����λ
    UINT32          OfferNumOrdes;          ///<
    UINT32          OfferNoOrders;          ///< ����λ��ʾί�б���
    UINT32          OfferS01OrderQty[50];   ///< ��һ��ί����
}SZ_L2_Snapshot;

/// Indexָ������
typedef struct _SZ_L2_Index
{
    int         DataTimeStamp;              ///< ʱ��
    char        SecurityID[7];              ///< ֤ȯ����
    double      PreCloseIndex;              ///< ǰ����ָ��
    double      OpenIndex;                  ///< ����ָ��
    double      Turnover;                   ///< ���������Ӧָ���ĳɽ����
    double      HighIndex;                  ///< ���ָ��
    double      LowIndex;                   ///< ���ָ��
    double      LastIndex;                  ///< ����ָ��
    INT64       NumTrades;                  ///< ���������Ӧָ���ĳɽ�����
    INT64       TotalVolumeTraded;          ///< ���������Ӧָ���Ľ�������
    char        EndOfDayMaker[2];           ///< ���б�־
}SZ_L2_Index;

/// Trade��ʳɽ�
typedef struct _SZ_L2_Trade
{
    UINT32      SetNo;                      ///< ֤ȯ������
    UINT32      RecNo;                      ///< �ɽ�����
    UINT32      BuyOrderRecNo;              ///< ��ί������
    UINT32      SellOrderRecNo;             ///< ����ί������
    char        SecurityID[7];              ///< ֤ȯ����
    float       Price;                      ///< �ɽ��۸�
    UINT32      TradeQty;                   ///< �ɽ�����
    char        FunctionCode[4];            ///< �ɽ�����
    char        OrderKind[4];               ///< �ɽ����
    int         TradeTime;                  ///< �ɽ�ʱ��
}SZ_L2_Trade;

/// ���ί��
typedef struct _SZ_L2_Order
{
    UINT32      SetNo;                      ///< ֤ȯ������
    UINT32      RecNo;                      ///< ί������
    char        SecurityID[7];              ///< ֤ȯ����
    float       Price;                      ///< ί�м۸�
    UINT32      OrderQty;                   ///< ί������
    char        OrderKind[4];               ///< ί�����
    char        FunctionCode[4];            ///< ί�д���
    int         OrderEntryTime;             ///< ί��ʱ��
}SZ_L2_Order;

/// StockInfo֤ȯ��Ϣ
typedef struct _SZ_L2_StockInfo
{    
    UINT32      RecNo;                      ///< ��¼����
    char        SecurityID[7];              ///< ֤ȯ����
    char        Symbol[20];                 ///< ֤ȯ����
    char        SecurityDesc[20];           ///< ֤ȯ����
    char        UnderlyingSecurityID[7];    ///< ����֤ȯ����
    char        SecurityIDSource[5];        ///< ֤ȯ����Դ
    //UINT32    NoSecurityAltID;            ///< ��ѡ֤ȯ����
    //char      SecurityAltID[7];           ///< ��ѡ֤ȯ����
    //char      SecurityAltIDSource[12];    ///< ��ѡ֤ȯ����ԴTODO:δ֪�ַ���С
    char        IndustryClassification[5];  ///< ��ҵ����
    char        Currency[5];                ///< ����
    float       ShareFaceValue;             ///< ÿ����ֵ
    UINT64      OutstandingShares;          ///< �ܷ�����
    UINT64      PublicFloatShareQuantity;   ///< ��ͨ����
    float       PreviousYearProfitPerShare; ///< ����ÿ������
    float       CurrentYearProfitPerShare;  ///< ����ÿ������
    UINT32      NAV;                        ///< ����T-1���ۼƾ�ֵ
    UINT32      NoMiscFees;                 ///< ������������
    UINT32      IssueDate;                  ///< ��������
    char        BondType[2];                ///< ծȯ����
    float       CouponRate;                 ///< Ʊ������
    float       ConversionPrice;            ///< ��Ȩ�۸�
    char        AorEType[2];                ///< ��ʽ/ŷʽ/��Ľ��ʽ
    char        CallOrPut[2];               ///< Call/Put��־
    char        WarrantClearingType[2];     ///< Ȩ֤���㷽ʽ
    UINT        CVRatio;                    ///< ��Ȩ����
    UINT        ConversionBeginDate;        ///< ��Ȩ��ʼ����
    UINT        ConversionEndDate;          ///< ��Ȩ��������
    UINT        InterestAccrualDate;        ///< ��Ϣ��
    UINT        MaturityDate;               ///< ���ڽ�����
    UINT        RoundLot;                   ///< ���׵�λ
    UINT        BidLotSize;                 ///< ��������λ
    UINT        AskLotSize;                 ///< ��������λ
    UINT        MaxFloor;                   ///< ÿ������
    char        TradeMethod[2];             ///< ���׷�ʽ
    float       PriceTickSize;              ///< �۸�λ
    char        PriceLimitType[7];          ///< �޼۲������� ��ȷ�������ֽ�
    float       AuctionPriceLimit;          ///< ���Ͼ����޼۲���
    float       ContinuousTradePriceLimit;  ///< ���������޼۲���
    float       DailyPriceUpLimit;          ///< �Ƿ��۸�
    float       DailyPriceDownLimit;        ///< �����۸�
    float       DailyPriceUpLimit2;         ///< �����ս�����߼���ļ۸�����
    float       DailyPriceDownLimit2;       ///< �����ս�����ͼ���ļ۸�����
    UINT        ContractMultiplier;         ///< ծȯ�ۺϻع���׼ȯ����
    float       GageRate;                   ///< ����Ʒ������
    char        CrdBuyUnderlying[2];        ///< ����������
    char        CrdSellUnderlying[2];       ///< ��ȯ�������
    UINT        NoIndicesParticipated;      ///< ����ָ������
    //char      ParticipatingindexID[7];    ///< ����ָ�� ��ȷ���ֽڸ���
    char        MarketMakerFlag[2];         ///< �����̱�־
    char        SecurityExchange[5];        ///< ����������
    char        CFICode[5];                 ///< ֤ȯ���
    char        SecuritySubType[5];         ///< ֤ȯ�����(A, B)
    char        SecurityProperties[2];      ///< ֤ȯ����
    UINT        SecurityTradingStatus;      ///< ����״̬
    char        CorporateAction[2];         ///< ��Ȩ��Ϣ��־
    char        TradingMechanism[2];        ///< ��Ʒ��������
    char        CrdPriceCheckType[2];       ///< ��ۼ�鷽ʽ
    char        NetVotingFlag[2];           ///< ����ͶƱ��־
    char        ShrstrurefmFlag[2];         ///< �ɸ�״̬��־
    char        OfferingFlag[2];            ///< �Ƿ���ҪԼ�չ��ڡ��Ƿ���ת���ڣ���תծ����������Ȩ�ڣ�Ȩ֤��
}SZ_L2_StockInfo;

/// ֤ȯ״̬
typedef struct _SZ_L2_StockStatus
{
    char        SecurityID[7];              ///< ֤ȯ����
    char        SecurityPreName[4];         ///< ֤ȯ���ǰ׺
    char        TradingPhaseCode[9];        ///< ֤ȯ����״̬
    char        CrdBuyStatus[2];            ///< ��ǰ�������뿪��״̬
    char        CrdSellStatus[2];           ///< ��ǰ��ȯ��������״̬
    char        SubScribeStatus[2];         ///< �Ƿ������깺
    char        RedemptionStatus[2];        ///< �Ƿ��������
    char        WarrantCreated[2];          ///< �����Ƿ��д��跢��
    char        WarrantDropped[2];          ///< �����Ƿ���ע������
}SZ_L2_StockStatus;


//=================================������Ʒlevel2==============================================================
/// ֱ���г�����������
typedef struct _DLL2_BestQuot
{
    char        szTradingDate[8];           ///< ��������
    char        szContractID[20];           ///< ��Լ��
    UINT        nTID;                       ///< ������
    char        szContractName[40];         ///< ��Լ����
    double      dLastPrice;                ///< ���¼�
    double      dHighPrice;                 ///< ��߼�
    double      dLowPrice;                  ///< ��ͼ�
    UINT        nTotalVolum;                ///< ���³ɽ���
    UINT        nPrevTotalVolume;           ///< �ɽ���
    double      dTurnover;                  ///< �ɽ���
    UINT        nPrevOpenInterest;          ///< ��ʼ�ֲ���
    UINT        nOpenInterest;              ///< �ֲ���
    INT         nInterestChg;               ///< �ֲ����仯
    double      dClearPrice;                ///< ������
    double      dListLowPrice;              ///< ��ʷ��ͼ�
    double      dListHighPrice;             ///< ��ʷ��߼�
    double      dUpperLimit;                ///< ��ͣ��
    double      dLowerLimit;                ///< ��ͣ��
    double      dLastClearPrice;            ///< ���ս����
    double      dLastClose;               ///< �������̼�
    double      dBidPrice;                  ///< �����
    UINT        nBidSize;                   ///< ������
    UINT        nBidImplyQty;               ///< �����Ƶ���
    double      dAskPrice;                  ///< �����
    UINT        nAskSize;                   ///< ������
    UINT        nAskImplyQty;               ///< �����Ƶ���
    double      dAveragePrice;              ///< ���վ���
    char        szTradingTime[12];          ///< ����ʱ��
    double      dOpenPrice;                 ///< ���̼�
    double      dClosePrice;               ///< ���̼�
}DLL2_BestQuot;    //size:264

/// ���ű���ί������������
#define DLL2_BEST_ORDER_LEVEL 10
typedef struct _DLL2_BestOrder
{
    double      dBestBuyOrderPrice;                     ///< ��۸�
    union{
        UINT    BestBuyOrderQty[DLL2_BEST_ORDER_LEVEL]; ///< ��ί����
        struct{
        UINT    nBestBuyOrderQtyOne;                    ///< ��ί����1
        UINT    nBestBuyOrderQtyTwo;                    ///< ��ί����2
        UINT    nBestBuyOrderQtyThree;                  ///< ��ί����3
        UINT    nBestBuyOrderQtyFour;                   ///< ��ί����4
        UINT    nBestBuyOrderQtyFive;                   ///< ��ί����5
        UINT    nBestBuyOrderQtySix;                    ///< ��ί����6
        UINT    nBestBuyOrderQtySeven;                  ///< ��ί����7
        UINT    nBestBuyOrderQtyEight;                  ///< ��ί����8
        UINT    nBestBuyOrderQtyNine;                   ///< ��ί����9
        UINT    nBestBuyOrderQtyTen;                    ///< ��ί����10
        };
    };
    double      dBestSellOrderPrice;                    ///< ���۸�
    union{
        UINT    BestSellOrderQty[DLL2_BEST_ORDER_LEVEL];///< ��ί����
        struct
        {
        UINT    nBestSellOrderQtyOne;                   ///< ��ί����1
        UINT    nBestSellOrderQtyTwo;                   ///< ��ί����2
        UINT    nBestSellOrderQtyThree;                 ///< ��ί����3
        UINT    nBestSellOrderQtyFour;                  ///< ��ί����4
        UINT    nBestSellOrderQtyFive;                  ///< ��ί����5
        UINT    nBestSellOrderQtySix;                   ///< ��ί����6
        UINT    nBestSellOrderQtySeven;                 ///< ��ί����7
        UINT    nBestSellOrderQtyEight;                 ///< ��ί����8
        UINT    nBestSellOrderQtyNine;                  ///< ��ί����9
        UINT    nBestSellOrderQtyTen;                   ///< ��ί����10
        };
    };
    char        szGenTime[12];                          ///< ����ʱ��
}DLL2_BestOrder;
/// ��Ȩ������
typedef struct _DLL2_OptPara
{
    char        TradeDate[8];               ///< ��������
    char        ContractID[20];             ///< ��Ȩ��Լ��
    double      Delta;                      ///< delta
    double      Gamma;                      ///< gama
    double      Rho;                        ///< rho
    double      Theta;                      ///< theta
    double      Vega;                       ///< vega
}DLL2_OptPara;
/// ���������
typedef struct _DLL2_MBLQuotPara
{
    double      OrderPrice;                 ///< �۸�
    UINT        OrderQty;                   ///< ί����
    UINT        ImplyQty;                   ///< �Ƶ���
    UINT        BsFlag;                     ///< ������־
    char        GenTime[12];                ///< ����ʱ��
}DLL2_MBLQuotPara;

/// ������L2�����������
#define DLL2_MBLQUOT_LEVEL 5
/// ������L2��Ȩ��������
#define DLL2_OPTPARA_LEVEL 10

/// �������
typedef struct _DLL2_MBLQuot_Output
{
    DLL2_BestQuot       BestQuot;                           ///< ֱ���г�����������
    DLL2_BestOrder      BestOrder;                          ///< ���ű���ί������������
    int                 MBLQuotBuyNum;                      ///< �������������
    DLL2_MBLQuotPara    MBLQuotBuy[DLL2_MBLQUOT_LEVEL];     ///< �����������
    int                 MBLQuotSellNum;                     ///< �������������
    DLL2_MBLQuotPara    MBLQuotSell[DLL2_MBLQUOT_LEVEL];    ///< �����������
}DLL2_MBLQuot_Output;

/// ��������������
typedef struct _DLL2_ArbiBestQuot
{
    char            szTradeDate[8];         ///< ��������
    char            szArbiContractID[80];   ///< ������Լ��
    UINT            nTID;                   ///< ������
    double          dLastPrice;             ///< ���¼�
    double          dLowPrice;              ///< ��ͼ�
    double          dHighPrice;             ///< ��߼�
    double          dListLowPrice;          ///< ��ʷ��ͼ�
    double          dListHighPrice;         ///< ��ʷ��߼�
    double          dUpperLimit;            ///< ��ͣ��
    double          dLowerLimit;            ///< ��ͣ��
    double          dBidPrice;              ///< �����
    UINT            nBidSize;               ///< ������
    double          dAskPrice;              ///< �����
    UINT            nAskSize;               ///< ������
    char            szGenTime[8];           ///< ����ʱ��
}DLL2_ArbiBestQuot;    //size:189

/// �����������
typedef struct _DLL2_ArbiMBLQuot_Output
{
    DLL2_ArbiBestQuot   ArbiBestQuot;                       ///< ��������������
    DLL2_BestOrder      BestOrder;                          ///< ���ű���ί����������
    int                 MBLQuotBuyNum;                      ///< �������������
    DLL2_MBLQuotPara    MBLQuotBuy[DLL2_MBLQUOT_LEVEL];     ///< �����������
    int                 MBLQuotSellNum;                     ///< �������������
    DLL2_MBLQuotPara    MBLQuotSell[DLL2_MBLQUOT_LEVEL];    ///< �����������
}DLL2_ArbiMBLQuot_Output;

/// ʵʱ���������
typedef struct _DLL2_RealTimePrice_Output 
{
    char        szContractID[80];       ///< ��Լ��
    double      dRealTimePrice;         ///< ʵʱ�����
}DLL2_RealTimePrice_Output;

/// ί��ͳ������
typedef struct _DLL2_OrderStatistic_Output
{
    char        szContractID[80];               ///< ��Լ��
    UINT        nTotalBuyOrderNum;              ///< ��ί������
    UINT        nTotalSellOrderNum;             ///< ��ί������
    double      dWeightedAverageBuyOrderPrice;  ///< ��Ȩƽ��ί��۸�
    double      dWeightedAverageSellOrderPrice; ///< ��Ȩƽ��ί���۸�
}DLL2_OrderStatistic_Output;

/// �ּ۳ɽ���
typedef struct _DLL2_PriceQty
{
    double      dPrice;                         ///< �۸�
    UINT        nPriceBOQty;                    ///< ������
    UINT        nPriceBEQty;                    ///< ��ƽ����
    UINT        nPriceSOQty;                    ///< ��������
    UINT        nPriceSEQty;                    ///< ��ƽ����
}DLL2_PriceQty;

#define DLL2_MARCH_PRICE_QTY_LEVEL 5
/// �ּ۳ɽ�������
typedef struct _DLL2_MarchPriceQty_Output
{
    char        szContractID[80];                               ///< ��Լ��
    union{
        DLL2_PriceQty   PriceQty[DLL2_MARCH_PRICE_QTY_LEVEL];   ///< ��ʷּ۳ɽ�����Ϣ
        struct
        {
            double      dPriceOne;                      ///< �۸�
            UINT        nPriceOneBOQty;                 ///< ������
            UINT        nPriceOneBEQty;                 ///< ��ƽ����
            UINT        nPriceOneSOQty;                 ///< ��������
            UINT        nPriceOneSEQty;                 ///< ��ƽ����
            double      dPriceTwo;                      ///< �۸�
            UINT        nPriceTwoBOQty;                 ///< ������
            UINT        nPriceTwoBEQty;                 ///< ��ƽ����
            UINT        nPriceTwoSOQty;                 ///< ��������
            UINT        nPriceTwoSEQty;                 ///< ��ƽ����
            double      dPriceThree;                    ///< �۸�
            UINT        nPriceThreeBOQty;               ///< ������
            UINT        nPriceThreeBEQty;               ///< ��ƽ����
            UINT        nPriceThreeSOQty;               ///< ��������
            UINT        nPriceThreeSEQty;               ///< ��ƽ����
            double      dPriceFour;                     ///< �۸�
            UINT        nPriceFourBOQty;                ///< ������
            UINT        nPriceFourBEQty;                ///< ��ƽ����
            UINT        nPriceFourSOQty;                ///< ��������
            UINT        nPriceFourSEQty;                ///< ��ƽ����
            double      dPriceFive;                     ///< �۸�
            UINT        nPriceFiveBOQty;                ///< ������
            UINT        nPriceFiveBEQty;                ///< ��ƽ����
            UINT        nPriceFiveSOQty;                ///< ��������
            UINT        nPriceFiveSEQty;                ///< ��ƽ����
        };
    };
}DLL2_MarchPriceQty_Output;

#pragma pack()
#endif

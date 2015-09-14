//////////////////////////////////////////////////////////////////////////////
/// @file       QTSDataType.h
/// @brief      QTS���ݸ�ʽ����
/// @copyright  Copyright (C), 2008-2014, GTA Information Tech. Co., Ltd.
/// @version    2.0
/// @date       2014.7.18
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_QTS_DATA_TYPE_H_
#define GTA_QTS_DATA_TYPE_H_

// ������궨��
#ifdef _WIN32
#define _CDECL         __cdecl
#ifdef GTA_QTS_API_EXPORTS
#define GTA_API_EXPORT __declspec(dllexport)
#else
#define GTA_API_EXPORT __declspec(dllimport)
#endif
#else
#define _CDECL
#define GTA_API_EXPORT
#ifndef __stdcall
#define __stdcall
#endif
#endif

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

/// ��Ϣ���Ͷ��壬ֵΪunsigned intֵ
enum MsgType
{
    Msg_Unknown                 = 0x00000000,       ///< �������Ϣ����
    Msg_SSEL1_Static            = 0x00101000,       ///< �Ͻ���L1��̬����
    Msg_SSEL1_Quotation         = 0x00101001,       ///< �Ͻ���L1ʵʱ����
    Msg_SSEL2_Static            = 0x00102000,       ///< �Ͻ���L2��̬���� 
    Msg_SSEL2_Quotation         = 0x00102001,       ///< �Ͻ���L2ʵʱ���� UA3202
    Msg_SSEL2_Transaction       = 0x00102002,       ///< �Ͻ���L2��ʳɽ� UA3201
    Msg_SSEL2_Index             = 0x00102003,       ///< �Ͻ���L2ָ������ UA3113
    Msg_SSEL2_Auction           = 0x00102004,       ///< �Ͻ���L2���⼯�Ͼ��� UA3107
    Msg_SSEL2_Overview          = 0x00102005,       ///< �Ͻ���L2�г����� UA3115
    Msg_SSEIOL1_Static          = 0x00103000,       ///< �Ͻ���������Ȩ��̬����
    Msg_SSEIOL1_Quotation       = 0x00103001,       ///< �Ͻ���������Ȩʵʱ���� UA9002
    Msg_SZSEL1_Static           = 0x00201000,       ///< ���L1��̬����
    Msg_SZSEL1_Quotation        = 0x00201001,       ///< ���L1ʵʱ����
    Msg_SZSEL2_Static           = 0x00202000,       ///< ���L2��̬���� UA101
    Msg_SZSEL2_Quotation        = 0x00202001,       ///< ���L2ʵʱ���� UA103
    Msg_SZSEL2_Transaction      = 0x00202002,       ///< ���L2��ʳɽ� UA202
    Msg_SZSEL2_Index            = 0x00202003,       ///< ���L2ָ������ UA104
    Msg_SZSEL2_Order            = 0x00202006,       ///< ���L2���ί�� UA201
    Msg_SZSEL2_Status           = 0x00202007,       ///< ���L2֤ȯ״̬ UA102
    Msg_CFFEXL2_Static          = 0x00302000,       ///< �н���L2��̬����
    Msg_CFFEXL2_Quotation       = 0x00302001,       ///< �н���L2ʵʱ����
    Msg_SHFEL1_Static           = 0x00401000,       ///< ��������̬����
    Msg_SHFEL1_Quotation        = 0x00401001,       ///< ������ʵʱ����
    Msg_CZCEL1_Static           = 0x00501000,       ///< ֣������̬����
    Msg_CZCEL1_Quotation        = 0x00501001,       ///< ֣����ʵʱ����
    Msg_DCEL1_Static            = 0x00601000,       ///< ������L1��̬����
    Msg_DCEL1_Quotation         = 0x00601001,       ///< ������L1�������
    Msg_DCEL1_ArbiQuotation     = 0x00601008,       ///< ������L1�����������
    Msg_DCEL2_Static            = 0x00602000,       ///< ������L2��̬����
    Msg_DCEL2_Quotation         = 0x00602001,       ///< ������L2�����������
    Msg_DCEL2_ArbiQuotation     = 0x00602008,       ///< ������L2���������������
    Msg_DCEL2_RealTimePrice     = 0x00602009,       ///< ������L2ʵʱ�����
    Msg_DCEL2_OrderStatistic    = 0x0060200A,       ///< ������L2ί��ͳ������
    Msg_DCEL2_MarchPriceQty     = 0x0060200B,       ///< ������L2�ּ۳ɽ�������
};
/// ���ݷ��࣬����г����ܺ�ķ���
enum DataCategory
{
    Category_Unknown            =   -1,             ///< ������Ϣ����
    Category_Static             = 0x00,             ///< ��̬����
    Category_Quotation          = 0x01,             ///< ʵʱ����
    Category_Transaction        = 0x02,             ///< ��ʳɽ�
    Category_Index              = 0x03,             ///< ָ������
    Category_Auction            = 0x04,             ///< ���⼯�Ͼ���
    Category_Overview           = 0x05,             ///< �г�����
    Category_Order              = 0x06,             ///< ���ί��
    Category_Status             = 0x07,             ///< ֤ȯ״̬
    Category_ArbiQuotation      = 0x08,             ///< �����������
    Category_RealTimePrice      = 0x09,             ///< ʵʱ�����
    Category_OrderStatistic     = 0x0A,             ///< ί��ͳ������
    Category_MarchPriceQty      = 0x0B,             ///< �ּ۳ɽ�������
};
/// �г����Ͷ���
enum MarketTag
{
    Market_Unknown         = 0,     ///< �����г�
    Market_SSE             = 1,     ///< �Ͻ���
    Market_SZSE            = 2,     ///< ���
    Market_CFFEX           = 3,     ///< �н���
    Market_SHFE            = 4,     ///< ������
    Market_CZCE            = 5,     ///< ֣����
    Market_DCE             = 6,     ///< ������
};
/// ����״̬����.
enum ConnectState
{
    Connecting                  = 0,    ///< ��������
    Connected                   = 1,    ///< ������
    ConnectClosing              = 2,    ///< ���ڹر�
    ConnectClosed               = 3,    ///< �ѹر�
};

/// ����ֵ�����б�
enum RetCode
{
    Ret_Error                   = -1,   ///< ʧ��
    Ret_Success                 = 0,    ///< �ɹ�
    Ret_NoAddress               = 1,    ///< �������������������ַ
    Ret_NoPermission            = 2,    ///< û��Ȩ�ޣ�����ϵ�ͷ�
    Ret_ParamInvalid            = 3,    ///< ������Ч
    Ret_AccountError            = 4,    ///< �ʺŻ��������
    Ret_AccountOutDate          = 5,    ///< �ʺŲ�����Ч����
    Ret_ConnectFail             = 6,    ///< ����ʧ��
    Ret_LoginRepeat             = 7,    ///< �ʺ��ظ���¼
    Ret_OutTime                 = 8,    ///< ��ʱ
    Ret_CloseConnect            = 9,    ///< ���ӶϿ�
};

/// �ֶ�ID����
enum FieldID
{
    FID_ERROR                   = 0,            ///< �����ֶζ��壬�ֶ��ѵ���β
    FID_AltSymbol1              = 1000,         ///< ��ѡ����. 
    FID_AltSymbol2              = 1001,         ///< ��ѡ����. 
    FID_AltSymbol3              = 1002,         ///< ��ѡ����. 
    FID_AltSymbolNo             = 1003,         ///< ��ѡ�������. 
    FID_AltSymbolSource1        = 1004,         ///< ��ѡ����Դ. 
    FID_AltSymbolSource2        = 1005,         ///< ��ѡ����Դ. 
    FID_AltSymbolSource3        = 1006,         ///< ��ѡ����Դ. 
    FID_AuctionOpenPrice        = 1007,         ///< ���⿪�̲ο���. 
    FID_AuctionPriceLimit       = 1008,         ///< ���Ͼ����޼۲���. 3 λС��
    FID_AuctionVolume           = 1009,         ///< ����ƥ����. 
    FID_BlockPriceDownLmt       = 1010,         ///< ���ǵ�ͣ���ڴε׼�. 3 λС��
    FID_BlockPriceUpLmt         = 1011,         ///< ���ǵ�ͣ���ڴζ���. 3 λС��
    FID_BondType                = 1012,         ///< ծȯ����. B = ��ҵծȯ��C = ��ծ��V = ��תծ
    FID_BondWtAvgBuyPrice       = 1013,         ///< ծȯ��Ȩƽ��ί���. ��Ԫ��
    FID_BondWtAvgSellPrice      = 1014,         ///< ծȯ��Ȩƽ��ί����. 
    FID_BuyLevelNo              = 1015,         ///< ���̼�λ��. "����L2ʵʱ���飺10�����飬����ʱ���գ��Ͻ���������Ȩʵʱ���飺�嵵:����5���յ�λ��0��䡣"
    FID_BuyLevelQueue           = 1016,         ///< ��1������. ��Ƶ���ݱ��棬�ȴ涩������,ֻ��һ���д����ݣ�50��������ʱ����
    FID_BuyOrderID              = 1017,         ///< ��ί������. �� 1 ��ʼ������0 ��ʾ�޶�Ӧί��
    FID_BuyOrderNo              = 1018,         ///< ��ί�м�λ��. 
    FID_BuyPrice01              = 1019,         ///< �����. 3 λС��
    FID_BuyPrice02              = 1020,         ///< �����. 3 λС��
    FID_BuyPrice03              = 1021,         ///< �����. 3 λС��
    FID_BuyPrice04              = 1022,         ///< �����. 3 λС��
    FID_BuyPrice05              = 1023,         ///< �����. 3 λС��
    FID_BuyPrice06              = 1024,         ///< �����. 3 λС��
    FID_BuyPrice07              = 1025,         ///< �����. 3 λС��
    FID_BuyPrice08              = 1026,         ///< �����. 3 λС��
    FID_BuyPrice09              = 1027,         ///< �����. 3 λС��
    FID_BuyPrice10              = 1028,         ///< �����. 3 λС��
    FID_BuyRecID                = 1029,         ///< �򷽶�����. 
    FID_BuySellFlag             = 1030,         ///< �����̱�־. B �C ����,������;S �C ����,������;N �C δ֪
    FID_BuyVolume01             = 1031,         ///< ������. 
    FID_BuyVolume02             = 1032,         ///< ������. 
    FID_BuyVolume03             = 1033,         ///< ������. 
    FID_BuyVolume04             = 1034,         ///< ������. 
    FID_BuyVolume05             = 1035,         ///< ������. 
    FID_BuyVolume06             = 1036,         ///< ������. 
    FID_BuyVolume07             = 1037,         ///< ������. 
    FID_BuyVolume08             = 1038,         ///< ������. 
    FID_BuyVolume09             = 1039,         ///< ������. 
    FID_BuyVolume10             = 1040,         ///< ������. 
    FID_BuyVolumeUnit           = 1041,         ///< ��������λ. �򶩵����걨���������Ǹ��ֶε���������
    FID_CallOrPut               = 1042,         ///< �Ϲ��Ϲ�. C = Call��P = Put
    FID_CFICode                 = 1043,         ///< ֤ȯ���. "�Ͻ�������E'��ʾ��Ʊ����EU����ʾ���𣻡�D����ʾծȯ����RWS����ʾȨ֤����FF����ʾ�ڻ���
                                                ///< �����CFICode��SecuritySubType�����ֶ�ȷ���˲�ͬ��֤ȯ���CFICode��ȡֵΪMRI��EU��ES��D��DC��"
    FID_OutstandingShare        = 1044,         ///< ��ͨ����. 
    FID_CloseFlag               = 1045,         ///< ���б�־. Y = ���У�N = ����
    FID_ClosePrice              = 1046,         ///< �����̼�. 
    FID_ContractID              = 1047,         ///< ��Լ���״��� . ��Լ���״���17λ��������˳���д��1����1����6λΪ���֣�ȡ���֤ȯ���룬�繤������601398��ȡ��601398����2����7λΪC(Call)����P(Put)���ֱ��ʾ�Ϲ���Ȩ�����Ϲ���Ȩ��3����8��9λ��ʾ������ݣ�4����10��11λ��ʾ�����·ݣ�5����12λ�ڳ���Ϊ��M������ʾ�·ݺ�Լ������Լ�״ε����󣬡�M���޸�Ϊ ��A�����Ա�ʾ�ú�Լ��������һ�Σ��緢���ڶ��ε�������A���޸�Ϊ��B������M���޸�Ϊ ��A�����Դ����ƣ�6����13��17λ��ʾ��Ȩ��Ȩ�۸�.����λ����
    FID_ContractMultiplier      = 1048,         ///< ծȯ�ۺϻع���׼ȯ����. 2 λС��
    FID_ContractMultiplierUnit  = 1049,         ///< ��Լ��λ . ������Ȩ��Ϣ������ĺ�Լ��λ, һ�������� 
    FID_ContTradePriceLmt       = 1050,         ///< ���������޼۲���. 3 λС��
    FID_ConversionBeginDate     = 1051,         ///< ��Ȩ��ʼ��. 
    FID_ConversionEndDate       = 1052,         ///< ��Ȩ������. 
    FID_ConversionPrice         = 1053,         ///< ��Ȩ�۸�. 3 λС��
    FID_ConversionRatio         = 1054,         ///< ��Ȩ����. 4 λС��
    FID_CouponRate              = 1055,         ///< Ʊ������. 6 λС��
    FID_CrdBuyStatus            = 1056,         ///< ��ǰ���ʿ���״̬. Y = ����,N = ��ͣ
    FID_CrdBuyUnderlying        = 1057,         ///< ���ʱ�ı�־. "�Ͻ�������T����ʾ�����ʱ��֤ȯ����F����ʾ�������ʱ��֤ȯ��
                                                ///< �����Y= �ǣ�N= ��"
    FID_CrdPriceCheckType       = 1058,         ///< ��ۼ�鷽ʽ. 
                                                ///< 0 = ����ȯ����ί�м۸����ƣ�
                                                ///< 1 = Ҫ����ȯ�����걨�۸񲻵�������ۣ�
                                                ///< 2 = Ҫ����ȯ�����걨�۸񲻵������ռ�
    FID_CrdSellStatus           = 1059,         ///< ��ǰ��ȯ����״̬. Y = ����,N = ��ͣ
    FID_CrdSellUnderlying       = 1060,         ///< ��ȯ��ı�־. "�Ͻ�������T����ʾ����ȯ���֤ȯ����F����ʾ������ȯ���֤ȯ��
                                                ///< �����Y= �ǣ�N= ��"
    FID_Currency                = 1061,         ///< ����. CNY = ����ң�HKD = �۱�
    FID_DeliveryDate            = 1062,         ///< ��Ȩ������. ��Ȩ�����գ�Ĭ��Ϊ��Ȩ�յ���һ�������գ�YYYYMMDD
    FID_EndDate                 = 1063,         ///< ������� . ��Ȩ�������/��Ȩ�գ�YYYYMMDD 
    FID_ETFBuyAmount            = 1064,         ///< ETF �깺���. 
    FID_ETFBuyNo                = 1065,         ///< ETF �깺����. 
    FID_ETFBuyVolume            = 1066,         ///< ETF �깺����. 
    FID_ETFSellAmount           = 1067,         ///< ETF ��ؽ��. 
    FID_ETFSellNo               = 1068,         ///< ETF ��ر���. 
    FID_ETFSellVolume           = 1069,         ///< ETF �������. 
    FID_ExerciseDate            = 1070,         ///< ��Ȩ��Ȩ�� . ��Ȩ��Ȩ�գ�YYYYMMDD 
    FID_ExercisePrice           = 1071,         ///< ��Ȩ��Ȩ�� . ������Ȩ��Ϣ���������Ȩ��Ȩ�ۣ��Ҷ��룬��ȷ����;��Ȩ�۸������ȡ�������뷽ʽ����Ʊ������λС����ETF������λС����
    FID_ExpireDate              = 1072,         ///< ��Ȩ������ . ��Ȩ�����գ�YYYYMMDD 
    FID_GageRate                = 1073,         ///< ����Ʒ������. 2 λС��
    FID_HighPrice               = 1074,         ///< ��߼�. 4λС��
    FID_IndustryType            = 1075,         ///< ��ҵ����. 
    FID_InterestAccrualDate     = 1076,         ///< ��Ϣ��. 
    FID_InterruptAuctionPrice   = 1077,         ///< �������жϲο���. 4 decimal places
    FID_InterruptAuctionVolume  = 1078,         ///< �������ж�����ƥ����. ���⼯�Ͼ��۹����У�����Ȩ�ڻ��ļ۸񲨶���̫������Ҫ�ж�һ��ʱ�䣬�жϽ����󣬼���ʹ����һ������Ϊ����ƥ����
    FID_IOPV                    = 1079,         ///< ETF ��ֵ��ֵ. 
    FID_ISINCode                = 1080,         ///< ISIN����. 
    FID_IssueDate               = 1081,         ///< ��������. 
    FID_IssuedVolume            = 1082,         ///< �ܷ�����. 
    FID_LastPrice               = 1083,         ///< �ּ�. 4λС��
    FID_LeaveVolume             = 1084,         ///< ����δƥ����. 
    FID_ListingDate             = 1085,         ///< ��������. ���Ͻ������ս������ڣ�YYYYMMDD
    FID_LmtOrdCeiling           = 1086,         ///< �޼��걨���� . �����޼��걨���걨�������ޡ� 
    FID_LmtOrdFloor             = 1087,         ///< �޼��걨���� . �����޼��걨���걨�������ޡ� 
    FID_LowPrice                = 1088,         ///< ��ͼ�. 4λС��
    FID_MarginRatioParam1       = 1089,         ///< ��֤��������һ . ��֤������������λ��% 
    FID_MarginRatioParam2       = 1090,         ///< ��֤���������� . ��֤������������λ��% 
    FID_MarginUnit              = 1091,         ///< ��λ��֤�� . ���ճ���һ�ź�Լ����Ҫ�ı�֤���� ������ȷ���� 
    FID_MarketMakerFlag         = 1095,         ///< �����̱�־. Y = �������̣�N = ��������
    FID_MarketTime              = 1099,         ///< �г�ʱ��. �ٷ�֮һ��
    FID_MarketType              = 1100,         ///< �г�����. ��ASHR����ʾA���г�����BSHR����ʾB���г�����CSHR����ʾ���ʰ��г���
    FID_MaturityDate            = 1101,         ///< ���ڽ�����. 
    FID_MaxBuyDuration          = 1102,         ///< ����ɽ����ȴ�ʱ��. 
    FID_DeclareVolumeCeiling    = 1103,         ///< �걨������. �걨��������
    FID_MaxSellDuration         = 1104,         ///< �����ɽ����ȴ�ʱ��. 
    FID_MessageID               = 1105,         ///< ��Ϣ���. 
    FID_DeclareVolumeFloor      = 1106,         ///< �걨������. �걨��������
    FID_MktOrdCeiling           = 1111,         ///< �м��걨���� . �����м��걨���걨�������ޡ� 
    FID_MktOrdFloor             = 1112,         ///< �м��걨���� . �����м��걨���걨�������ޡ� 
    FID_NameUnderlying          = 1113,         ///< ����֤ȯ���� . 
    FID_NAV                     = 1114,         ///< ����T-1���ۼƾ�ֵ. 4 λС��
    FID_NetVotingFlag           = 1115,         ///< ����ͶƱ��־. Y = �������������ͶƱ��N = �������������ͶƱ
    FID_NonTradableNo           = 1116,         ///< ����ͨ����. Ԥ��
    FID_OfferingFlag            = 1117,         ///< �չ���ת�ɡ���Ȩ����־. Y= �ǣ�N= ��
    FID_OpenPrice               = 1118,         ///< ���̼�. 4λС��
    FID_OptionType              = 1119,         ///< ��Ȩ����. A= ��ʽ��E = ŷʽ��B = ��Ľ��ʽ
    FID_LocalTimeStamp          = 1120,         ///< �ɼ�ʱ��. ��̩���ڲ��ӵĲɼ�ʱ�䣬���ڲ���ʱ����ȷ������
    FID_OrderCode               = 1121,         ///< ί�д���. 
    FID_OrderPrice              = 1122,         ///< ί�м۸�. 3λС��
    FID_OrderType               = 1123,         ///< ί�����. 
    FID_OrderVolume             = 1124,         ///< ί������. 
    FID_PacketTimeStamp         = 1125,         ///< ��ͷʱ��. ��̩���ڲ��ӵİ�ͷʱ�䣬���ڲ���ʱ����ȷ������
    FID_ParValue                = 1128,         ///< ÿ����ֵ. 3 λС��
    FID_PERatio1                = 1129,         ///< ��ӯ�� 1. 2 λС������Ʊ���۸�/����ÿ������ծȯ��ÿ��ԪӦ����Ϣ
    FID_PERatio2                = 1130,         ///< ��ӯ�� 2. 2 λС����Ʊ���۸�/����ÿ������ծȯ�����������ʻ���ÿ�ٷݵ� IOPV ��ֵȨ֤�������
    FID_PreClosePrice           = 1131,         ///< ���ռ�. 3λС����ǰ���̼۸����г�Ȩ��Ϣ��Ϊ��Ȩ��Ϣ������̼ۣ������ڻ����г�����ʵʱ���꣬ȡֵΪ0.010
    FID_PreClosePriceUnderlying = 1132,         ///< ������ռ� . ��Ȩ���֤ȯ��Ȩ��Ϣ�������ǰ���̼۸��Ҷ��룬��λ��Ԫ 
    FID_PreSettlePrice          = 1133,         ///< �����. ���ս���ۣ��Ҷ��룬��λ��Ԫ ��4 decimal places
    FID_PreYearEPS              = 1134,         ///< ����ÿ������. 4 λС��
    FID_PriceDownLimit          = 1135,         ///< �����۸�. 3 λС��
    FID_TickSize                = 1136,         ///< ��С���۵�λ. "�걨�۸����С�䶯��λ
                                                ///< �Ͻ���������Ȩ����λԪ����ȷ��0.1��"
    FID_PriceLimitType          = 1137,         ///< �޼۲�������. 0��8517/8518 �ֶ�Ϊ�۸�
    FID_UpDownLimitType         = 1138,         ///< �ǵ�����������. ��N����ʾ���׹���3.4.13�涨�����ǵ����������ͻ���Ȩ֤����취��22���涨����R'��ʾ���׹���3.4.15��3.4.16�涨�����ǵ����������ͣ���S����ʾ�ع��ǵ����������͡�
    FID_PriceUpLimit            = 1139,         ///< �Ƿ��۸�. ����N�����ǵ������ƵĲ�Ʒ�����ֶε��ղ�����ģ�����ǰ���̼ۣ����������н��ײ�ƷΪ���мۣ����㣻����R�������ǵ������ƵĲ�Ʒ�����ֶ�ȡ����ʱ���ڲο��۸��������޼۸�3 λС��
    FID_RecID                   = 1140,         ///< ҵ������. �� 1 ��ʼ���� TradeChannel����
    FID_RedemptionStatus        = 1141,         ///< ��أ����ۣ���־. Y= ��,N= ��
    FID_RoundLot                = 1142,         ///< ������ . ���׵�λ��һ�ֵ��ڼ��ź�Լ��
    FID_SecurityEN              = 1143,         ///< Ӣ��֤ȯ����. 
    FID_SecurityExchange        = 1144,         ///< ����������. XSHE = ����֤ȯ�����������·�
    FID_SecurityName            = 1145,         ///< ֤ȯ����. 
    FID_SecurityNo              = 1146,         ///< ֤ȯ����. 
    FID_SecurityPhaseTag        = 1147,         ///< ����״̬.  ���ֶ�Ϊ4 λ�ַ���������ÿλ��ʾ�ض��ĺ��壬�޶�������ո񡣵�1 λ����S����ʾ����������ǰ��ʱ�Σ���C����ʾ���Ͼ���ʱ�Σ���T����ʾ��������ʱ�Σ���B����ʾ����ʱ�Σ���E����ʾ����ʱ�Σ���V����ʾ�������жϣ���P����ʾ��ʱͣ�ơ���2 λ����0����ʾδ����ͣ�ƣ���1����ʾ����ͣ�ơ�
    FID_SecurityStatus          = 1148,         ///< ��Ʒ״̬��ʶ. ��0λ��Ӧ����N����ʾ�������У���1λ��Ӧ����D����ʾ��Ȩ����2λ��Ӧ����R'��ʾ��Ϣ����3λ��Ӧ����D����ʾ���������������ײ�Ʒ����S����ʾ���վ�ʾ��Ʒ����P����ʾ���������Ʒ��
    FID_SecurityStatusFlag      = 1149,         ///< ��Ȩ��Լ״̬. ���ֶ�Ϊ8λ�ַ���������ÿλ��ʾ�ض��ĺ��壬�޶�������ո񡣵�1λ����0����ʾ�ɿ��֣���1����ʾ�����������֣��������ҿ��֣������뿪�֡���2λ����0����ʾδ����ͣ�ƣ���1����ʾ����ͣ�ơ���3λ����0����ʾδ�ٽ������գ���1����ʾ���뵽���ղ���10�������ա���4λ����0����ʾ����δ����������1����ʾ���10���������ں�Լ��������������5λ����A����ʾ�����¹��Ƶĺ�Լ����E����ʾ�����ĺ�Լ����D����ʾ����ժ�Ƶĺ�Լ��
    FID_SecuritySubType         = 1150,         ///< ֤ȯ�����. "�Ͻ������Զ�����ϸ֤ȯ���
                                                ///< �����SecuritySubType��CFICodeȷ���˲�ͬ��֤ȯ���ȡֵ��ΧΪ��N/A����ֵ��������A��B,AR��BR��G��O��R��AN��AS��"
    FID_SecurityTag             = 1151,         ///< �ɽ�֤ȯ���ǰ׺. 4 λ�ַ���
    FID_SecurityTypeID          = 1152,         ///< ֤ȯ����. N = ������S = ST �ɣ�P = PT �ɣ�T = ����ת��֤ȯ��L = ���п����ͻ���LOF����O = ����ʾ��ֵ�Ŀ���ʽ����F = �ǽ����Ϳ���ʽ����E = ETF
    FID_SellLevelNo             = 1153,         ///< ���̼�λ��. "�Ͻ���������Ȩʵʱ���飺�嵵:����5���յ�λ��0��䣻
                                                ///< ���L2ʵʱ���顢�Ͻ���L2ʵʱ���飺10�����飬����ʱ����"
    FID_SellLevelQueue          = 1154,         ///< ��1������. ��Ƶ���ݱ��棬�ȴ涩������,ֻ��һ���д����ݣ�50��������ʱ����
    FID_SellOrderID             = 1155,         ///< ����ί������. �� 1 ��ʼ������0 ��ʾ�޶�Ӧί��
    FID_SellOrderNo             = 1156,         ///< ����ί�м�λ��. 
    FID_SellPrice01             = 1157,         ///< ������. 3 λС��
    FID_SellPrice02             = 1158,         ///< ������. 3 λС��
    FID_SellPrice03             = 1159,         ///< ������. 3 λС��
    FID_SellPrice04             = 1160,         ///< ������. 3 λС��
    FID_SellPrice05             = 1161,         ///< ������. 3 λС��
    FID_SellPrice06             = 1162,         ///< ������. 3 λС��
    FID_SellPrice07             = 1163,         ///< ������. 3 λС��
    FID_SellPrice08             = 1164,         ///< ������. 3 λС��
    FID_SellPrice09             = 1165,         ///< ������. 3 λС��
    FID_SellPrice10             = 1166,         ///< ������. 3 λС��
    FID_SellRecID               = 1167,         ///< ����������. 
    FID_SellVolume01            = 1168,         ///< ������. 
    FID_SellVolume02            = 1169,         ///< ������. 
    FID_SellVolume03            = 1170,         ///< ������. 
    FID_SellVolume04            = 1171,         ///< ������. 
    FID_SellVolume05            = 1172,         ///< ������. 
    FID_SellVolume06            = 1173,         ///< ������. 
    FID_SellVolume07            = 1174,         ///< ������. 
    FID_SellVolume08            = 1175,         ///< ������. 
    FID_SellVolume09            = 1176,         ///< ������. 
    FID_SellVolume10            = 1177,         ///< ������. 
    FID_SellVolumeUnit          = 1178,         ///< ��������λ. ��������λ
    FID_SetID                   = 1179,         ///< ֤ȯ������. 
    FID_SetNo                   = 1180,         ///< ��Ʒ�����. ȡֵ��Χ��1��999,������������Ʒ��һ�ַ��鷽ʽ�������ڶ���������Ը��ؾ�����䡣��ֵ��һ���������ڲ���仯��
    FID_SettlePrice             = 1181,         ///< �����. 4 decimal places
    FID_ShrstrurefmFlag         = 1182,         ///< �ɸı�־. Y = �Ѿ���ɹɸģ�N = ��δ��ɹɸ�
    FID_Side                    = 1183,         ///< ��������. 0=��δƥ�������������ߵ�δƥ������Ϊ 0;1=����δƥ����������δƥ����=0;2=������δƥ��������δƥ����=0
    FID_StartDate               = 1184,         ///< �׸������� . ��Ȩ�׸�������,YYYYMMDD (��*10000+��*100+��)
    FID_StatusID                = 1185,         ///< ����״̬. 
                                                ///< 2 = ͣ�ƣ�Trading Halt����
                                                ///< 3 = �ָ���Resume����
                                                ///< 101 = �������У�
                                                ///< 102 = �����¹ɣ�
                                                ///< 103 = ����״̬��
                                                ///< 104 = �������۷��У�
                                                ///< 105 = �������۷��У�
                                                ///< 106 = ��ծ���Ʒ�����
                                                ///< 107 = ����ͣ��
    FID_SubScribeStatus         = 1186,         ///< �깺��תծ����Ȩ����־. Y= ��,N= ��
    FID_Symbol                  = 1187,         ///< ֤ȯ����. 
    FID_SymbolSource            = 1188,         ///< ֤ȯ����Դ. 4 = ISIN,102 = ����֤ȯ������
    FID_SymbolUnderlying        = 1189,         ///< ����֤ȯ����. 
    FID_TradeAmount             = 1190,         ///< �ɽ����. �ɽ����
    FID_Time                    = 1191,         ///< ��������ʱ��(����). 143025001 ��ʾ 14:30:25.001
    FID_TotalAmount             = 1192,         ///< �ɽ��ܶ�. Ԫ
    FID_TotalBuyNo              = 1193,         ///< �����ܱ���. 
    FID_TotalBuyOrderVolume     = 1195,         ///< ί����������. ��Ʊ����;Ȩ֤����;ծȯ����
    FID_TotalLongPosition       = 1196,         ///< ��Լδƽ���� . ��λ�� ���ţ� 
    FID_TotalNo                 = 1197,         ///< �ɽ�����. 
    FID_TotalPosition           = 1198,         ///< �ֲ���. 
    FID_TotalSellNo             = 1199,         ///< �����ܱ���. 
    FID_TotalSellOrderVolume    = 1201,         ///< ί����������. 
    FID_TotalVolume             = 1202,         ///< �ɽ�����. "�Ͻ���L2ʵʱ���飺��Ʊ����;Ȩ֤����;ծȯ���֣�
                                                ///< �Ͻ���������Ȩ��Trade volume of this security.�����Ȩ��Լ�Ĳ�Ʒ����Ϊ��00000000�������ʾ�������ڣ���ʽΪYYYYMMDD"
    FID_TotalWarrantExecVol     = 1203,         ///< Ȩִ֤������. 
    FID_TradableMarketNo        = 1204,         ///< ����ͨ����������. Ԥ��
    FID_TradableNo              = 1205,         ///< ����ͨδ��������. Ԥ��
    FID_TradeChannel            = 1206,         ///< �ɽ�ͨ��. 
    FID_TradeCode               = 1207,         ///< �ɽ�����. 
    FID_TradeDate               = 1208,         ///< �г�����. 
    FID_TradeMethod             = 1209,         ///< ���׷���. 1 = ���ǵ��ۣ�2 = ���ǵ�����3 = ���ǵ�ͣ
    FID_TradePrice              = 1210,         ///< �ɽ��۸�. 3 λС��
    FID_TradeStage              = 1211,         ///< ֤ȯ����״̬. 
                                                ///< 0 = ����ǰ,
                                                ///< 1 = ���̼��Ͼ���,
                                                ///< 2 = �������۽׶�,
                                                ///< 3 = ������ʱͣ��,
                                                ///< 4 = ���̼��Ͼ���,
                                                ///< 5 = ���о��۱���,
                                                ///< 6 = Э��ת�ý���,
                                                ///< 7 = ����
    FID_TradeStatus             = 1212,         ///< ��ǰƷ�ֽ���״̬. 
    FID_TradeTime               = 1213,         ///< �ɽ�ʱ��. 143025006 ��ʾ14:30:25.006
    FID_TradeType               = 1214,         ///< �ɽ����. 
    FID_TradeVolume             = 1215,         ///< �ɽ�����. ��Ʊ����;Ȩ֤����;ծȯ����
    FID_TradingMechanism        = 1216,         ///< ��Ʒ��������. G = ���о��۽��ף�N = ���о��۽���+Э�齻�ף�O = ��ȫЭ��ת�ã��ո� = ��������
    FID_UnderlyingType          = 1217,         ///< ���֤ȯ���� . EBS �C ETF�� ASH �C A�� 
    FID_Version                 = 1218,         ///< ��Լ�汾�� . ��Ȩ��Լ�İ汾�š��¹Һ�Լ�ǡ�1�� 
    FID_WarrantClearingType     = 1219,         ///< Ȩ֤���㷽ʽ. S = ֤ȯ���㣬C = �ֽ����
    FID_WarrantCreated          = 1220,         ///< ���跢����־. Y= ��,N= ��
    FID_WarrantDownLimit        = 1221,         ///< Ȩ֤��ͣ��. ��Ԫ��
    FID_WarrantDropped          = 1222,         ///< ע��������־. Y= ��,N= ��
    FID_WarrantUpLimit          = 1223,         ///< Ȩ֤��ͣ��. ��Ԫ��
    FID_WithdrawBuyAmount       = 1224,         ///< ���볷����. 
    FID_WithdrawBuyNo           = 1225,         ///< ���볷������. 
    FID_WithdrawBuyVolume       = 1226,         ///< ���볷����. 
    FID_WithdrawSellAmount      = 1227,         ///< ����������. 
    FID_WithdrawSellNo          = 1228,         ///< ������������. 
    FID_WithdrawSellVolume      = 1229,         ///< ����������. 
    FID_WtAvgBuyPrice           = 1230,         ///< ��Ȩƽ��ί���. 3 λС����Ԫ��
    FID_WtAvgSellPrice          = 1231,         ///< ��Ȩƽ��ί����. 3 λС����Ԫ��
    FID_XDAmount                = 1232,         ///< ��Ϣ���. ÿ�ɷֺ���
    FID_XRRatio                 = 1233,         ///< ��Ȩ����. ÿ���͹ɱ��������ڹ�ծԤ���в�Ʒ��Ϊ��֤�������
    FID_XRXDFlag                = 1234,         ///< ��Ȩ��Ϣ��־. A = ����Ϣ��B = �����䣬C = ��Ȩ��D = �¹ɣ�E = ����Ϣ��N = ����
    FID_YearEPS                 = 1235,         ///< ����ÿ������. 4 λС��
    FID_YTM                     = 1236,         ///< ծȯ����������. 
    FID_ParticipateIndexNo      = 1237,         ///< ����ָ������. 
    FID_ParticipateIndex01      = 1238,         ///< ����ָ��. ���·�
    FID_ParticipateIndex02      = 1239,         ///< ����ָ��. ���·�
    FID_ParticipateIndex03      = 1240,         ///< ����ָ��. ���·�
    FID_MiscFeeNo               = 1241,         ///< �ӷ������. 
    FID_MiscFeeAmount1          = 1242,         ///< �ӷѶ�. 6 λС��
    FID_MiscFeeType1            = 1243,         ///< �ӷ����. 4 = ���ַѣ�5 = ӡ��˰��13 = ������
    FID_MiscFeeUnit1            = 1244,         ///< �ӷѵ�λ. 
    FID_MiscFeeAmount2          = 1245,         ///< �ӷѶ�. 6 λС��
    FID_MiscFeeType2            = 1246,         ///< �ӷ����. 4 = ���ַѣ�5 = ӡ��˰��13 = ������
    FID_MiscFeeUnit2            = 1247,         ///< �ӷѵ�λ. 
    FID_MiscFeeAmount3          = 1248,         ///< �ӷѶ�. 6 λС��
    FID_MiscFeeType3            = 1249,         ///< �ӷ����. 4 = ���ַѣ�5 = ӡ��˰��13 = ������
    FID_MiscFeeUnit3            = 1250,         ///< �ӷѵ�λ. 
    FID_TotalBuyOrderNo01       = 1251,         ///< ��һ����ί�б���. ���L2������գ�Ϊ 0 ��ʾ����ʾ
    FID_TotalBuyOrderNo02       = 1252,         ///< �������ί�б���. ���L2������գ�Ϊ 0 ��ʾ����ʾ
    FID_TotalBuyOrderNo03       = 1253,         ///< ��������ί�б���. ���L2������գ�Ϊ 0 ��ʾ����ʾ
    FID_TotalBuyOrderNo04       = 1254,         ///< ���ĵ���ί�б���. ���L2������գ�Ϊ 0 ��ʾ����ʾ
    FID_TotalBuyOrderNo05       = 1255,         ///< ���嵵��ί�б���. ���L2������գ�Ϊ 0 ��ʾ����ʾ
    FID_TotalBuyOrderNo06       = 1256,         ///< ��������ί�б���. ���L2������գ�Ϊ 0 ��ʾ����ʾ
    FID_TotalBuyOrderNo07       = 1257,         ///< ���ߵ���ί�б���. ���L2������գ�Ϊ 0 ��ʾ����ʾ
    FID_TotalBuyOrderNo08       = 1258,         ///< ��˵���ί�б���. ���L2������գ�Ϊ 0 ��ʾ����ʾ
    FID_TotalBuyOrderNo09       = 1259,         ///< ��ŵ���ί�б���. ���L2������գ�Ϊ 0 ��ʾ����ʾ
    FID_TotalBuyOrderNo10       = 1260,         ///< ��ʮ����ί�б���. ���L2������գ�Ϊ 0 ��ʾ����ʾ
    FID_TotalSellOrderNo01      = 1261,         ///< ��һ����ί�б���. Ϊ 0 ��ʾ����ʾ
    FID_TotalSellOrderNo02      = 1262,         ///< ��������ί�б���. Ϊ 0 ��ʾ����ʾ
    FID_TotalSellOrderNo03      = 1263,         ///< ��������ί�б���. Ϊ 0 ��ʾ����ʾ
    FID_TotalSellOrderNo04      = 1264,         ///< ���ĵ���ί�б���. Ϊ 0 ��ʾ����ʾ
    FID_TotalSellOrderNo05      = 1265,         ///< ���嵵��ί�б���. Ϊ 0 ��ʾ����ʾ
    FID_TotalSellOrderNo06      = 1266,         ///< ��������ί�б���. Ϊ 0 ��ʾ����ʾ
    FID_TotalSellOrderNo07      = 1267,         ///< ���ߵ���ί�б���. Ϊ 0 ��ʾ����ʾ
    FID_TotalSellOrderNo08      = 1268,         ///< ���˵���ί�б���. Ϊ 0 ��ʾ����ʾ
    FID_TotalSellOrderNo09      = 1269,         ///< ���ŵ���ί�б���. Ϊ 0 ��ʾ����ʾ
    FID_TotalSellOrderNo10      = 1270,         ///< ��ʮ����ί�б���. Ϊ 0 ��ʾ����ʾ
    FID_SellLevelQueueNo01      = 1271,         ///< ��һ����ʾί�б���. Ϊ 0 ��ʾ����ʾ
    FID_BuyLevelQueueNo01       = 1272,         ///< ��һ����ʾί�б���. Ϊ 0 ��ʾ����ʾ
    FID_PreTotalPosition        = 1092,         ///< ��ֲ���
    FID_PreDelta                = 1093,         ///< ����ʵ��
    FID_Delta                   = 1094,         ///< ����ʵ��
    FID_SettleGroupID           = 1096,         ///< ���������
    FID_SettleID                = 1097          ///< ������
};

///��Ϣ�ṹ����ֶ�����
enum FIELD_TYPE{    
   Type_ERROR       = 0,           ///< δ֪����
   Type_Char        = 1,           ///< char
   Type_Short       = 2,           ///< short
   Type_Int         = 3,           ///< int
   Type_UInt        = 4,           ///< unsigned int
   Type_Longlong    = 5,           ///< long long 
   Type_ULonglong   = 6,           ///< unsigned long long 
   Type_String      = 7,           ///< string �ַ���
   Type_Double      = 8,           ///< double
   Type_Sequence    = 9,           ///< queue ����
};

/// ���ݽṹ�ֶγ��ȶ���
#define SYMBOL_LEN          20     ///< ���볤��
#define SECURITY_NAME_LEN   20     ///< ֤ȯ���Ƴ���
#define SECURITY_EN_LEN     24     ///< Ӣ��֤ȯ���
#define MARKET_TAG_LEN      10     ///< �г���־����
#define TIMEOUT_DEFAULT     3      ///< Ĭ�����ó�ʱʱ��

#endif // GTA_QTS_DATA_TYPE_H_

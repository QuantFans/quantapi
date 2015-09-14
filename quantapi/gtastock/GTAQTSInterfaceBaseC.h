//////////////////////////////////////////////////////////////////////////////
/// @file       GTAQTSInterfaceBaseC.h 
/// @brief      QTS����ӿ�C���Խӿڣ����ṹ�巵�����ݣ��Զ�����
/// @copyright  Copyright (C), 2008-2014, GTA Information Tech. Co., Ltd.
/// @version    2.0
/// @date       2014.7.18
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_QTS_INTERFACE_BASE_C_H_
#define GTA_QTS_INTERFACE_BASE_C_H_
#include "QTSDataType.h"
#include "QTSStruct.h"
#include "QTSDataFieldDefine.h"
extern "C"
{

/// ʵʱ���ݡ�����״̬�ص����������ṹ�巵������


/// ��½״̬����
/// @param  errCode  -- ʧ��ԭ��(�û����ڡ��ظ���½)�û�������������д���
typedef void (*OnBaseLoginState)( RetCode errCode);
void GTA_API_EXPORT _CDECL SetOnBaseLoginState(OnBaseLoginState cbOnBaseLoginState);

/// ����״̬���أ����ӳɹ�/ʧ��
/// @param  msgType      -- ��Ϣ����
/// @param  errCode     -- ʧ��ԭ�򣬳ɹ�ʱ����0
typedef void (*OnBaseConnectionState)(MsgType msgType, RetCode errCode);
void GTA_API_EXPORT _CDECL SetOnBaseConnectionState(OnBaseConnectionState cbOnBaseConnectionState);

/// �Ͻ���L1��̬���ݶ�������ʵʱ�ص��ӿ�
/// @param  pRealSSEL1Static     -- ʵʱ����
typedef void (*OnBaseSubscribe_SSEL1_Static)(const SSEL1_Static* pRealSSEL1Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEL1_Static(OnBaseSubscribe_SSEL1_Static cbOnBaseSubscribe_SSEL1_Static);

/// �Ͻ���L1ʵʱ���鶩������ʵʱ�ص��ӿ�
/// @param  pRealSSEL1Quotation  -- ʵʱ����
typedef void (*OnBaseSubscribe_SSEL1_Quotation)(const SSEL1_Quotation* pRealSSEL1Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEL1_Quotation(OnBaseSubscribe_SSEL1_Quotation cbOnBaseSubscribe_SSEL1_Quotation);

/// �Ͻ���L2��̬���ݶ�������ʵʱ�ص��ӿ�
/// @param  pRealSSEL2Static     -- ʵʱ����
typedef void (*OnBaseSubscribe_SSEL2_Static)(const SSEL2_Static* pRealSSEL2Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEL2_Static(OnBaseSubscribe_SSEL2_Static cbOnBaseSubscribe_SSEL2_Static);

/// �Ͻ���L2ʵʱ������ն�������ʵʱ�ص��ӿ�
/// @param  pRealSSEL2Quotation  -- ʵʱ����
typedef void (*OnBaseSubscribe_SSEL2_Quotation)(const SSEL2_Quotation* pRealSSEL2Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEL2_Quotation(OnBaseSubscribe_SSEL2_Quotation cbOnBaseSubscribe_SSEL2_Quotation);

/// �Ͻ���L2ָ�����鶩������ʵʱ�ص��ӿ�
/// @param  pRealSSEL2Index      -- ʵʱ����
typedef void (*OnBaseSubscribe_SSEL2_Index)(const SSEL2_Index* pRealSSEL2Index);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEL2_Index(OnBaseSubscribe_SSEL2_Index cbOnBaseSubscribe_SSEL2_Index);

/// �Ͻ���L2��ʳɽ���������ʵʱ�ص��ӿ�
/// @param  pRealSSEL2Transaction    -- ʵʱ����
typedef void (*OnBaseSubscribe_SSEL2_Transaction)(const SSEL2_Transaction* pRealSSEL2Transaction);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEL2_Transaction(OnBaseSubscribe_SSEL2_Transaction cbOnBaseSubscribe_SSEL2_Transaction);

/// �Ͻ���L2���⼯�Ͼ��۶�������ʵʱ�ص��ӿ�
/// @param  pRealSSEL2Auction    -- ʵʱ����
typedef void (*OnBaseSubscribe_SSEL2_Auction)(const SSEL2_Auction* pRealSSEL2Auction);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEL2_Auction(OnBaseSubscribe_SSEL2_Auction cbOnBaseSubscribe_SSEL2_Auction);

/// �Ͻ���L2�г�������������ʵʱ�ص��ӿ�
/// @param  pRealSSEL2Overview   -- ʵʱ����
typedef void (*OnBaseSubscribe_SSEL2_Overview)(const SSEL2_Overview* pRealSSEL2Overview);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEL2_Overview(OnBaseSubscribe_SSEL2_Overview cbOnBaseSubscribe_SSEL2_Overview);

/// �Ͻ���������Ȩ��̬���ݶ�������ʵʱ�ص��ӿ�
/// @param  pRealSSEIOL1Static   -- ʵʱ����
typedef void (*OnBaseSubscribe_SSEIOL1_Static)(const SSEIOL1_Static* pRealSSEIOL1Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEIOL1_Static(OnBaseSubscribe_SSEIOL1_Static cbOnBaseSubscribe_SSEIOL1_Static);

/// �Ͻ���������Ȩʵʱ���鶩������ʵʱ�ص��ӿ�
/// @param  pRealSSEIOL1Quotation    -- ʵʱ����
typedef void (*OnBaseSubscribe_SSEIOL1_Quotation)(const SSEIOL1_Quotation* pRealSSEIOL1Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SSEIOL1_Quotation(OnBaseSubscribe_SSEIOL1_Quotation cbOnBaseSubscribe_SSEIOL1_Quotation);

/// ���L1��̬���ݶ�������ʵʱ�ص��ӿ�
/// @param  pRealSZSEL1Static    -- ʵʱ����
typedef void (*OnBaseSubscribe_SZSEL1_Static)(const SZSEL1_Static* pRealSZSEL1Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SZSEL1_Static(OnBaseSubscribe_SZSEL1_Static cbOnBaseSubscribe_SZSEL1_Static);

/// ���L1ʵʱ���鶩������ʵʱ�ص��ӿ�
/// @param  pRealSZSEL1Quotation -- ʵʱ����
typedef void (*OnBaseSubscribe_SZSEL1_Quotation)(const SZSEL1_Quotation* pRealSZSEL1Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SZSEL1_Quotation(OnBaseSubscribe_SZSEL1_Quotation cbOnBaseSubscribe_SZSEL1_Quotation);

/// ���L2��̬���ݶ�������ʵʱ�ص��ӿ�
/// @param  pRealSZSEL2Static    -- ʵʱ����
typedef void (*OnBaseSubscribe_SZSEL2_Static)(const SZSEL2_Static* pRealSZSEL2Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SZSEL2_Static(OnBaseSubscribe_SZSEL2_Static cbOnBaseSubscribe_SZSEL2_Static);

/// ���L2ʵʱ���鶩������ʵʱ�ص��ӿ�
/// @param  pRealSZSEL2Quotation -- ʵʱ����
typedef void (*OnBaseSubscribe_SZSEL2_Quotation)(const SZSEL2_Quotation* pRealSZSEL2Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SZSEL2_Quotation(OnBaseSubscribe_SZSEL2_Quotation cbOnBaseSubscribe_SZSEL2_Quotation);

/// ���L2֤ȯ״̬��������ʵʱ�ص��ӿ�
/// @param  pRealSZSEL2Status    -- ʵʱ����
typedef void (*OnBaseSubscribe_SZSEL2_Status)(const SZSEL2_Status* pRealSZSEL2Status);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SZSEL2_Status(OnBaseSubscribe_SZSEL2_Status cbOnBaseSubscribe_SZSEL2_Status);

/// ���L2ָ�����鶩������ʵʱ�ص��ӿ�
/// @param  pRealSZSEL2Index     -- ʵʱ����
typedef void (*OnBaseSubscribe_SZSEL2_Index)(const SZSEL2_Index* pRealSZSEL2Index);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SZSEL2_Index(OnBaseSubscribe_SZSEL2_Index cbOnBaseSubscribe_SZSEL2_Index);

/// ���L2���ί�ж�������ʵʱ�ص��ӿ�
/// @param  pRealSZSEL2Order     -- ʵʱ����
typedef void (*OnBaseSubscribe_SZSEL2_Order)(const SZSEL2_Order* pRealSZSEL2Order);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SZSEL2_Order(OnBaseSubscribe_SZSEL2_Order cbOnBaseSubscribe_SZSEL2_Order);

/// ���L2��ʳɽ���������ʵʱ�ص��ӿ�
/// @param  pRealSZSEL2Transaction   -- ʵʱ����
typedef void (*OnBaseSubscribe_SZSEL2_Transaction)(const SZSEL2_Transaction* pRealSZSEL2Transaction);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SZSEL2_Transaction(OnBaseSubscribe_SZSEL2_Transaction cbOnBaseSubscribe_SZSEL2_Transaction);

/// �н�����̬���ݶ�������ʵʱ�ص��ӿ�
/// @param  pRealCFFEXL2Static   -- ʵʱ����
typedef void (*OnBaseSubscribe_CFFEXL2_Static)(const CFFEXL2_Static* pRealCFFEXL2Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_CFFEXL2_Static(OnBaseSubscribe_CFFEXL2_Static cbOnBaseSubscribe_CFFEXL2_Static);

/// �н���L2ʵʱ���鶩������ʵʱ�ص��ӿ�
/// @param  pRealCFFEXL2Quotation    -- ʵʱ����
typedef void (*OnBaseSubscribe_CFFEXL2_Quotation)(const CFFEXL2_Quotation* pRealCFFEXL2Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_CFFEXL2_Quotation(OnBaseSubscribe_CFFEXL2_Quotation cbOnBaseSubscribe_CFFEXL2_Quotation);

/// ֣������̬���ݶ�������ʵʱ�ص��ӿ�
/// @param  pRealCZCEL1Static    -- ʵʱ����
typedef void (*OnBaseSubscribe_CZCEL1_Static)(const CZCEL1_Static* pRealCZCEL1Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_CZCEL1_Static(OnBaseSubscribe_CZCEL1_Static cbOnBaseSubscribe_CZCEL1_Static);

/// ֣����ʵʱ���鶩������ʵʱ�ص��ӿ�
/// @param  pRealCZCEL1Quotation -- ʵʱ����
typedef void (*OnBaseSubscribe_CZCEL1_Quotation)(const CZCEL1_Quotation* pRealCZCEL1Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_CZCEL1_Quotation(OnBaseSubscribe_CZCEL1_Quotation cbOnBaseSubscribe_CZCEL1_Quotation);

/// ������L1��̬���ݶ�������ʵʱ�ص��ӿ�
/// @param  pRealDCEL1Static     -- ʵʱ����
typedef void (*OnBaseSubscribe_DCEL1_Static)(const DCEL1_Static* pRealDCEL1Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL1_Static(OnBaseSubscribe_DCEL1_Static cbOnBaseSubscribe_DCEL1_Static);

/// ������L1������鶩������ʵʱ�ص��ӿ�
/// @param  pRealDCEL1Quotation  -- ʵʱ����
typedef void (*OnBaseSubscribe_DCEL1_Quotation)(const DCEL1_Quotation* pRealDCEL1Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL1_Quotation(OnBaseSubscribe_DCEL1_Quotation cbOnBaseSubscribe_DCEL1_Quotation);

/// ������L1����������鶩������ʵʱ�ص��ӿ�
/// @param  pRealDCEL1ArbiQuotation  -- ʵʱ����
typedef void (*OnBaseSubscribe_DCEL1_ArbiQuotation)(const DCEL1_ArbiQuotation* pRealDCEL1ArbiQuotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL1_ArbiQuotation(OnBaseSubscribe_DCEL1_ArbiQuotation cbOnBaseSubscribe_DCEL1_ArbiQuotation);

/// ������L2��̬���ݶ�������ʵʱ�ص��ӿ�
/// @param  pRealDCEL2Static     -- ʵʱ����
typedef void (*OnBaseSubscribe_DCEL2_Static)(const DCEL2_Static* pRealDCEL2Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL2_Static(OnBaseSubscribe_DCEL2_Static cbOnBaseSubscribe_DCEL2_Static);

/// ������L2����������鶩������ʵʱ�ص��ӿ�
/// @param  pRealDCEL2Quotation  -- ʵʱ����
typedef void (*OnBaseSubscribe_DCEL2_Quotation)(const DCEL2_Quotation* pRealDCEL2Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL2_Quotation(OnBaseSubscribe_DCEL2_Quotation cbOnBaseSubscribe_DCEL2_Quotation);

/// ������L2��������������鶩������ʵʱ�ص��ӿ�
/// @param  pRealDCEL2ArbiQuotation  -- ʵʱ����
typedef void (*OnBaseSubscribe_DCEL2_ArbiQuotation)(const DCEL2_ArbiQuotation* pRealDCEL2ArbiQuotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL2_ArbiQuotation(OnBaseSubscribe_DCEL2_ArbiQuotation cbOnBaseSubscribe_DCEL2_ArbiQuotation);

/// ������L2ʵʱ����۶�������ʵʱ�ص��ӿ�
/// @param  pRealDCEL2RealTimePrice  -- ʵʱ����
typedef void (*OnBaseSubscribe_DCEL2_RealTimePrice)(const DCEL2_RealTimePrice* pRealDCEL2RealTimePrice);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL2_RealTimePrice(OnBaseSubscribe_DCEL2_RealTimePrice cbOnBaseSubscribe_DCEL2_RealTimePrice);

/// ������L2ί��ͳ�����鶩������ʵʱ�ص��ӿ�
/// @param  pRealDCEL2OrderStatistic -- ʵʱ����
typedef void (*OnBaseSubscribe_DCEL2_OrderStatistic)(const DCEL2_OrderStatistic* pRealDCEL2OrderStatistic);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL2_OrderStatistic(OnBaseSubscribe_DCEL2_OrderStatistic cbOnBaseSubscribe_DCEL2_OrderStatistic);

/// ������L2�ּ۳ɽ������鶩������ʵʱ�ص��ӿ�
/// @param  pRealDCEL2MarchPriceQty  -- ʵʱ����
typedef void (*OnBaseSubscribe_DCEL2_MarchPriceQty)(const DCEL2_MarchPriceQty* pRealDCEL2MarchPriceQty);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_DCEL2_MarchPriceQty(OnBaseSubscribe_DCEL2_MarchPriceQty cbOnBaseSubscribe_DCEL2_MarchPriceQty);

/// ��������̬���ݶ�������ʵʱ�ص��ӿ�
/// @param  pRealSHFEL1Static    -- ʵʱ����
typedef void (*OnBaseSubscribe_SHFEL1_Static)(const SHFEL1_Static* pRealSHFEL1Static);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SHFEL1_Static(OnBaseSubscribe_SHFEL1_Static cbOnBaseSubscribe_SHFEL1_Static);

/// ������ʵʱ���鶩������ʵʱ�ص��ӿ�
/// @param  pRealSHFEL1Quotation -- ʵʱ����
typedef void (*OnBaseSubscribe_SHFEL1_Quotation)(const SHFEL1_Quotation* pRealSHFEL1Quotation);
void GTA_API_EXPORT _CDECL SetOnBaseSubscribe_SHFEL1_Quotation(OnBaseSubscribe_SHFEL1_Quotation cbOnBaseSubscribe_SHFEL1_Quotation);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ����ϵͳ����ӿڣ����ӷ�����������֤���������ݣ���ѯ����.

/// ����API������ʼ��
void GTA_API_EXPORT _CDECL BaseInit();

/// ����API��������ʼ��
void GTA_API_EXPORT _CDECL BaseUninit();


/// ���ó�ʱʱ�䣬���ü�ʱ��Ч��ͬ�����õĳ�ʱʱ��
/// @param  nSenond     -- ��ʱʱ�䣬��λ��
void GTA_API_EXPORT _CDECL BaseSetTimeout(int nSecond = TIMEOUT_DEFAULT);

/// ע�������������ַ����ע������ͬ��ַ��ʵ�ָ߿��ã�����˳��Ϊ˳�����ӣ�����ʱ��������ǰʹ�õ�ַ
/// @param  pIP         -- ��������ַ.
/// @param  uPort       -- �������˿�.
/// @return RetCode     -- �������
RetCode GTA_API_EXPORT _CDECL BaseRegisterService(const char* pIP, unsigned short uPort);

/// ��������������������û���֤��Ϣ��ͬ�����󣬵���ǰ����
/// @param  pUserName   -- �˺�����
/// @param  pPassword   -- �˺����룬���ܺ�����
/// @return RetCode     -- �������
RetCode GTA_API_EXPORT _CDECL BaseLogin(const char* pUserName, const char* pPassword);

/// ��ȡ���鶩�ķ�������ַ��Ϣ
/// @param  ppServerAddrs               -- ��ŷ�������ַ���������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode      -- �������
RetCode GTA_API_EXPORT _CDECL BaseGetServerAddr(ServerState** ppServerAddrs, int* pSize);

/// ��ȡ��Ȩ�޵���������.
/// @param  ppDataTypeList  -- ��������ָ�룬���ݴ�С��Ϊ��Ȩ�޵����ݸ����������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize           -- �������ݸ���
/// @return RetCode         -- �������
RetCode GTA_API_EXPORT _CDECL BaseGetMsgTypeList(MsgType** ppDataTypeList, int* pSize);

/// �������飬�ظ�����ͬһ�����ݶ��ʱȡ����
/// @param  msgType     -- ��Ҫ���ĵ���������
/// @param  pCodeList   -- ���ɶ����б��ԡ�,���ָĩβ������\0������ΪNULLʱ����ȫ�г�
/// @return RetCode     -- �������
RetCode GTA_API_EXPORT _CDECL BaseSubscribe(MsgType msgType, char* pCodeList = NULL);

/// ȡ������
/// @param  msgType     -- ��Ҫȡ�����ĵ���������
/// @param  pCodeList   -- ȡ�������б��ԡ�,���ָĩβ������\0������ΪNULLʱȡ�����д���
/// @return RetCode     -- �������
RetCode GTA_API_EXPORT _CDECL BaseUnsubscribe(MsgType msgType, char* pCodeList = NULL);

/// ȡ�����ж�����Ϣ
/// @return RetCode     -- �������
RetCode GTA_API_EXPORT _CDECL BaseUnsubscribeAll();

/// ��ȡ��Ʊ�б�
/// @param  pMarketTag  -- �г���ʶ���ԡ�,���ָ����г���ʶ��ĩβ������\0������������ΪNULL
/// @param  ppStockList -- ���صĸ��ɴ����б����г���־�������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize       -- �������ݸ���
/// @return RetCode     -- �������
RetCode GTA_API_EXPORT _CDECL BaseGetStockList(char* pMarketTag, StockSymbol** ppStockList, int* pSize);

/// ��ѯ�Ͻ���L1��̬����
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSSEL1Static     -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize               -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEL1_Static(char* pCodeList, SSEL1_Static** ppSnapSSEL1Static, int* pSize);

/// ��ѯ�Ͻ���L1ʵʱ����
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSSEQuotation     -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEL1_Quotation(char* pCodeList, SSEL1_Quotation** ppSnapSSEQuotation, int* pSize);

/// ��ѯ�Ͻ���L2��̬����
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSSEStatic        -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEL2_Static(char* pCodeList, SSEL2_Static** ppSnapSSEL2Static, int* pSize);

/// ��ѯ�Ͻ���L2ʵʱ�������
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSSEL2Quotation    -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEL2_Quotation(char* pCodeList, SSEL2_Quotation** ppSnapSSEL2Quotation, int* pSize);

/// ��ѯ�Ͻ���L2ָ������
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSSEL2Index        -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEL2_Index(char* pCodeList, SSEL2_Index** ppSnapSSEL2Index, int* pSize);

/// ��ѯ�Ͻ���L2��ʳɽ�
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSSEL2Transation   -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEL2_Transaction(char* pCodeList, SSEL2_Transaction** ppSnapSSEL2Transation, int* pSize);

/// ��ѯ�Ͻ���L2���⼯�Ͼ���
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSSEL2Auction    -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEL2_Auction(char* pCodeList, SSEL2_Auction** ppSnapSSEL2Auction, int* pSize);

/// ��ѯ�Ͻ���L2�г�����
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSSEL2Overview   -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEL2_Overview(char* pCodeList, SSEL2_Overview** ppSnapSSEL2Overview, int* pSize);

/// ��ѯ�Ͻ���������Ȩ��̬����
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSSEIOL1Static   -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEIOL1_Static(char* pCodeList, SSEIOL1_Static** ppSnapSSEIOL1Static, int* pSize);

/// ��ѯ�Ͻ���������Ȩʵʱ����
/// @param  pCodeList               -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSSEIOL1Quotation    -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode                 -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SSEIOL1_Quotation(char* pCodeList, SSEIOL1_Quotation** ppSnapSSEIOL1Quotation, int* pSize);

/// ��ѯ���L1��̬����
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSZSEL1Static    -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SZSEL1_Static(char* pCodeList, SZSEL1_Static** ppSnapSZSEL1Static, int* pSize);

/// ��ѯ���L1ʵʱ����
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSZSEL1Quotation -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SZSEL1_Quotation(char* pCodeList, SZSEL1_Quotation** ppSnapSZSEL1Quotation, int* pSize);

/// ��ѯ���L2��̬����
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSZSEL2Static    -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SZSEL2_Static(char* pCodeList, SZSEL2_Static** ppSnapSZSEL2Static, int* pSize);

/// ��ѯ���L2ʵʱ����
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSZSEL2Quotation    -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SZSEL2_Quotation(char* pCodeList, SZSEL2_Quotation** ppSnapSZSEL2Quotation, int* pSize);

/// ��ѯ���L2֤ȯ״̬
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSZSEL2StockStatus  -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SZSEL2_Status(char* pCodeList, SZSEL2_Status** ppSnapSZSEL2StockStatus, int* pSize);

/// ��ѯ���L2ָ������
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSZSEL2Index        -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SZSEL2_Index(char* pCodeList, SZSEL2_Index** ppSnapSZSEL2Index, int* pSize);

/// ��ѯ���L2���ί��
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSZSEL2Order        -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SZSEL2_Order(char* pCodeList, SZSEL2_Order** ppSnapSZSEL2Order, int* pSize);

/// ��ѯ���L2��ʳɽ�
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSZSEL2Transaction  -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SZSEL2_Transaction(char* pCodeList, SZSEL2_Transaction** ppSnapSZSEL2Transaction, int* pSize);

/// ��ѯ�н�����̬����
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapCFFEXL2Static       -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_CFFEXL2_Static(char* pCodeList, CFFEXL2_Static** ppSnapCFFEXL2Static, int* pSize);

/// ��ѯ�н���L2ʵʱ����
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapCFFEXL2Quotation    -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_CFFEXL2_Quotation(char* pCodeList, CFFEXL2_Quotation** ppSnapCFFEXL2Quotation, int* pSize);


/// ��ѯ֣������̬����
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapCZCEL1Static    -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_CZCEL1_Static(char* pCodeList, CZCEL1_Static** ppSnapCZCEL1Static, int* pSize);

/// ��ѯ֣����ʵʱ����
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapCZCEL1Quotation -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_CZCEL1_Quotation(char* pCodeList, CZCEL1_Quotation** ppSnapCZCEL1Quotation, int* pSize);

/// ��ѯ������L1��̬����
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapDCEL1Static     -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL1_Static(char* pCodeList, DCEL1_Static** ppSnapDCEL1Static, int* pSize);

/// ��ѯ������L1�������
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapDCEL1Quotation  -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL1_Quotation(char* pCodeList, DCEL1_Quotation** ppSnapDCEL1Quotation, int* pSize);

/// ��ѯ������L1�����������
/// @param  pCodeList               -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapDCEL1ArbiQuotation  -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode                 -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL1_ArbiQuotation(char* pCodeList, DCEL1_ArbiQuotation** ppSnapDCEL1ArbiQuotation, int* pSize);

/// ��ѯ������L2��̬����
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapDCEL2Static     -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL2_Static(char* pCodeList, DCEL2_Static** ppSnapDCEL2Static, int* pSize);

/// ��ѯ������L2�����������
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapDCEL2Quotation  -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode              -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL2_Quotation(char* pCodeList, DCEL2_Quotation** ppSnapDCEL2Quotation, int* pSize);

/// ��ѯ������L2���������������
/// @param  pCodeList               -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapDCEL2ArbiQuotation  -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode                 -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL2_ArbiQuotation(char* pCodeList, DCEL2_ArbiQuotation** ppSnapDCEL2ArbiQuotation, int* pSize);

/// ��ѯ������L2ʵʱ�����
/// @param  pCodeList               -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapDCEL2RealTimePrice  -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode                 -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL2_RealTimePrice(char* pCodeList, DCEL2_RealTimePrice** ppSnapDCEL2RealTimePrice, int* pSize);

/// ��ѯ������L2ί��ͳ������
/// @param  pCodeList               -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapDCEL2OrderStatistic -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                       -- �������ݸ���
/// @return RetCode                 -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL2_OrderStatistic(char* pCodeList, DCEL2_OrderStatistic** ppSnapDCEL2OrderStatistic, int* pSize);

/// ��ѯ������L2�ּ۳ɽ�������
/// @param  pCodeList               -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapDCEL2MarchPriceQty  -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize                   -- �������ݸ���
/// @return RetCode                 -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_DCEL2_MarchPriceQty(char* pCodeList, DCEL2_MarchPriceQty** ppSnapDCEL2MarchPriceQty, int* pSize);

/// ��ѯ��������̬����
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSHFEL1Static    -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize               -- �������ݸ���
/// @return RetCode             -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SHFEL1_Static(char* pCodeList, SHFEL1_Static** ppSnapSHFEL1Static, int* pSize);

/// ��ѯ������ʵʱ����
/// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
/// @param  ppSnapSHFEL1Quotation -- ���������б������BaseReleaseValue�ͷ��ڴ�
/// @param  pSize               -- �������ݸ���
/// @return RetCode             -- �������
RetCode GTA_API_EXPORT _CDECL BaseQuerySnap_SHFEL1_Quotation(char* pCodeList, SHFEL1_Quotation** ppSnapSHFEL1Quotation, int* pSize);

/// �ͷŶ����ڴ�
/// @param  ppDataValue         -- ���ͷ��ڴ�
void GTA_API_EXPORT _CDECL BaseReleaseValue(void** ppDataValue);

};

#endif // GTA_QTS_INTERFACE_BASE_C_H_

//////////////////////////////////////////////////////////////////////////////
/// @file       GTAQTSInterfaceBase.h 
/// @brief      QTS����ӿڶ��壬���ṹ�巵�����ݣ��Զ�����
/// @copyright  Copyright (C), 2008-2014, GTA Information Tech. Co., Ltd.
/// @version    2.0
/// @date       2014.7.18
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_QTS_INTERFACE_BASE_H_
#define GTA_QTS_INTERFACE_BASE_H_
#include "QTSDataType.h"
#include "QTSStruct.h"
#include "QTSDataFieldDefine.h"

/// ʵʱ���ݡ�����״̬�ص��ӿڣ����ṹ�巵������
class GTA_API_EXPORT IGTAQTSCallbackBase
{
public:
    /// ��½״̬����
    /// @param  errCode  -- ʧ��ԭ��(�û����ڡ��ظ���½)�û�������������д���
    virtual void OnLoginState( RetCode errCode){}

    /// ����״̬���أ����ӳɹ�/ʧ��
    /// @param  msgType      -- ��Ϣ����
    /// @param  errCode     -- ʧ��ԭ�򣬳ɹ�ʱ����0
    virtual void OnConnectionState(MsgType msgType, RetCode errCode){}

    /// �Ͻ���L1��̬���ݶ�������ʵʱ�ص��ӿ�
    /// @param  RealSSEL1Static     -- ʵʱ����
    virtual void OnSubscribe_SSEL1_Static(const SSEL1_Static& RealSSEL1Static){}

    /// �Ͻ���L1ʵʱ���鶩������ʵʱ�ص��ӿ�
    /// @param  RealSSEL1Quotation  -- ʵʱ����
    virtual void OnSubscribe_SSEL1_Quotation(const SSEL1_Quotation& RealSSEL1Quotation){}

    /// �Ͻ���L2��̬���ݶ�������ʵʱ�ص��ӿ�
    /// @param  RealSSEL2Static     -- ʵʱ����
    virtual void OnSubscribe_SSEL2_Static(const SSEL2_Static& RealSSEL2Static){}

    /// �Ͻ���L2ʵʱ������ն�������ʵʱ�ص��ӿ�
    /// @param  RealSSEL2Quotation  -- ʵʱ����
    virtual void OnSubscribe_SSEL2_Quotation(const SSEL2_Quotation& RealSSEL2Quotation){}

    /// �Ͻ���L2ָ�����鶩������ʵʱ�ص��ӿ�
    /// @param  RealSSEL2Index      -- ʵʱ����
    virtual void OnSubscribe_SSEL2_Index(const SSEL2_Index& RealSSEL2Index){}

    /// �Ͻ���L2��ʳɽ���������ʵʱ�ص��ӿ�
    /// @param  RealSSEL2Transaction    -- ʵʱ����
    virtual void OnSubscribe_SSEL2_Transaction(const SSEL2_Transaction& RealSSEL2Transaction){}

    /// �Ͻ���L2���⼯�Ͼ��۶�������ʵʱ�ص��ӿ�
    /// @param  RealSSEL2Auction    -- ʵʱ����
    virtual void OnSubscribe_SSEL2_Auction(const SSEL2_Auction& RealSSEL2Auction){}

    /// �Ͻ���L2�г�������������ʵʱ�ص��ӿ�
    /// @param  RealSSEL2Overview   -- ʵʱ����
    virtual void OnSubscribe_SSEL2_Overview(const SSEL2_Overview& RealSSEL2Overview){}

    /// �Ͻ���������Ȩ��̬���ݶ�������ʵʱ�ص��ӿ�
    /// @param  RealSSEIOL1Static   -- ʵʱ����
    virtual void OnSubscribe_SSEIOL1_Static(const SSEIOL1_Static& RealSSEIOL1Static){}

    /// �Ͻ���������Ȩʵʱ���鶩������ʵʱ�ص��ӿ�
    /// @param  RealSSEIOL1Quotation    -- ʵʱ����
    virtual void OnSubscribe_SSEIOL1_Quotation(const SSEIOL1_Quotation& RealSSEIOL1Quotation){}

    /// ���L1��̬���ݶ�������ʵʱ�ص��ӿ�
    /// @param  RealSZSEL1Static    -- ʵʱ����
    virtual void OnSubscribe_SZSEL1_Static(const SZSEL1_Static& RealSZSEL1Static){}

    /// ���L1ʵʱ���鶩������ʵʱ�ص��ӿ�
    /// @param  RealSZSEL1Quotation -- ʵʱ����
    virtual void OnSubscribe_SZSEL1_Quotation(const SZSEL1_Quotation& RealSZSEL1Quotation){}

    /// ���L2��̬���ݶ�������ʵʱ�ص��ӿ�
    /// @param  RealSZSEL2Static    -- ʵʱ����
    virtual void OnSubscribe_SZSEL2_Static(const SZSEL2_Static& RealSZSEL2Static){}

    /// ���L2ʵʱ���鶩������ʵʱ�ص��ӿ�
    /// @param  RealSZSEL2Quotation -- ʵʱ����
    virtual void OnSubscribe_SZSEL2_Quotation(const SZSEL2_Quotation& RealSZSEL2Quotation){}

    /// ���L2֤ȯ״̬��������ʵʱ�ص��ӿ�
    /// @param  RealSZSEL2Status    -- ʵʱ����
    virtual void OnSubscribe_SZSEL2_Status(const SZSEL2_Status& RealSZSEL2Status){}

    /// ���L2ָ�����鶩������ʵʱ�ص��ӿ�
    /// @param  RealSZSEL2Index     -- ʵʱ����
    virtual void OnSubscribe_SZSEL2_Index(const SZSEL2_Index& RealSZSEL2Index){}

    /// ���L2���ί�ж�������ʵʱ�ص��ӿ�
    /// @param  RealSZSEL2Order     -- ʵʱ����
    virtual void OnSubscribe_SZSEL2_Order(const SZSEL2_Order& RealSZSEL2Order){}

    /// ���L2��ʳɽ���������ʵʱ�ص��ӿ�
    /// @param  RealSZSEL2Transaction   -- ʵʱ����
    virtual void OnSubscribe_SZSEL2_Transaction(const SZSEL2_Transaction& RealSZSEL2Transaction){}

    /// �н�����̬���ݶ�������ʵʱ�ص��ӿ�
    /// @param  RealCFFEXL2Static   -- ʵʱ����
    virtual void OnSubscribe_CFFEXL2_Static(const CFFEXL2_Static& RealCFFEXL2Static){}

    /// �н���L2ʵʱ���鶩������ʵʱ�ص��ӿ�
    /// @param  RealCFFEXL2Quotation    -- ʵʱ����
    virtual void OnSubscribe_CFFEXL2_Quotation(const CFFEXL2_Quotation& RealCFFEXL2Quotation){}

    /// ֣������̬���ݶ�������ʵʱ�ص��ӿ�
    /// @param  RealCZCEL1Static    -- ʵʱ����
    virtual void OnSubscribe_CZCEL1_Static(const CZCEL1_Static& RealCZCEL1Static){}

    /// ֣����ʵʱ���鶩������ʵʱ�ص��ӿ�
    /// @param  RealCZCEL1Quotation -- ʵʱ����
    virtual void OnSubscribe_CZCEL1_Quotation(const CZCEL1_Quotation& RealCZCEL1Quotation){}

    /// ������L1��̬���ݶ�������ʵʱ�ص��ӿ�
    /// @param  RealDCEL1Static     -- ʵʱ����
    virtual void OnSubscribe_DCEL1_Static(const DCEL1_Static& RealDCEL1Static){}

    /// ������L1������鶩������ʵʱ�ص��ӿ�
    /// @param  RealDCEL1Quotation  -- ʵʱ����
    virtual void OnSubscribe_DCEL1_Quotation(const DCEL1_Quotation& RealDCEL1Quotation){}

    /// ������L1����������鶩������ʵʱ�ص��ӿ�
    /// @param  RealDCEL1ArbiQuotation  -- ʵʱ����
    virtual void OnSubscribe_DCEL1_ArbiQuotation(const DCEL1_ArbiQuotation& RealDCEL1ArbiQuotation){}

    /// ������L2��̬���ݶ�������ʵʱ�ص��ӿ�
    /// @param  RealDCEL2Static     -- ʵʱ����
    virtual void OnSubscribe_DCEL2_Static(const DCEL2_Static& RealDCEL2Static){}

    /// ������L2����������鶩������ʵʱ�ص��ӿ�
    /// @param  RealDCEL2Quotation  -- ʵʱ����
    virtual void OnSubscribe_DCEL2_Quotation(const DCEL2_Quotation& RealDCEL2Quotation){}

    /// ������L2��������������鶩������ʵʱ�ص��ӿ�
    /// @param  RealDCEL2ArbiQuotation  -- ʵʱ����
    virtual void OnSubscribe_DCEL2_ArbiQuotation(const DCEL2_ArbiQuotation& RealDCEL2ArbiQuotation){}

    /// ������L2ʵʱ����۶�������ʵʱ�ص��ӿ�
    /// @param  RealDCEL2RealTimePrice  -- ʵʱ����
    virtual void OnSubscribe_DCEL2_RealTimePrice(const DCEL2_RealTimePrice& RealDCEL2RealTimePrice){}

    /// ������L2ί��ͳ�����鶩������ʵʱ�ص��ӿ�
    /// @param  RealDCEL2OrderStatistic -- ʵʱ����
    virtual void OnSubscribe_DCEL2_OrderStatistic(const DCEL2_OrderStatistic& RealDCEL2OrderStatistic){}

    /// ������L2�ּ۳ɽ������鶩������ʵʱ�ص��ӿ�
    /// @param  RealDCEL2MarchPriceQty  -- ʵʱ����
    virtual void OnSubscribe_DCEL2_MarchPriceQty(const DCEL2_MarchPriceQty& RealDCEL2MarchPriceQty){}

    /// ��������̬���ݶ�������ʵʱ�ص��ӿ�
    /// @param  RealSHFEL1Static    -- ʵʱ����
    virtual void OnSubscribe_SHFEL1_Static(const SHFEL1_Static& RealSHFEL1Static){}

    /// ������ʵʱ���鶩������ʵʱ�ص��ӿ�
    /// @param  RealSHFEL1Quotation -- ʵʱ����
    virtual void OnSubscribe_SHFEL1_Quotation(const SHFEL1_Quotation& RealSHFEL1Quotation){}
};



/// ����ϵͳ����ӿڣ����ӷ�����������֤���������ݣ���ѯ����.
class GTA_API_EXPORT IGTAQTSApiBase
{
public:
    virtual ~IGTAQTSApiBase(){};
public:
    /// ����һ��ʵ��.����ʵ��������ͨ�����ӿ�����.
    /// @param  CallBack    -- ���ӻص�������֪ͨ����״̬
    /// @return NULL        -- ����ʵ��ʧ��
    static IGTAQTSApiBase* CreateInstance(IGTAQTSCallbackBase& CallBack);

    /// �ͷ�һ��ʵ��,��ʵ����ͨ��CreateInstance���ɵ�.
    /// @param  pInstance   -- ʵ������ָ��.
    static void ReleaseInstance(IGTAQTSApiBase* pInstance);

    /// ���ó�ʱʱ�䣬���ü�ʱ��Ч��ͬ�����õĳ�ʱʱ��
    /// @param  nSenond     -- ��ʱʱ�䣬��λ��
    virtual void SetTimeout(int nSecond = TIMEOUT_DEFAULT) = 0;

    /// ע�������������ַ����ע������ͬ��ַ��ʵ�ָ߿��ã�����˳��Ϊ˳�����ӣ�����ʱ��������ǰʹ�õ�ַ
    /// @param  pIP         -- ��������ַ.
    /// @param  uPort       -- �������˿�.
    /// @return RetCode     -- �������
    virtual RetCode RegisterService(const char* pIP, unsigned short uPort) = 0;

    /// ��������������������û���֤��Ϣ��ͬ�����󣬵���ǰ����
    /// @param  pUserName   -- �˺�����
    /// @param  pPassword   -- �˺����룬���ܺ�����
    /// @return RetCode     -- �������
    virtual RetCode Login(const char* pUserName, const char* pPassword) = 0;

    /// ��ȡ���鶩�ķ�������ַ��Ϣ
    /// @param  ServerStates    -- ��ŷ�������ַ����
    /// @return RetCode         -- �������
    virtual RetCode GetConnectState(CDataBuffer<ServerState>& ServerStates) = 0;

    /// ��ȡ��Ȩ�޵���������.
    /// @param  DataTypeList-- ��������ָ�룬���ݴ�С��Ϊ��Ȩ�޵����ݸ���
    /// @return RetCode     -- �������
    virtual RetCode GetDataTypeList(CDataBuffer<MsgType>& DataTypeList) = 0;

    /// �������飬�ظ�����ͬһ�����ݶ��ʱȡ����
    /// @param  msgType     -- ��Ҫ���ĵ���������
    /// @param  pCodeList   -- ���ɶ����б��ԡ�,���ָĩβ������\0������ΪNULLʱ����ȫ�г�
    /// @return RetCode     -- �������
    virtual RetCode Subscribe(MsgType msgType, char* pCodeList = NULL) = 0;

    /// ȡ������
    /// @param  msgType     -- ��Ҫȡ�����ĵ���������
    /// @param  pCodeList   -- ȡ�������б��ԡ�,���ָĩβ������\0������ΪNULLʱȡ�����д���
    /// @return RetCode     -- �������
    virtual RetCode Unsubscribe(MsgType msgType, char* pCodeList = NULL) = 0;

    /// ȡ�����ж�����Ϣ
    /// @return RetCode     -- �������
    virtual RetCode UnsubscribeAll() = 0;

    /// ��ȡ��Ʊ�б�
    /// @param  pMarketTag  -- �г���ʶ���ԡ�,���ָ����г���ʶ��ĩβ������\0������������ΪNULL
    /// @param  StockList   -- ���صĸ��ɴ����б����г���־��
    /// @return RetCode     -- �������
    virtual RetCode GetStockList(char* pMarketTag, CDataBuffer<StockSymbol>& StockList) = 0;

    /// ��ѯ�Ͻ���L1��̬����
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSSEL1Static     -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SSEL1_Static(char* pCodeList, CDataBuffer<SSEL1_Static>& SnapSSEL1Static) = 0;

    /// ��ѯ�Ͻ���L1ʵʱ����
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSSEQuotation     -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SSEL1_Quotation(char* pCodeList, CDataBuffer<SSEL1_Quotation>& SnapSSEQuotation) = 0;

    /// ��ѯ�Ͻ���L2��̬����
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSSEStatic        -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SSEL2_Static(char* pCodeList, CDataBuffer<SSEL2_Static>& SnapSSEL2Static) = 0;

    /// ��ѯ�Ͻ���L2ʵʱ�������
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSSEL2Quotation    -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SSEL2_Quotation(char* pCodeList, CDataBuffer<SSEL2_Quotation>& SnapSSEL2Quotation) = 0;

    /// ��ѯ�Ͻ���L2ָ������
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSSEL2Index        -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SSEL2_Index(char* pCodeList, CDataBuffer<SSEL2_Index>& SnapSSEL2Index) = 0;

    /// ��ѯ�Ͻ���L2��ʳɽ�
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSSEL2Transation   -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SSEL2_Transaction(char* pCodeList, CDataBuffer<SSEL2_Transaction>& SnapSSEL2Transation) = 0;

    /// ��ѯ�Ͻ���L2���⼯�Ͼ���
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSSEL2Auction    -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SSEL2_Auction(char* pCodeList, CDataBuffer<SSEL2_Auction>& SnapSSEL2Auction) = 0;

    /// ��ѯ�Ͻ���L2�г�����
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSSEL2Overview   -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SSEL2_Overview(char* pCodeList, CDataBuffer<SSEL2_Overview>& SnapSSEL2Overview) = 0;

    /// ��ѯ�Ͻ���������Ȩ��̬����
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSSEIOL1Static   -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SSEIOL1_Static(char* pCodeList, CDataBuffer<SSEIOL1_Static>& SnapSSEIOL1Static) = 0;

    /// ��ѯ�Ͻ���������Ȩʵʱ����
    /// @param  pCodeList               -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSSEIOL1Quotation    -- ���������б�
    /// @return RetCode                 -- �������
    virtual RetCode QuerySnap_SSEIOL1_Quotation(char* pCodeList, CDataBuffer<SSEIOL1_Quotation>& SnapSSEIOL1Quotation) = 0;

    /// ��ѯ���L1��̬����
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSZSEL1Static    -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SZSEL1_Static(char* pCodeList, CDataBuffer<SZSEL1_Static>& SnapSZSEL1Static) = 0;

    /// ��ѯ���L1ʵʱ����
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSZSEL1Quotation -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SZSEL1_Quotation(char* pCodeList, CDataBuffer<SZSEL1_Quotation>& SnapSZSEL1Quotation) = 0;

    /// ��ѯ���L2��̬����
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSZSEL2Static    -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SZSEL2_Static(char* pCodeList, CDataBuffer<SZSEL2_Static>& SnapSZSEL2Static) = 0;

    /// ��ѯ���L2ʵʱ����
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSZSEL2Quotation    -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SZSEL2_Quotation(char* pCodeList, CDataBuffer<SZSEL2_Quotation>& SnapSZSEL2Quotation) = 0;

    /// ��ѯ���L2֤ȯ״̬
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSZSEL2StockStatus  -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SZSEL2_Status(char* pCodeList, CDataBuffer<SZSEL2_Status>& SnapSZSEL2StockStatus) = 0;

    /// ��ѯ���L2ָ������
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSZSEL2Index        -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SZSEL2_Index(char* pCodeList, CDataBuffer<SZSEL2_Index>& SnapSZSEL2Index) = 0;

    /// ��ѯ���L2���ί��
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSZSEL2Order        -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SZSEL2_Order(char* pCodeList, CDataBuffer<SZSEL2_Order>& SnapSZSEL2Order) = 0;

    /// ��ѯ���L2��ʳɽ�
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSZSEL2Transaction  -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SZSEL2_Transaction(char* pCodeList, CDataBuffer<SZSEL2_Transaction>& SnapSZSEL2Transaction) = 0;

    /// ��ѯ�н�����̬����
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapCFFEXL2Static       -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_CFFEXL2_Static(char* pCodeList, CDataBuffer<CFFEXL2_Static>& SnapCFFEXL2Static) = 0;

    /// ��ѯ�н���L2ʵʱ����
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapCFFEXL2Quotation    -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_CFFEXL2_Quotation(char* pCodeList, CDataBuffer<CFFEXL2_Quotation>& SnapCFFEXL2Quotation) = 0;

    /// ��ѯ֣������̬����
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapCZCEL1Static    -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_CZCEL1_Static(char* pCodeList, CDataBuffer<CZCEL1_Static>& SnapCZCEL1Static) = 0;

    /// ��ѯ֣����ʵʱ����
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapCZCEL1Quotation -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_CZCEL1_Quotation(char* pCodeList, CDataBuffer<CZCEL1_Quotation>& SnapCZCEL1Quotation) = 0;

    /// ��ѯ������L1��̬����
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapDCEL1Static     -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_DCEL1_Static(char* pCodeList, CDataBuffer<DCEL1_Static>& SnapDCEL1Static) = 0;

    /// ��ѯ������L1�������
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapDCEL1Quotation  -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_DCEL1_Quotation(char* pCodeList, CDataBuffer<DCEL1_Quotation>& SnapDCEL1Quotation) = 0;

    /// ��ѯ������L1�����������
    /// @param  pCodeList               -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapDCEL1ArbiQuotation  -- ���������б�
    /// @return RetCode                 -- �������
    virtual RetCode QuerySnap_DCEL1_ArbiQuotation(char* pCodeList, CDataBuffer<DCEL1_ArbiQuotation>& SnapDCEL1ArbiQuotation) = 0;

    /// ��ѯ������L2��̬����
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapDCEL2Static     -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_DCEL2_Static(char* pCodeList, CDataBuffer<DCEL2_Static>& SnapDCEL2Static) = 0;

    /// ��ѯ������L2�����������
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapDCEL2Quotation  -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_DCEL2_Quotation(char* pCodeList, CDataBuffer<DCEL2_Quotation>& SnapDCEL2Quotation) = 0;

    /// ��ѯ������L2���������������
    /// @param  pCodeList               -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapDCEL2ArbiQuotation  -- ���������б�
    /// @return RetCode                 -- �������
    virtual RetCode QuerySnap_DCEL2_ArbiQuotation(char* pCodeList, CDataBuffer<DCEL2_ArbiQuotation>& SnapDCEL2ArbiQuotation) = 0;

    /// ��ѯ������L2ʵʱ�����
    /// @param  pCodeList               -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapDCEL2RealTimePrice  -- ���������б�
    /// @return RetCode                 -- �������
    virtual RetCode QuerySnap_DCEL2_RealTimePrice(char* pCodeList, CDataBuffer<DCEL2_RealTimePrice>& SnapDCEL2RealTimePrice) = 0;

    /// ��ѯ������L2ί��ͳ������
    /// @param  pCodeList               -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapDCEL2OrderStatistic -- ���������б�
    /// @return RetCode                 -- �������
    virtual RetCode QuerySnap_DCEL2_OrderStatistic(char* pCodeList, CDataBuffer<DCEL2_OrderStatistic>& SnapDCEL2OrderStatistic) = 0;

    /// ��ѯ������L2�ּ۳ɽ�������
    /// @param  pCodeList               -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapDCEL2MarchPriceQty  -- ���������б�
    /// @return RetCode                 -- �������
    virtual RetCode QuerySnap_DCEL2_MarchPriceQty(char* pCodeList, CDataBuffer<DCEL2_MarchPriceQty>& SnapDCEL2MarchPriceQty) = 0;

    /// ��ѯ��������̬����
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSHFEL1Static    -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SHFEL1_Static(char* pCodeList, CDataBuffer<SHFEL1_Static>& SnapSHFEL1Static) = 0;

    /// ��ѯ������ʵʱ����
    /// @param  pCodeList           -- ���ն����б�NULLʱΪȫ�г���������
    /// @param  SnapSHFEL1Quotation -- ���������б�
    /// @return RetCode             -- �������
    virtual RetCode QuerySnap_SHFEL1_Quotation(char* pCodeList, CDataBuffer<SHFEL1_Quotation>& SnapSHFEL1Quotation) = 0;

};

#endif // GTA_QTS_INTERFACE_BASE_H_

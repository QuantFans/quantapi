//////////////////////////////////////////////////////////////////////////////
/// @file       GTAQTSInterfaceEx.h 
/// @brief      ��չ����ӿڶ��壬���ֶβ�ѯ�����������ݣ��Զ�����
/// @copyright  Copyright (C), 2008-2014, GTA Information Tech. Co., Ltd.
/// @version    2.0
/// @date       2014.7.18
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_QTS_INTERFACE_EX_H_
#define GTA_QTS_INTERFACE_EX_H_
#include "QTSDataType.h"
#include "QTSStruct.h"
#include "QTSDataFieldDefine.h"

/// ʵʱ���ݡ�����״̬�ص��ӿڣ����ֶη�������
class GTA_API_EXPORT IGTAQTSCallbackEx
{
public:

    /// ��½״̬����
    /// @param  errCode  -- ʧ��ԭ��(�û����ڡ��ظ���½)�û�������������д���
    virtual void OnLoginState( RetCode errCode){}

    /// ����״̬���أ����ӳɹ�/ʧ��
    /// @param  msgType      -- ��Ϣ����
    /// @param  errCode     -- ʧ��ԭ�򣬳ɹ�ʱ����0
    virtual void OnConnectionState(MsgType msgType, RetCode errCode){}

    /// �Ự��־ʧЧ������API���Ѿ�û��ʹ�ã�
    /// @param  pSessionTag    -- �Ự��־
    virtual void OnSessionTagInvalid(void* pSessionTag){}

    /// ��������ʵʱ�ص��ӿ�
    /// @param  msgCategory -- ���ص����ݷ���
    /// @param  RealData    -- ʵʱ����
    /// @param  pSessionTag -- ��������ʱ������û���־
    virtual void OnSubscribe(const DataCategory msgCategory, IQuotationData& RealData, void*  pSessionTag){}
};


/// ����ϵͳ����ӿڣ����ӷ�����������֤���������ݣ���ѯ����.
class GTA_API_EXPORT IGTAQTSApiEx
{
public:
    virtual ~IGTAQTSApiEx(){};
public:
    /// ����һ��ʵ��.����ʵ��������ͨ�����ӿ�����.
    /// @param  CallBack    -- ���ӻص�������֪ͨ����״̬
    /// @return NULL        -- ����ʵ��ʧ��
    static IGTAQTSApiEx* CreateInstance(IGTAQTSCallbackEx& CallBack);

    /// �ͷ�һ��ʵ��,��ʵ����ͨ��CreateInstance���ɵ�.
    /// @param  pInstance   -- ʵ������ָ��.
    static void ReleaseInstance(IGTAQTSApiEx* pInstance);

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
    /// @param  msgCategory -- ��Ҫ���ĵ����ݷ���
    /// @param  pCodeList   -- ���ɶ����б��ԡ�,���ָĩβ������\0������������ΪNULL
    /// @param  pSessionTag -- �Ự��־,�ص���������OnSubscribeʱ���ظ���ֵ
    /// @return RetCode     -- �������
    virtual RetCode Subscribe(DataCategory msgCategory, char* pCodeList, void*  pSessionTag) = 0;

    /// �������ݷ��ࡢ�û���ʶ�ʹ����б�ȡ������
    /// @param  msgCategory -- ȡ�����ĵ����ݷ���
    /// @param  pCodeList   -- ȡ�������б��ԡ�,���ָĩβ������\0����
    /// @param  pSessionTag -- �Ự��־,ȡ���ñ�־���������ж���
    /// @return RetCode     -- �������
    virtual RetCode Unsubscribe(DataCategory msgCategory, char* pCodeList, void*  pSessionTag) = 0;

    /// �������ݷ���ʹ����б�ȡ������
    /// @param  msgCategory -- ȡ�����ĵ����ݷ���
    /// @param  pCodeList   -- ȡ�������б��ԡ�,���ָĩβ������\0����
    /// @return RetCode     -- �������
    virtual RetCode UnsubscribeByCategory(DataCategory msgCategory, char* pCodeList) = 0;

    /// ���ݻỰ��־�ʹ����б�ȡ������
    /// @param  pSessionTag -- �Ự��־,ȡ���ñ�־���������ж���
    /// @param  pCodeList   -- ȡ�������б��ԡ�,���ָĩβ������\0����
    /// @return RetCode     -- �������
    virtual RetCode UnsubscribeBySessionTag(void*  pSessionTag, char* pCodeList) = 0;

    /// ȡ�����ж�����Ϣ
    /// @return RetCode     -- �������
    virtual RetCode UnsubscribeAll() = 0;

    /// ��ѯ�Ͻ�����̬����
    /// @param  msgCategory -- ��Ҫ��ѯ�����ݷ���
    /// @param  pCodeList   -- ���ɶ����б��ԡ�,���ָĩβ������\0������������ΪNULL
    /// @param  SnapData    -- ���������б�
    /// @return RetCode     -- �������
    virtual RetCode QuerySnap(DataCategory msgCategory, char* pCodeList, CDataBuffer<CQuotationDataPtr>& SnapData) = 0;

    /// ��ȡ��Ʊ�б�
    /// @param  pMarketTag  -- �г���ʶ���ԡ�,���ָ����г���ʶ��ĩβ������\0������������ΪNULL
    /// @param  StockList   -- ���صĸ��ɴ����б����г���־��
    /// @return RetCode     -- �������
    virtual RetCode GetStockList(char* pMarketTag, CDataBuffer<StockSymbol>& StockList) = 0;
};


#endif // GTA_QTS_INTERFACE_EX_H_

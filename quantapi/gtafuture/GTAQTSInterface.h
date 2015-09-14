//////////////////////////////////////////////////////////////////////////////
/// @file       GTAQTSInterface.h
/// @brief      ����ӿڶ��壬���Զ���������
/// @copyright  Copyright (C), 2008-2014, GTA Information Tech. Co., Ltd.
/// @version    1.9.1
/// @date       2014.7.18
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_QTS_INTERFACE_H_
#define GTA_QTS_INTERFACE_H_

#include "GTAMarketServiceApi.h"

/// ����ϵͳ����ӿ�.ʹ�ô˽ӿ�ʱ������Ҫ�����������¶���<br>
/// �ṩ����������ع���.
class GTA_API_EXPORT IGTAQTSInterface
{
public:
    virtual ~IGTAQTSInterface(){};
public:
    /// ����һ��ʵ��.����ʵ��������ͨ�����ӿ�����.
    /// @param Callback ����ص��ӿ�.
    /// @return ʧ�ܷ���NULL.
    static IGTAQTSInterface* CreateInstance(IGTAMarketServiceCallback* Callback);

    /// �ͷ�һ��ʵ��,��ʵ����ͨ��CreateInstance���ɵ�.
    /// @param pInstance IGTAMarketServiceApiʵ��.
    static void ReleaseInstance(IGTAQTSInterface* pInstance);

    /// ע�������������ַ����ע������ͬ��ַ��ʵ�ָ߿��ã�����˳��Ϊ˳�����ӣ�����ʱ��������ǰʹ�õ�ַ
    /// @param pIP ��������ַ.
    /// @param uPort �������˿�.
    virtual void RegisterService(const char* pIP, unsigned short uPort) = 0;

    /// �����������֤�û�.
    /// ���ӳɹ�����֤ģʽ����Ҫ���ô˺����Ƚ�����֤������֤ģʽֱ�ӵ��û�ȡ�г��б���.
    /// @param userID �û�ID������֤����������.
    virtual void Logon(int userID) = 0;

    /// ���ӷ�����
    /// @return ����false��δ������Ч��������ַ������ture����ʼ��������
    virtual bool Connect() = 0;

    /// ����������������������������Ϊ10-20�룬����Connectǰ����
    /// @param uTimeout ��������ʱ��,��λ��
    virtual void SetTimeout(const unsigned int uTimeout = 10) = 0;

    /// ��ȡ�г���������״̬.
    /// @return ����״̬.
    virtual NetState GetConnectionState() = 0;
    /// ��ȡ��ǰ���ӷ�������ַ
    /// @param pAddr    ��ŷ�������ַ��ָ�룬����ΪIP:Port����192.168.1.1:8000
    /// @param nBufLen  pAddr����ĳ���
    virtual void GetConnectedAddr(char* pAddr, const int nBufLen) = 0;

    /// ��ȡ�г��б�.
    virtual void GetMarketList() = 0;

    /// ��ȡ�г������б�.
    /// @param mi �г�.
    virtual void GetStockList(MarketInfo* mi) = 0;

    /// ����/ȡ������.
    /// @param mdi �г����ݱ�־.
    /// @param dataType �������ͣ��μ������г��������Ͷ���
    /// @param sm ����ģʽ.
    /// @param mr �г���Χ.
    /// @param codelist �����б��ַ�����ʽ������֮����','�ָ�,���type���������飬��NULL.
    /// @param codelistLen ���뻺��������.
    virtual void Subscribe(MarketDataInfo* mdi, SubscribeMode sm, MarketRange mr, const char* codelist, int codelistLen) = 0;

    /// ��ѯ����/�г�����.
    /// @param mdi �г����ݱ�־.
    /// @param mr �г���Χ.
    /// @param sds ����Դ����
    /// @param codelist �����ɲ�ѯ���գ�NULL��ʾ����ѯ���ɿ��գ��ַ�����ʽ�����б�����֮���ö��ŷָ�.
    /// @param codelistLen ���뻺��������.
    virtual void QuerySnap(MarketDataInfo* mdi, MarketRange mr, SnapDataSource sds, const char* codelist, int codelistLen) = 0;

    /// ͬ����ѯ����/�г�����.
    /// @param mdi �г����ݱ�־.
    /// @param mr �г���Χ.
    /// @param sds ����Դ����
    /// @param codelist �����ɲ�ѯ���գ�NULL��ʾ����ѯ���ɿ��գ��ַ�����ʽ�����б�����֮���ö��ŷָ�.
    /// @param codelistLen ���뻺��������.
    /// @return IDataBuf* ��������.
    virtual IDataBuf* SyncQuerySnap(MarketDataInfo* mdi, MarketRange mr, SnapDataSource sds, const char* codelist, int codelistLen) = 0;

    /// ͬ����ȡ���SPTable����.
    /// @return ���SPTable����.
    virtual IDataBuf* SyncGetHKSPTable() = 0;
};

#endif // GTA_QTS_INTERFACE_H_

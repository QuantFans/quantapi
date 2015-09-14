//////////////////////////////////////////////////////////////////////////////
///
/// @file    GTAMarketServiceApi.h
/// @brief   ��֤������ӿڶ���
/// @note    Copyright (C), 2008-2010, GTA Information Tech. Co., Ltd.
/// @version 1.0
/// @author  �οɶ�
/// @date    2010.10.18
///
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_MARKET_SERVICE_API_H_
#define GTA_MARKET_SERVICE_API_H_

#include "GTAMarketServiceApiStruct.h"
#include "QutoSvrDefine.h"
#include "OutputData.h"

/// ���ݷ�װ��.
/// ��Ҫ����ͬ������api�ӿ�ʱ����api�ڲ����ص����ݽ��з�װ.
class GTA_API_EXPORT IDataBuf
{
public:
    /// ����ʵ��.
    static IDataBuf* CreateInstance();

    /// �ͷ�ʵ��.
    static void ReleaseInstance(IDataBuf* db);

    /// ��ȡ����ָ��ͷ.
    virtual char* GetBuf() = 0;

    /// ��ȡ���ݳ���.
    virtual int GetLength() = 0;

    /// �������.
    ///
    /// @param data ����ָ��.
    /// @param len ���ݳ���.
    virtual int Append(char* data, int len) = 0;

    virtual ~IDataBuf(){};
};

/// ��֤�ص��ӿ�.
/// ��֤����Ľ�����ڴ˽ӿ�֪ͨӦ��.
class IGTAAuthCallback
{
public:
    /// ֪ͨ��֤�����Ϣ.
    ///
    /// @param cr ��֤��Ӧ��Ϣ.
    /// @param msi �г���������Ϣ.
    /// @param msicnt �г���������Ϣ����.
    virtual void OnCertify(CertifyResp* cr, MarketServerInfo* msi, int msicnt){};

    /// ֪ͨ�����г������������Ϣ.
    ///
    /// @param result ������� 0�ɹ�������ʧ�ܣ����������.
    /// @param msi �г���������Ϣ(����).
    virtual void OnMarketServer(unsigned char result, MarketServerInfo* msi){};
};

/// ��֤�ӿ�.
/// �ṩ�û���֤�Լ����»�ȡ�����������ַ�ȹ���.
class GTA_API_EXPORT IGTAAuthApi
{
public:
    /// ����һ��IGTAAuthApiʵ��.
    /// ����IGTAAuthApiʵ��������ͨ�����ӿ�����.
    ///
    /// @return IGTAAuthApi* ʧ�ܷ���NULL.
    static IGTAAuthApi* CreateInstance();

    /// �ͷ�һ��IGTAAuthApiʵ��.
    /// ��ʵ����ͨ��CreateInstance���ɵ�. 
    ///
    /// @param pInstance �ӿ�ʵ��.
    static void ReleaseInstance(IGTAAuthApi* pInstance);

    /// ��ʼ����֤ģ��.
    /// ������������̣߳���ʼ�����绷���Ȳ���.
    /// 
    /// @param cb ��֤����ص��ӿ�.
    ///
    /// @return 0�ɹ�������ʧ��.
    virtual int Init(IGTAAuthCallback* cb) = 0;

    /// ֹͣģ��.
    /// ģ���ṩ�����з���ֹͣ.
    virtual void Fini() = 0;

    /// ������֤.
    /// 
    /// @param req ������Ϣ.
    virtual void RequestCertify(CertifyReq* req) = 0;

    /// �����г���������Ϣ.
    ///
    /// @param userID �û�ID,��֤���ص���ϢCertifyResp�����userID�ֶ�.
    /// @param mi �г���־.
    virtual void RequestMarketServer(int userID, MarketInfo* mi) = 0;

    virtual ~IGTAAuthApi(){};
};

/// �������ص��ӿ�.
/// �첽���������ӿڵĽ���ڴ˽ӿ�֪ͨӦ��.
class IGTAMarketServiceCallback
{
public:
    /// ֪ͨ�������ӽ��.
    /// 
    /// @param reason ���ӽ����־ 0�ɹ�������ʧ�ܣ����ʧ�ܴ����.
    virtual void OnConnect(int reason){};

    /// ֪ͨ����Ͽ�.
    ///
    /// @param reason �����룬���ʧ�ܴ����.
    virtual void OnConnectionFail(int reason){};

    /// ��¼���.
    /// 
    /// @param userID �û�ID.
    /// @param result ��¼�����0�ɹ���������ʧ��.
    virtual void OnLogon(int userID, int result){};

	/// ֪ͨ�г��б�����.
    /// 
    /// @param md �г��б����ݣ�����cnt��MarketDesc.
    /// @param cnt �г�����.
    virtual void OnMarketList(MarketDesc* md, int cnt){};

    /// ֪ͨ�г������б�.
    /// 
    /// @param mi �г�.
    /// @param data �����б����ݣ�����֮���Զ��ŷָ�. 
    /// @param datalen ���ݳ���.
    virtual void OnStockList(MarketInfo* mi, void* data, int datalen){};

    /// ����/ȡ�����Ĳ������.
    /// 
    /// @param mdi �г����ݱ�־
    /// @param result ������� 0�ɹ� ����ʧ��.
    virtual void OnSubscribe(MarketDataInfo* mdi, int result){};

    /// ֪ͨʵʱ����.
    /// 
    /// @param mdi �г����ݱ�־.
    /// @param dataType �������ͣ��μ������г��������Ͷ���
    /// @param data �������ݣ�ÿ���г���ͬ����Ӧ�����н���.
    /// @param datalen ���ݳ���
    virtual void OnRealData(MarketDataInfo* mdi, void* data, int datalen){};

    /// ֪ͨ��������.
    ///
    /// @param mdi �г����ݱ�־.
    /// @param data �������ݣ�ÿ���г���ͬ����Ӧ�����н���.
    /// @param datalen ���ݳ���.
    virtual void OnSnapData(MarketDataInfo* mdi, void* data, int datalen){};

    /// ֪ͨ��ۼ�λ��.
    /// 
    /// @param data ��λ������.
    /// @param datalen ��λ�����ݳ���.
    virtual void OnHKSPTable(void* data, int datalen){};

    /// ϵͳ����״̬.
    /// 
    /// @param type ״̬����
    /// @param data ״̬����.
    /// @param datalen ״̬���ݳ���.
    virtual void OnSysState(BYTE type, void* data, int datalen){};
};

/// ����ϵͳ����ӿ�.
/// �ṩ����������ع���.
class GTA_API_EXPORT IGTAMarketServiceApi
{
public:
    /// ����һ��IGTAMarketServiceApiʵ��.
    /// ����IGTAMarketServiceApiʵ��������ͨ�����ӿ�����.
    /// 
    /// @return ʧ�ܷ���NULL.
    static IGTAMarketServiceApi* CreateInstance();

    /// �ͷ�һ��IGTAMarketServiceApiʵ��.
    /// ��ʵ����ͨ��CreateInstance���ɵ�.
    /// 
    /// @param pInstance IGTAMarketServiceApiʵ��.
    static void ReleaseInstance(IGTAMarketServiceApi* pInstance);

    /// ��ʼ��ģ��.
    /// ������������̣߳���ʼ�����绷���Ȳ���.
    /// 
    /// @param cb ����ص��ӿ�.
    /// @param snapshotFlag ���ձ�־��0������ 1 ����.
    /// 
    /// @return 0�ɹ�������ʧ��.
    virtual int Init(IGTAMarketServiceCallback* cb, int snapshotFlag) = 0;

    /// ֹͣģ��.
    /// ģ���ṩ�����з���ֹͣ.
    virtual void Fini() = 0;    

    /// �����г����������.
    /// 
    /// @param addr ��������ַ.
    /// @param port �������˿�.
    /// @param timeout ���ӳ�ʱ���룩.
    virtual void Connect(const char* addr, unsigned short port, unsigned int timeout = 10) = 0;

    /// �����������֤�û�.
    /// ���ӳɹ�����֤ģʽ����Ҫ���ô˺����Ƚ�����֤������֤ģʽֱ�ӵ��û�ȡ�г��б���.
    /// 
    /// @param userID �û�ID������֤����������.
    virtual void Logon(int userID) = 0;

    /// ��ȡ�г���������״̬.
    /// 
    /// @return ����״̬.
    virtual NetState GetConnectionState() = 0;

    /// �Ͽ����г���������.���ӶϺ���ɻص�֪ͨ.
    virtual void CloseConnection() = 0;

    /// ��ȡ�г��б�.
    virtual void GetMarketList() = 0;

    /// ��ȡ�г������б�.
    /// 
    /// @param mi �г�.
    virtual void GetStockList(MarketInfo* mi) = 0;

    /// ����/ȡ������.
    /// 
    /// @param mdi �г����ݱ�־.
    /// @param dataType �������ͣ��μ������г��������Ͷ���
    /// @param sm ����ģʽ.
    /// @param mr �г���Χ.
    /// @param codelist �����б��ַ�����ʽ������֮����','�ָ�,���type������
    ///                 ���飬��NULL.
    /// @param codelistLen ���뻺��������.
    virtual void Subscribe(MarketDataInfo* mdi, 
                           SubscribeMode sm, MarketRange mr, 
                           const char* codelist, int codelistLen) = 0;

    /// ��ѯ����/�г�����.
    /// 
    /// @param mdi �г����ݱ�־.
    /// @param mr �г���Χ.
    /// @param sds ����Դ����
    /// @param codelist �����ɲ�ѯ���գ�NULL��ʾ����ѯ���ɿ��գ��ַ�����ʽ����
    ///                 �б�����֮���ö��ŷָ�.
    /// @param codelistLen ���뻺��������.
    virtual void QuerySnap(MarketDataInfo* mdi, MarketRange mr, SnapDataSource sds, 
                           const char* codelist, int codelistLen) = 0;

    /// ͬ����ѯ����/�г�����.
    /// 
    /// @param mdi �г����ݱ�־.
    /// @param mr �г���Χ.
    /// @param sds ����Դ����
    /// @param codelist �����ɲ�ѯ���գ�NULL��ʾ����ѯ���ɿ��գ��ַ�����ʽ����
    ///                 �б�����֮���ö��ŷָ�.
    /// @param codelistLen ���뻺��������.
    ///
    /// @return IDataBuf* ��������.
    virtual IDataBuf* SyncQuerySnap(MarketDataInfo* mdi, MarketRange mr, SnapDataSource sds, 
                                    const char* codelist, int codelistLen) = 0;

    /// ͬ����ȡ���SPTable����.
    /// 
    /// @return ���SPTable����.
    virtual IDataBuf* SyncGetHKSPTable() = 0;

    virtual ~IGTAMarketServiceApi(){};
};

/// �������ػص��ӿ�.
/// �첽������������ؽӿڵĽ���ڴ˽ӿ�֪ͨӦ��.
class IGTADataDownloadCallback
{
public:
    /// ֪ͨ���صľ�̬����.    
    /// 
    /// @param result   ���ӽ����־ 0�ɹ�������ʧ�ܣ����ʧ�ܴ����.
    /// @param mdi      �г����ݱ�־
    /// @param data     ���ݣ����ΪNULL����ʾ���������Ӧ���ݽ���
    /// @param datalen  ���ݳ���
    virtual void OnData(unsigned char result, MarketDataInfo* mdi, 
                        void* data, int datalen){};
};

/// �������ؽӿ�.
/// �ṩ��ʷ�������ع���.
class GTA_API_EXPORT IGTADataDownloadApi
{
public:
    /// ����һ��IGTADataDownloadApiʵ��.
    /// ����IGTADataDownloadApiʵ��������ͨ�����ӿ�����.
    /// 
    /// @return ʧ�ܷ���NULL.
    static IGTADataDownloadApi* CreateInstance();

    /// �ͷ�һ��IGTADataDownloadApiʵ��.
    /// ��ʵ����ͨ��CreateInstance���ɵ�.
    /// 
    /// @param pInstance IGTADataDownloadApiʵ��.
    static void ReleaseInstance(IGTADataDownloadApi* pInstance);

    /// ��ʼ��ģ��.
    /// ������������̣߳���ʼ�����绷���Ȳ���.
    /// 
    /// @param cb ����ص��ӿ�.
    /// 
    /// @return 0�ɹ�������ʧ��.
    virtual int Init(IGTADataDownloadCallback* cb) = 0;

    /// ֹͣģ��.
    /// ģ���ṩ�����з���ֹͣ.
    virtual void Fini() = 0;

    /// ��������.
    /// 
    /// @param req ������Ϣ.
    virtual void RequestData(DataDownloadReq* req) = 0;

    virtual ~IGTADataDownloadApi(){};
};

#endif // GTA_MARKET_SERVICE_API_H_

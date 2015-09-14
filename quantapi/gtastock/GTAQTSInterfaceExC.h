//////////////////////////////////////////////////////////////////////////////
/// @file       GTAQTSInterfaceExC.h 
/// @brief      ��չ����ӿڶ��壬���ֶβ�ѯ�����������ݣ��Զ�����
/// @copyright  Copyright (C), 2008-2014, GTA Information Tech. Co., Ltd.
/// @version    2.0
/// @date       2014.7.18
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_QTS_INTERFACE_EX_C_H_
#define GTA_QTS_INTERFACE_EX_C_H_
#include "QTSDataType.h"
#include "QTSStruct.h"
#include "QTSDataFieldDefine.h"
extern "C"
{
/// ʵʱ���ݡ�����״̬�ص��ӿڣ����ֶη�������

/// ��½״̬����
/// @param  errCode  -- ʧ��ԭ��(�û����ڡ��ظ���½)�û�������������д���
typedef void (*OnExLoginState)( RetCode errCode);
void GTA_API_EXPORT _CDECL SetOnExLoginState(OnExLoginState cbOnExLoginState);

/// ����״̬���أ����ӳɹ�/ʧ��
/// @param  msgType      -- ��Ϣ����
/// @param  errCode     -- ʧ��ԭ�򣬳ɹ�ʱ����0
typedef void (*OnExConnectionState)(MsgType msgType, RetCode errCode);
void GTA_API_EXPORT _CDECL SetOnExConnectionState(OnExConnectionState cbOnExConnectionState);

/// �Ự��־ʧЧ������AIP���Ѿ�û��ʹ�ã�
/// @param  pSessionTag    -- �Ự��־
typedef void (*OnExSessionTagInvalid)(void* pSessionTag);
void GTA_API_EXPORT _CDECL SetOnExSessionTagInvalid(OnExSessionTagInvalid cbOnExSessionTagInvalid);

/// ��������ʵʱ�ص��ӿ�
/// @param  msgCategory -- ���ص����ݷ���
/// @param  RealData    -- ʵʱ����
/// @param  pSessionTag -- ��������ʱ������û���־
typedef void (*OnExSubscribe)(const DataCategory msgCategory, CQuotationDataPtr* RealData, void*  pSessionTag);
void GTA_API_EXPORT _CDECL SetOnExSubscribe(OnExSubscribe cbOnExSubscribe);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ����ϵͳ����ӿڣ����ӷ�����������֤���������ݣ���ѯ����.

/// ��չAPI������ʼ��
void GTA_API_EXPORT _CDECL ExInit();

/// ��չAPI��������ʼ��
void GTA_API_EXPORT _CDECL ExUninit();

/// ���ó�ʱʱ�䣬���ü�ʱ��Ч��ͬ�����õĳ�ʱʱ��
/// @param  nSenond     -- ��ʱʱ�䣬��λ��
void GTA_API_EXPORT _CDECL ExSetTimeout(int nSecond = TIMEOUT_DEFAULT);

/// ע�������������ַ����ע������ͬ��ַ��ʵ�ָ߿��ã�����˳��Ϊ˳�����ӣ�����ʱ��������ǰʹ�õ�ַ
/// @param  pIP         -- ��������ַ.
/// @param  uPort       -- �������˿�.
/// @return RetCode     -- �������
RetCode GTA_API_EXPORT _CDECL ExRegisterService(const char* pIP, unsigned short uPort);

/// ��������������������û���֤��Ϣ��ͬ�����󣬵���ǰ����
/// @param  pUserName   -- �˺�����
/// @param  pPassword   -- �˺����룬���ܺ�����
/// @return RetCode     -- �������
RetCode GTA_API_EXPORT _CDECL ExLogin(const char* pUserName, const char* pPassword);

/// ��ȡ���鶩�ķ�������ַ��Ϣ
/// @param  ServerAddrs -- ��ŷ�������ַ���������ExReleaseValue�ͷ��ڴ�
/// @param  pSize       -- �������ݸ���
/// @return RetCode     -- �������
RetCode GTA_API_EXPORT _CDECL ExGetServerAddr(ServerState** ppServerAddrs, int* pSize);

/// ��ȡ��Ȩ�޵���������.
/// @param  ppDataTypeList  -- ��������ָ�룬���ݴ�С��Ϊ��Ȩ�޵����ݸ����������ExReleaseValue�ͷ��ڴ�
/// @param  pSize           -- �������ݸ���
/// @return RetCode         -- �������
RetCode GTA_API_EXPORT _CDECL ExGetMsgTypeList(MsgType** ppDataTypeList, int* pSize);


/// �������飬�ظ�����ͬһ�����ݶ��ʱȡ����
/// @param  msgCategory -- ��Ҫ���ĵ����ݷ���
/// @param  pCodeList   -- ���ɶ����б��ԡ�,���ָĩβ������\0������������ΪNULL
/// @param  pSessionTag -- �Ự��־,�ص���������OnSubscribeʱ���ظ���ֵ
/// @return RetCode     -- �������
RetCode GTA_API_EXPORT _CDECL ExSubscribe(DataCategory msgCategory, char* pCodeList, void*  pSessionTag);

/// �������ݷ��ࡢ�û���ʶ�ʹ����б�ȡ������
/// @param  msgCategory -- ȡ�����ĵ����ݷ���
/// @param  pCodeList   -- ȡ�������б��ԡ�,���ָĩβ������\0����
/// @param  pSessionTag -- �Ự��־,ȡ���ñ�־���������ж���
/// @return RetCode     -- �������
RetCode GTA_API_EXPORT _CDECL ExUnsubscribe(DataCategory msgCategory, char* pCodeList, void*  pSessionTag);

/// �������ݷ���ʹ����б�ȡ������
/// @param  msgCategory -- ȡ�����ĵ����ݷ���
/// @param  pCodeList   -- ȡ�������б��ԡ�,���ָĩβ������\0����
/// @return RetCode     -- �������
RetCode GTA_API_EXPORT _CDECL ExUnsubscribeByCategory(DataCategory msgCategory, char* pCodeList);

/// ���ݻỰ��־�ʹ����б�ȡ������
/// @param  pSessionTag -- �Ự��־,ȡ���ñ�־���������ж���
/// @param  pCodeList   -- ȡ�������б��ԡ�,���ָĩβ������\0����
/// @return RetCode     -- �������
RetCode GTA_API_EXPORT _CDECL ExUnsubscribeBySessionTag(void*  pSessionTag, char* pCodeList);

/// ȡ�����ж�����Ϣ
/// @return RetCode     -- �������
RetCode GTA_API_EXPORT _CDECL ExUnsubscribeAll();

/// ��ѯ�Ͻ�����̬����
/// @param  msgCategory -- ��Ҫ��ѯ�����ݷ���
/// @param  pCodeList   -- ���ɶ����б��ԡ�,���ָĩβ������\0������������ΪNULL
/// @param  SnapData    -- ���������б������ExReleaseQuerySnap�ͷ��ڴ�
/// @param  pSize       -- �������ݸ���
/// @return RetCode     -- �������
RetCode GTA_API_EXPORT _CDECL ExQuerySnap(DataCategory msgCategory, char* pCodeList, CQuotationDataPtr** ppSnapData, int* pSize);

/// �ͷŲ�ѯ���շ��ض����ڴ�
/// @param  ppSnapData         -- �����ڴ�ָ��ExQuerySnap���ص��ڴ�
void GTA_API_EXPORT _CDECL ExReleaseQuerySnap(CQuotationDataPtr** ppSnapData);

/// ��ȡ��Ʊ�б�
/// @param  pMarketTag  -- �г���ʶ���ԡ�,���ָ����г���ʶ��ĩβ������\0������������ΪNULL
/// @param  StockList   -- ���صĸ��ɴ����б����г���־�������ExReleaseValue�ͷ��ڴ�
/// @param  pSize       -- �������ݸ���
/// @return RetCode     -- �������
RetCode GTA_API_EXPORT _CDECL ExGetStockList(char* pMarketTag, StockSymbol** ppStockList, int* pSize);

/// �ͷŶ����ڴ�
/// @param  ppDataValue         -- ���ͷ��ڴ�
void GTA_API_EXPORT _CDECL ExReleaseValue(void** ppDataValue);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// ���ֶ���ֵ�ӿ�

/// �ֶθ���
/// @param   pQuotationData -- ��������ָ��
/// @return                 -- �ֶθ���
int GTA_API_EXPORT _CDECL GetField_Count(void* pQuotationData);

//////////////////////////////////////////////////////////////////////
/// �����ֶ�ID��ȡ����
/// @param   pQuotationData -- ��������ָ��
/// @param  FieldID FID     -- �ֶ�ID��־
/// @return void*           -- IFieldValueָ�룬ͨ����ָ���ȡ�ڲ���ֵ
GTA_API_EXPORT void* _CDECL GetField_Value(void* pQuotationData, FieldID FID);

//////////////////////////////////////////////////////////////////////
/// ��˳���ȡ�ֶ�����

/// ����Ϊ��ʵ�ֶ�λ��
/// @param   pQuotationData -- ��������ָ��
/// @return void*           -- IFieldValueָ�룬ͨ����ָ���ȡ�ڲ���ֵ
GTA_API_EXPORT void* _CDECL GetField_First(void* pQuotationData);
/// ����һ���ֶ�
/// @param   pQuotationData -- ��������ָ��
/// @return void*           -- IFieldValueָ�룬ͨ����ָ���ȡ�ڲ���ֵ
GTA_API_EXPORT void* _CDECL GetField_Next(void* pQuotationData);

//////////////////////////////////////////////////////////////////////
/// �������±��������
/// �����±��ȡIFieldValue�е�ֵ
/// @param   pQuotationData -- ��������ָ��
/// @param  int nIndex      -- �±�����
/// @return void*           -- IFieldValueָ�룬ͨ����ָ���ȡ�ڲ���ֵ
GTA_API_EXPORT void* _CDECL GetField_Subscript(void* pQuotationData, int nIndex);


//////////////////////////////////////////////////////////////////////
/// ����IFieldValue��ȡ�ڲ���ֵ

/// ��ȡ��������
/// @param   pIFieldValue       -- IFieldValueָ�룬ͨ����ָ���ȡ�ڲ���ֵ
/// @return  FieldID            -- �ֶ�ID��־
FieldID GTA_API_EXPORT _CDECL Field_FID(void* pIFieldValue);
/// ��ȡ��������
/// @param   pIFieldValue       -- IFieldValueָ�룬ͨ����ָ���ȡ�ڲ���ֵ
/// @return  FIELD_TYPE         -- �ֶ���������
FIELD_TYPE GTA_API_EXPORT _CDECL Field_Type(void* pIFieldValue);

/// ��ȡchar������ֵ
/// @param   pIFieldValue       -- IFieldValueָ�룬ͨ����ָ���ȡ�ڲ���ֵ
/// @param  cValue          -- ������ֵ
/// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
bool GTA_API_EXPORT _CDECL Field_Char(void* pIFieldValue, char* cValue);

/// ��ȡshort������ֵ
/// @param   pIFieldValue       -- IFieldValueָ�룬ͨ����ָ���ȡ�ڲ���ֵ
/// @param  nValue          -- ������ֵ
/// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
bool GTA_API_EXPORT _CDECL Field_Short(void* pIFieldValue, short* nValue);

/// ��ȡusigned int������ֵ
/// @param   pIFieldValue       -- IFieldValueָ�룬ͨ����ָ���ȡ�ڲ���ֵ
/// @param  nValue          -- ������ֵ
/// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
bool GTA_API_EXPORT _CDECL Field_UInt(void* pIFieldValue, unsigned int* nValue);

/// ��ȡint������ֵ
/// @param   pIFieldValue       -- IFieldValueָ�룬ͨ����ָ���ȡ�ڲ���ֵ
/// @param  nValue          -- ������ֵ
/// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
bool GTA_API_EXPORT _CDECL Field_Int(void* pIFieldValue, int* nValue);

/// ��ȡ�ַ���������ֵ
/// @param   pIFieldValue       -- IFieldValueָ�룬ͨ����ָ���ȡ�ڲ���ֵ
/// @param  pValue          -- �ַ�������
/// @param  nSize           -- �ַ�����С����С��ʵ�ʴ�С���򷵻�ʵ�ʴ�С������ʧ��
/// @return true -- ��ȷ�������ݣ� false -- �������ʹ��󣬻��ַ�����С����
bool GTA_API_EXPORT _CDECL Field_String(void* pIFieldValue, char* pValue, unsigned int* nSize);

/// ��ȡlonglong�ַ�������ֵ
/// @param   pIFieldValue       -- IFieldValueָ�룬ͨ����ָ���ȡ�ڲ���ֵ
/// @param  llValue         -- ������ֵ
/// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
bool GTA_API_EXPORT _CDECL Field_Longlong(void* pIFieldValue, long long* llValue);

/// ��ȡunsigned longlong�ַ�������ֵ
/// @param   pIFieldValue       -- IFieldValueָ�룬ͨ����ָ���ȡ�ڲ���ֵ
/// @param  llValue         -- ������ֵ
/// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
bool GTA_API_EXPORT _CDECL Field_ULonglong(void* pIFieldValue, unsigned long long* llValue);

/// ��ȡfloat������ֵ
/// @param   pIFieldValue       -- IFieldValueָ�룬ͨ����ָ���ȡ�ڲ���ֵ
/// @param  fValue          -- ������ֵ
/// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
bool GTA_API_EXPORT _CDECL Field_Float(void* pIFieldValue, float* fValue);


/// ��ȡdouble������ֵ
/// @param   pIFieldValue       -- IFieldValueָ�룬ͨ����ָ���ȡ�ڲ���ֵ
/// @param  dbValue         -- ������ֵ
/// @return true -- ��ȷ�������ݣ� false -- �������ʹ���
bool GTA_API_EXPORT _CDECL Field_Double(void* pIFieldValue, double* dbValue);

/// ��ȡqueue������ֵ
/// @param   pIFieldValue       -- IFieldValueָ�룬ͨ����ָ���ȡ�ڲ���ֵ
/// @param  Queue          -- ���е�ַ
/// @param  nSize           -- �����ܴ�ŵ����ݸ���
/// @return true -- ��ȷ�������ݣ� false -- �������ʹ��󣬻��ַ�����С����
bool GTA_API_EXPORT _CDECL Field_Queue(void* pIFieldValue, unsigned int* Queue, unsigned int* size);


};
#endif // GTA_QTS_INTERFACE_EX_C_H_

//////////////////////////////////////////////////////////////////////////////
/// @file       GTAQTSInterfaceExC.h 
/// @brief      扩展行情接口定义，按字段查询返回数据内容，自动重连
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
/// 实时数据、连接状态回调接口，按字段返回数据

/// 登陆状态返回
/// @param  errCode  -- 失败原因(用户过期、重复登陆)用户需对这两个进行处理
typedef void (*OnExLoginState)( RetCode errCode);
void GTA_API_EXPORT _CDECL SetOnExLoginState(OnExLoginState cbOnExLoginState);

/// 连接状态返回，连接成功/失败
/// @param  msgType      -- 消息类型
/// @param  errCode     -- 失败原因，成功时返回0
typedef void (*OnExConnectionState)(MsgType msgType, RetCode errCode);
void GTA_API_EXPORT _CDECL SetOnExConnectionState(OnExConnectionState cbOnExConnectionState);

/// 会话标志失效（即在AIP中已经没有使用）
/// @param  pSessionTag    -- 会话标志
typedef void (*OnExSessionTagInvalid)(void* pSessionTag);
void GTA_API_EXPORT _CDECL SetOnExSessionTagInvalid(OnExSessionTagInvalid cbOnExSessionTagInvalid);

/// 订阅数据实时回调接口
/// @param  msgCategory -- 返回的数据分类
/// @param  RealData    -- 实时数据
/// @param  pSessionTag -- 订阅数据时传入的用户标志
typedef void (*OnExSubscribe)(const DataCategory msgCategory, CQuotationDataPtr* RealData, void*  pSessionTag);
void GTA_API_EXPORT _CDECL SetOnExSubscribe(OnExSubscribe cbOnExSubscribe);


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 行情系统服务接口，连接服务器进行认证，订阅数据，查询快照.

/// 扩展API环境初始化
void GTA_API_EXPORT _CDECL ExInit();

/// 扩展API环境反初始化
void GTA_API_EXPORT _CDECL ExUninit();

/// 设置超时时间，设置即时生效，同步调用的超时时间
/// @param  nSenond     -- 超时时间，单位秒
void GTA_API_EXPORT _CDECL ExSetTimeout(int nSecond = TIMEOUT_DEFAULT);

/// 注册行情服务器地址，可注册多个不同地址，实现高可用，连接顺序为顺序连接，断线时先重连当前使用地址
/// @param  pIP         -- 服务器地址.
/// @param  uPort       -- 服务器端口.
/// @return RetCode     -- 错误代码
RetCode GTA_API_EXPORT _CDECL ExRegisterService(const char* pIP, unsigned short uPort);

/// 连接行情服务器，发送用户认证信息，同步请求，调用前需先
/// @param  pUserName   -- 账号名称
/// @param  pPassword   -- 账号密码，加密后密码
/// @return RetCode     -- 错误代码
RetCode GTA_API_EXPORT _CDECL ExLogin(const char* pUserName, const char* pPassword);

/// 获取行情订阅服务器地址信息
/// @param  ServerAddrs -- 存放服务器地址对象，需调用ExReleaseValue释放内存
/// @param  pSize       -- 返回数据个数
/// @return RetCode     -- 错误代码
RetCode GTA_API_EXPORT _CDECL ExGetServerAddr(ServerState** ppServerAddrs, int* pSize);

/// 获取有权限的数据类型.
/// @param  ppDataTypeList  -- 数据类型指针，数据大小即为有权限的数据个数，需调用ExReleaseValue释放内存
/// @param  pSize           -- 返回数据个数
/// @return RetCode         -- 错误代码
RetCode GTA_API_EXPORT _CDECL ExGetMsgTypeList(MsgType** ppDataTypeList, int* pSize);


/// 订阅行情，重复订阅同一个数据多次时取并集
/// @param  msgCategory -- 需要订阅的数据分类
/// @param  pCodeList   -- 个股订阅列表，以“,”分割，末尾必须以\0结束，不允许为NULL
/// @param  pSessionTag -- 会话标志,回调参数，在OnSubscribe时返回该数值
/// @return RetCode     -- 错误代码
RetCode GTA_API_EXPORT _CDECL ExSubscribe(DataCategory msgCategory, char* pCodeList, void*  pSessionTag);

/// 根据数据分类、用户标识和代码列表取消订阅
/// @param  msgCategory -- 取消订阅的数据分类
/// @param  pCodeList   -- 取消个股列表，以“,”分割，末尾必须以\0结束
/// @param  pSessionTag -- 会话标志,取消该标志关联的所有订阅
/// @return RetCode     -- 错误代码
RetCode GTA_API_EXPORT _CDECL ExUnsubscribe(DataCategory msgCategory, char* pCodeList, void*  pSessionTag);

/// 根据数据分类和代码列表取消订阅
/// @param  msgCategory -- 取消订阅的数据分类
/// @param  pCodeList   -- 取消个股列表，以“,”分割，末尾必须以\0结束
/// @return RetCode     -- 错误代码
RetCode GTA_API_EXPORT _CDECL ExUnsubscribeByCategory(DataCategory msgCategory, char* pCodeList);

/// 根据会话标志和代码列表取消订阅
/// @param  pSessionTag -- 会话标志,取消该标志关联的所有订阅
/// @param  pCodeList   -- 取消个股列表，以“,”分割，末尾必须以\0结束
/// @return RetCode     -- 错误代码
RetCode GTA_API_EXPORT _CDECL ExUnsubscribeBySessionTag(void*  pSessionTag, char* pCodeList);

/// 取消所有订阅信息
/// @return RetCode     -- 错误代码
RetCode GTA_API_EXPORT _CDECL ExUnsubscribeAll();

/// 查询上交所静态数据
/// @param  msgCategory -- 需要查询的数据分类
/// @param  pCodeList   -- 个股订阅列表，以“,”分割，末尾必须以\0结束，不允许为NULL
/// @param  SnapData    -- 快照数据列表，需调用ExReleaseQuerySnap释放内存
/// @param  pSize       -- 返回数据个数
/// @return RetCode     -- 错误代码
RetCode GTA_API_EXPORT _CDECL ExQuerySnap(DataCategory msgCategory, char* pCodeList, CQuotationDataPtr** ppSnapData, int* pSize);

/// 释放查询快照返回对象内存
/// @param  ppSnapData         -- 快照内存指针ExQuerySnap返回的内存
void GTA_API_EXPORT _CDECL ExReleaseQuerySnap(CQuotationDataPtr** ppSnapData);

/// 获取股票列表
/// @param  pMarketTag  -- 市场标识，以“,”分割多个市场标识，末尾必须以\0结束，不允许为NULL
/// @param  StockList   -- 返回的个股代码列表，带市场标志，需调用ExReleaseValue释放内存
/// @param  pSize       -- 返回数据个数
/// @return RetCode     -- 错误代码
RetCode GTA_API_EXPORT _CDECL ExGetStockList(char* pMarketTag, StockSymbol** ppStockList, int* pSize);

/// 释放对象内存
/// @param  ppDataValue         -- 需释放内存
void GTA_API_EXPORT _CDECL ExReleaseValue(void** ppDataValue);


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// 按字段数值接口

/// 字段个数
/// @param   pQuotationData -- 行情数据指针
/// @return                 -- 字段个数
int GTA_API_EXPORT _CDECL GetField_Count(void* pQuotationData);

//////////////////////////////////////////////////////////////////////
/// 根据字段ID获取数据
/// @param   pQuotationData -- 行情数据指针
/// @param  FieldID FID     -- 字段ID标志
/// @return void*           -- IFieldValue指针，通过此指针获取内部数值
GTA_API_EXPORT void* _CDECL GetField_Value(void* pQuotationData, FieldID FID);

//////////////////////////////////////////////////////////////////////
/// 按顺序读取字段内容

/// 设置为其实字段位置
/// @param   pQuotationData -- 行情数据指针
/// @return void*           -- IFieldValue指针，通过此指针获取内部数值
GTA_API_EXPORT void* _CDECL GetField_First(void* pQuotationData);
/// 下移一个字段
/// @param   pQuotationData -- 行情数据指针
/// @return void*           -- IFieldValue指针，通过此指针获取内部数值
GTA_API_EXPORT void* _CDECL GetField_Next(void* pQuotationData);

//////////////////////////////////////////////////////////////////////
/// 按数组下标访问数据
/// 根据下标获取IFieldValue中的值
/// @param   pQuotationData -- 行情数据指针
/// @param  int nIndex      -- 下标索引
/// @return void*           -- IFieldValue指针，通过此指针获取内部数值
GTA_API_EXPORT void* _CDECL GetField_Subscript(void* pQuotationData, int nIndex);


//////////////////////////////////////////////////////////////////////
/// 根据IFieldValue获取内部数值

/// 获取数据类型
/// @param   pIFieldValue       -- IFieldValue指针，通过此指针获取内部数值
/// @return  FieldID            -- 字段ID标志
FieldID GTA_API_EXPORT _CDECL Field_FID(void* pIFieldValue);
/// 获取数据类型
/// @param   pIFieldValue       -- IFieldValue指针，通过此指针获取内部数值
/// @return  FIELD_TYPE         -- 字段数据类型
FIELD_TYPE GTA_API_EXPORT _CDECL Field_Type(void* pIFieldValue);

/// 获取char类型数值
/// @param   pIFieldValue       -- IFieldValue指针，通过此指针获取内部数值
/// @param  cValue          -- 返回数值
/// @return true -- 正确返回数据， false -- 数据类型错误
bool GTA_API_EXPORT _CDECL Field_Char(void* pIFieldValue, char* cValue);

/// 获取short类型数值
/// @param   pIFieldValue       -- IFieldValue指针，通过此指针获取内部数值
/// @param  nValue          -- 返回数值
/// @return true -- 正确返回数据， false -- 数据类型错误
bool GTA_API_EXPORT _CDECL Field_Short(void* pIFieldValue, short* nValue);

/// 获取usigned int类型数值
/// @param   pIFieldValue       -- IFieldValue指针，通过此指针获取内部数值
/// @param  nValue          -- 返回数值
/// @return true -- 正确返回数据， false -- 数据类型错误
bool GTA_API_EXPORT _CDECL Field_UInt(void* pIFieldValue, unsigned int* nValue);

/// 获取int类型数值
/// @param   pIFieldValue       -- IFieldValue指针，通过此指针获取内部数值
/// @param  nValue          -- 返回数值
/// @return true -- 正确返回数据， false -- 数据类型错误
bool GTA_API_EXPORT _CDECL Field_Int(void* pIFieldValue, int* nValue);

/// 获取字符串类型数值
/// @param   pIFieldValue       -- IFieldValue指针，通过此指针获取内部数值
/// @param  pValue          -- 字符串内容
/// @param  nSize           -- 字符串大小，如小于实际大小，则返回实际大小并返回失败
/// @return true -- 正确返回数据， false -- 数据类型错误，或字符串大小错误
bool GTA_API_EXPORT _CDECL Field_String(void* pIFieldValue, char* pValue, unsigned int* nSize);

/// 获取longlong字符类型数值
/// @param   pIFieldValue       -- IFieldValue指针，通过此指针获取内部数值
/// @param  llValue         -- 返回数值
/// @return true -- 正确返回数据， false -- 数据类型错误
bool GTA_API_EXPORT _CDECL Field_Longlong(void* pIFieldValue, long long* llValue);

/// 获取unsigned longlong字符类型数值
/// @param   pIFieldValue       -- IFieldValue指针，通过此指针获取内部数值
/// @param  llValue         -- 返回数值
/// @return true -- 正确返回数据， false -- 数据类型错误
bool GTA_API_EXPORT _CDECL Field_ULonglong(void* pIFieldValue, unsigned long long* llValue);

/// 获取float类型数值
/// @param   pIFieldValue       -- IFieldValue指针，通过此指针获取内部数值
/// @param  fValue          -- 返回数值
/// @return true -- 正确返回数据， false -- 数据类型错误
bool GTA_API_EXPORT _CDECL Field_Float(void* pIFieldValue, float* fValue);


/// 获取double类型数值
/// @param   pIFieldValue       -- IFieldValue指针，通过此指针获取内部数值
/// @param  dbValue         -- 返回数值
/// @return true -- 正确返回数据， false -- 数据类型错误
bool GTA_API_EXPORT _CDECL Field_Double(void* pIFieldValue, double* dbValue);

/// 获取queue队列数值
/// @param   pIFieldValue       -- IFieldValue指针，通过此指针获取内部数值
/// @param  Queue          -- 队列地址
/// @param  nSize           -- 队列能存放的数据个数
/// @return true -- 正确返回数据， false -- 数据类型错误，或字符串大小错误
bool GTA_API_EXPORT _CDECL Field_Queue(void* pIFieldValue, unsigned int* Queue, unsigned int* size);


};
#endif // GTA_QTS_INTERFACE_EX_C_H_

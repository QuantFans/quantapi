CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(QuantApi)

# add the 'lib' dir to cmake's module search path
SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/lib/")
SET(BINARY_DIR "${CMAKE_SOURCE_DIR}/build")
SET(LIBNARY "${CMAKE_SOURCE_DIR}/lib")

SET(COMMON_DIR "${CMAKE_SOURCE_DIR}/quantdigger/message/0_Common")
SET(MSG_TYPE_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/thirdparty/protobuf-2.5.0/include")
SET(ZMQ_CLIENT_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/thirdparty/zeromq-4.0.4/include")
#ADD_DEFINITIONS(-DIGNORE_LOG_ASSERT)  # 取消LOG_ASSERT

IF (WIN32)
    ADD_DEFINITIONS("-std=c++11")
    ADD_DEFINITIONS(-DWIN32) # 这个层面没作用
    SET(LIBS "${CMAKE_SOURCE_DIR}/lib/windows")
    SET(CTP_MD_LIB "${LIBS}/thostmduserapi.lib")
    SET(CTP_TRADER_LIB "${LIBS}/thosttraderapi.lib")
	SET(ZMQ_LIB "${LIBS}/libzmq.lib")
	SET(PROTOBUF_LIB "${LIBS}/libprotobuf.lib")
ELSE()
    list(APPEND CMAKE_CXX_FLAGS "-pthread -std=c++11 ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")
    SET(LIBS "${CMAKE_SOURCE_DIR}/lib/linux")
    SET(CTP_MD_LIB "${LIBS}/libthostmduserapi.so")
    SET(CTP_TRADER_LIB "${LIBS}/libthosttraderapi.so")
	SET(ZMQ_LIB "${LIBS}/libzmq.so")
	SET(PROTOBUF_LIB "${LIBS}/libprotobuf.so")
ENDIF()
# 系统的根目录 
ADD_DEFINITIONS(-DPROJECT_SOURCE_DIR=\\"${CMAKE_SOURCE_DIR}\\")


    
ADD_SUBDIRECTORY(quantapi)
ADD_SUBDIRECTORY(util)

# Use Python interpreter
#FIND_PACKAGE(PythonInterp)
# 还未验证在windows下cxxtest配置能否顺利编译
#IF (UNIX)
    #ADD_SUBDIRECTORY(tests)
#ENDIF()

#rpath
#LD_LIBRARY_PATH
#make install DESTDIR=
SET(CMAKE_SKIP_BUILD_RPATH  FALSE)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE) 
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

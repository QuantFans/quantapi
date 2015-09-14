CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)

FILE(GLOB source
    "./ctp/*.cpp"
    #	"./lts/*.cpp"
    "*.cpp"
    "./gtastock/*.cpp" 
    "./gtafuture/*.cpp" 
)

ADD_LIBRARY (quantapi ${source})

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}
    ${LOG4CXX_INCLUDE_DIR}
    )


TARGET_LINK_LIBRARIES (quantapi
	${CTP_MD_LIB}
	${CTP_TRADER_LIB}
	${LTS_MD_LIB}
	${LTS_TRADER_LIB}
    	${GTA_STOCKMD_LIB}
    	${GTA_MD_LIB}
    	${LOG4CXX_LIB}
    	util
    )

INSTALL (TARGETS quantapi
    DESTINATION "${BINARY_DIR}/lib/")


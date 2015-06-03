CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)

FILE(GLOB source
    "./ctp/*.cpp"
    "*.cpp" 
)

ADD_LIBRARY (trader_api ${source})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})


TARGET_LINK_LIBRARIES (trader_api
	${CTP_MD_LIB}
	${CTP_TRADER_LIB}
    util
    )

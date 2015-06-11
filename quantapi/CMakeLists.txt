CMAKE_MINIMUM_REQUIRED(VERSION 2.6 FATAL_ERROR)

FILE(GLOB source
    "./ctp/*.cpp"
    "*.cpp" 
)

ADD_LIBRARY (quantapi ${source})
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR})


TARGET_LINK_LIBRARIES (quantapi
	${CTP_MD_LIB}
	${CTP_TRADER_LIB}
    util
    )

INSTALL (TARGETS quantapi
    DESTINATION "${BINARY_DIR}/lib/")


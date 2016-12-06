cmake_minimum_required(VERSION 3.4)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)


IF (${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
    SET(CMAKE_CXX_FLAGS
            "-Wall -pedantic -Weverything -Wno-c++98-compat\
            -Wno-c++98-compat-pedantic -Wno-padded -Wno-missing-prototypes\
            -pthread -std=c++14 -stdlib=libc++")

    LINK_LIBRARIES(pthread)

ELSEIF (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")

    SET(CMAKE_CXX_FLAGS "-Wall -pedantic -pthread -std=c++14")

    LINK_LIBRARIES(pthread)

ENDIF()

# 指定生成目标
AUX_SOURCE_DIRECTORY(. DIR_CLIENT)
AUX_SOURCE_DIRECTORY(./../detail/. DIR_DETAIL)
SET(SOURCE ${DIR_CLIENT}  ${DIR_DETAIL})
ADD_LIBRARY(tinyrpc_client ${SOURCE})
TARGET_LINK_LIBRARIES(tinyrpc_client tinyrpc_core)
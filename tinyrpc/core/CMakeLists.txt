cmake_minimum_required(VERSION 3.4)

SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

# 指定生成目标
file(GLOB_RECURSE DEP_HEADERS
        include/*.h
        include/*.hpp)
file(GLOB_RECURSE DIR_DETAIL
        detail/*.h
        detail/*.cc)
AUX_SOURCE_DIRECTORY(. DIR_CORE)
SET(SOURCE ${DIR_CORE}  ${DIR_DETAIL} ${DEP_HEADERS})
SET(FMT
    fmt/format.h
    fmt/format.cc
    fmt/posix.h
    fmt/posix.cc)

IF (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    LINK_LIBRARIES(pthread)
ENDIF()
ADD_LIBRARY(tinyrpc_core ${SOURCE})
ADD_LIBRARY(fmt ${FMT})

TARGET_LINK_LIBRARIES(tinyrpc_core fmt)
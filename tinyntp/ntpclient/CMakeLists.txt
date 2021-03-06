cmake_minimum_required(VERSION 3.4)

# Find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
LINK_DIRECTORIES(${PROJECT_SOURCE_DIR}/lib )

# Instruct CMake to run moc automatically when needed.
SET(CMAKE_AUTOMOC ON)
# Find the QtWidgets library
FIND_PACKAGE(Qt5Widgets)


IF (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
    SET(CMAKE_CXX_FLAGS "-Wall -pedantic -pthread -std=c++14")
    LINK_LIBRARIES(pthread)
ELSEIF (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
    ADD_DEFINITIONS(-DWIN32_LEAN_AND_MEAN -DNOMINMAX -DVC_EXTRALEAN -D_CRT_NONSTDC_NO_DEPRECATE -D_CRT_SECURE_NO_WARNINGS -D_CRT_NON_CONFORMING_SWPRINTFS -D_CRT_SECURE_NO_DEPRECATE -D_WIN32_WINNT=0x0501 -D_WIN32_WINNT=0x0501 -D_GNU_SOURCE -DASIO_HAS_STD_ADDRESSOF -DASIO_HAS_STD_ARRAY -DASIO_HAS_CSTDINT -DASIO_HAS_STD_SHARED_PTR -DASIO_HAS_STD_TYPE_TRAITS)
ENDIF()

# 指定生成目标

# Set some Win32 Specific Settings
IF(WIN32)
    SET(GUI_TYPE WIN32)
ENDIF(WIN32)

AUX_SOURCE_DIRECTORY(. DIR_SRCS)
ADD_EXECUTABLE(ntp_client ${GUI_TYPE} ${DIR_SRCS})
TARGET_LINK_LIBRARIES(ntp_client tinyrpc_client Qt5::Widgets)
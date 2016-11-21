PROJECT(RAPP_MOVE_BY_SPEACH_NAO_CPP)

cmake_minimum_required(VERSION 2.8.3)

find_package(Rapp REQUIRED)
find_package(Boost COMPONENTS system random REQUIRED)
find_package(RappRobots REQUIRED)
include_directories(${RAPP_INCLUDE_DIRS}/rapp)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${Rapp_DIR})
include(RappMacros)

find_library(PTHREAD NAMES libpthread.so.0 )

setup_rapp()
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11 -Wall -fPIC -static-libstdc++ -mtune=native -march=native")

create_rapp(
    NAME move_by_speach_nao
    SRCS move_by_speach_nao.cpp
    LIBS ${PTHREAD} ${Boost_LIBRARIES} dl
 #   [FILES file1, file2, ...]
)



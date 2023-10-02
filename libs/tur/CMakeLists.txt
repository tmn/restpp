cmake_minimum_required(VERSION 3.27)
project(tur LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)

FetchContent_Declare(curl URL https://curl.se/download/curl-8.3.0.tar.gz)
FetchContent_MakeAvailable(curl)

set(SOURCES
    restclient.cpp
    restclient.h
)

add_library(tur ${SOURCES})

target_link_libraries(tur PUBLIC libcurl)
target_include_directories(tur PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

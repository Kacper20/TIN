cmake_minimum_required(VERSION 3.5)
project(TIN)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Sources/main.cpp Sources/Libraries/jsoncpp.cpp Sources/Libraries/json/json.h Sources/Libraries/json/json-forwards.h)
add_executable(TIN ${SOURCE_FILES})
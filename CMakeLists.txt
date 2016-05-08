cmake_minimum_required(VERSION 3.5)
project(TIN)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES Sources/node/main.cpp Sources/Libraries/jsoncpp.cpp Sources/Libraries/json/json.h Sources/Libraries/json/json-forwards.h Sources/node/WorkerNode.cpp Sources/node/WorkerNode.h Sources/node/NodeNetworkLayer.cpp Sources/node/NodeNetworkLayer.h Sources/Shared/TCPSocket.cpp Sources/Shared/TCPSocket.h Sources/Shared/SocketAddress.cpp Sources/Shared/SocketAddress.h Sources/Shared/OSXSpecificHeaders.h)
add_executable(TIN ${SOURCE_FILES})
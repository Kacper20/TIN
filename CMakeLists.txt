cmake_minimum_required(VERSION 3.5)
project(TIN)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

set(SHARED_FILES Sources/Libraries/jsoncpp.cpp Sources/Libraries/json/json.h Sources/Libraries/json/json-forwards.h
        Sources/Shared/TCPSocket.cpp Sources/Shared/TCPSocket.h Sources/Shared/SocketAddress.cpp
        Sources/Shared/SocketAddress.h Sources/Shared/OSXSpecificHeaders.h Sources/Shared/Commands/Command.cpp
        Sources/Shared/Commands/Command.h Sources/Shared/Commands/AddProcessCommand.cpp
        Sources/Shared/Commands/AddProcessCommand.h Sources/Shared/JSONConstants.h
        Sources/Shared/MessageNetworkManager.cpp Sources/Shared/MessageNetworkManager.h
        Sources/Shared/MessagesQueue.h
        Sources/Shared/FileManager.h Sources/Shared/FileManager.cpp
        Sources/Shared/Responses/Response.cpp Sources/Shared/Responses/Response.h)

set(NODE_SOURCE ${SHARED_FILES} Sources/Node/main.cpp  Sources/Node/WorkerNode.cpp Sources/Node/WorkerNode.h
        Sources/Node/NodeNetworkLayer.cpp Sources/Node/NodeNetworkLayer.h Sources/Node/ProcessHandler.cpp
        Sources/Node/ProcessHandler.h Sources/Node/CommandsDeserializer.cpp Sources/Node/CommandsDeserializer.h
        Sources/Node/NodeServer.cpp Sources/Node/NodeServer.h Sources/Node/CommandDispatcher.h
        Sources/Node/CommandDispatcher.cpp)

set(SERVER_SOURCE ${SHARED_FILES} Sources/Server/main.cpp Sources/Server/ServerNetworkLayer.h
        Sources/Server/ServerNetworkLayer.cpp)

set(ADMIN_SOURCE ${SHARED_FILES} Sources/Administrator/main.cpp )

add_executable(Node ${NODE_SOURCE})

add_executable(Server ${SERVER_SOURCE})

add_executable(Administrator ${ADMIN_SOURCE})
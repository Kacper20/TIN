cmake_minimum_required(VERSION 3.5)
project(TIN)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -I usr/lib/include/boost")

set(SHARED_FILES Sources/Libraries/jsoncpp.cpp Sources/Libraries/json/json.h Sources/Libraries/json/json-forwards.h
        Sources/Shared/TCPSocket.cpp Sources/Shared/TCPSocket.h Sources/Shared/SocketAddress.cpp
        Sources/Shared/SocketAddress.h Sources/Shared/OSXSpecificHeaders.h Sources/Shared/Commands/Command.cpp
        Sources/Shared/Commands/Command.h Sources/Shared/Commands/StartProcessCommand.cpp
        Sources/Shared/Commands/StartProcessCommand.h Sources/Shared/JSONConstants.h
        Sources/Shared/MessageNetworkManager.cpp Sources/Shared/MessageNetworkManager.h
        Sources/Shared/MessagesQueue.h
        Sources/Shared/FileManager.h Sources/Shared/FileManager.cpp
        Sources/Shared/Responses/Response.cpp Sources/Shared/Responses/Response.h
        Sources/Shared/Responses/StartProcessResponse.cpp Sources/Shared/Responses/StartProcessResponse.h
        Sources/Shared/Commands/StartProcessWithScheduleCommand.cpp Sources/Shared/Commands/StartProcessWithScheduleCommand.h
        Sources/Shared/Schedule/Schedule.cpp Sources/Shared/Schedule/Schedule.h)

set(NODE_SOURCE ${SHARED_FILES} Sources/Node/main.cpp  Sources/Node/WorkerNode.cpp Sources/Node/WorkerNode.h
        Sources/Node/NodeNetworkLayer.cpp Sources/Node/NodeNetworkLayer.h Sources/Node/ProcessHandler.cpp
        Sources/Node/ProcessHandler.h Sources/Node/CommandsDeserializer.cpp Sources/Node/CommandsDeserializer.h
        Sources/Node/NodeServer.cpp Sources/Node/NodeServer.h Sources/Node/CommandDispatcher.h
        Sources/Node/CommandDispatcher.cpp Sources/Shared/Responses/ScheduledProcessEndedResponse.cpp Sources/Shared/Responses/ScheduledProcessEndedResponse.h Sources/Node/PathConstants.h)

set(SERVER_SOURCE ${SHARED_FILES} Sources/Server/main.cpp Sources/Server/ServerNetworkLayer.h
        Sources/Server/ServerNetworkLayer.cpp Sources/Server/Server.h Sources/Server/AdminListener.h
        Sources/Server/NodeSender.h Sources/Server/NodeListener.h Sources/Server/AdminSender.h Sources/Server/Server.cpp Sources/Server/AdminListener.cpp Sources/Server/NodeSender.cpp Sources/Server/NodeListener.cpp Sources/Server/AdminSender.cpp)

set(ADMIN_SOURCE ${SHARED_FILES} Sources/Administrator/main.cpp  Sources/Administrator/InputHandler.cpp Sources/Administrator/InputHandler.h Sources/Administrator/AdministratorNetworkLayer.cpp Sources/Administrator/AdministratorNetworkLayer.h)

add_executable(Node ${NODE_SOURCE})

add_executable(Server ${SERVER_SOURCE})

add_executable(Administrator ${ADMIN_SOURCE})
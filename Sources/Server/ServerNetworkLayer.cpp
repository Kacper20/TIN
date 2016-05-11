//
// Created by Rafał Rzeuski on 09.05.16.
//

#include "ServerNetworkLayer.h"
#include <iostream>

int ServerNetworkLayer::connectToNode() {
    TCPSocket socket;
    SocketAddress nodeAddress;
    // No local port binding needed, just connect(...)
    if(socket.connect(socket.internalDescriptor(), nodeAddress) == -1) {
        std::cout << "Failed to connect to target address!" << std::endl;
    }

}


//
// Created by Rafał Rzeuski on 09.05.16.
//

#include "ServerNetworkLayer.h"
#include "../Libraries/json/json.h"
#include <iostream>

int ServerNetworkLayer::connectToNode(const std::string addressWithPort) {
    nodeConnectionSocket = new TCPSocket();
    SocketAddress nodeAddress(addressWithPort);
    // No local port binding needed, just connect(...)
    if(nodeConnectionSocket->connect(nodeConnectionSocket->internalDescriptor(), nodeAddress) == -1) {
        std::cerr << "Failed to connect to target address!";
        return -1;
    }
    return 0;
}

int ServerNetworkLayer::sendScript(const std::string filename) const {
    if(nodeConnectionSocket == nullptr) {
        std::cerr << "There is no node to send the data to!";
        return -1;
    }
    //TODO: load script from file
    Json::Value value;
    // In reverse order, because StyledWriter.write writes them in reverse, I think
    value["text"] = "echo \'Imagination is the essence to discovery.\'";
    value["type"] = "script";
    Json::StyledWriter writer;
    std::string message = writer.write(value);
    //TODO: should we send the size of the message first, then the message itself?
    std::cout << "Message going out!" << std::endl << message << std::endl;
    int bytesSent = nodeConnectionSocket->send(message);
    std::cout << "Sent " << bytesSent << " bytes" << std::endl;

    return 0;
}
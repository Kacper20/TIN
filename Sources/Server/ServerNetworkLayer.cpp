//
// Created by Rafał Rzeuski on 09.05.16.
//

#include "ServerNetworkLayer.h"
#include "../Libraries/json/json.h"
#include <iostream>
#include <string>

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
    // Prepare our JSON
    Json::Value value;
    Json::Value processDetails;
    processDetails["content"] = "echo \'Imagination is the essence of discovery.\'";
    value["messageType"] = "startNewProcess";
    value["processDetails"] = processDetails;
    // Make a c++ string object out of it
    std::string message;
    Json::StyledWriter writer;
    message = writer.write(value);
    std::cout << message << std::endl;
    //TODO: Send the size of the message first
    // Count the size of the message
    long messageSizeInt = message.size();
    // Our TCPSocket.send method currently only accepts string, so that's what we will send
    std::string messageSizeStr;
    messageSizeStr += std::to_string(messageSizeInt);
    std::cout << messageSizeStr << std::endl;
    // Send the size of the message and get the number of bytes sent, will be useful for checking if any errors occurred
    //TODO: error checking
    int bytesSent = nodeConnectionSocket->send(message);
    // Send the message
    bytesSent = nodeConnectionSocket->send(message);

    return 0;
}
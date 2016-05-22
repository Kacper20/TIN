//
// Created by Rafał Rzeuski on 09.05.16.
//

#include "ServerNetworkLayer.h"
#include "../Libraries/json/json.h"
#include <iostream>
#include <string>


//ServerNetworkLayer::ServerNetworkLayer() {
//  TCPSocket s = TCPSocket();
//  nodeConnectionSocket = s;
//  networkManager = MessageNetworkManager(s);
//}

int ServerNetworkLayer::connectToNodes(const std::string addressWithPort) {
  SocketAddress nodeAddress(addressWithPort);
  // No local port binding needed, just connect(...)
  if (nodeConnectionSocket.connect(nodeConnectionSocket.internalDescriptor(), nodeAddress) == -1) {
    perror("Failed to connect target address");
    return -1;
  }
  return 0;
}

int ServerNetworkLayer::sendMessage(const std::string message) const {
  std::cout << "Sending message: " << message << std::endl;
  return networkManager.sendMessage(message);
}
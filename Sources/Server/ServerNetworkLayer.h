//
// Created by Rafał Rzeuski on 09.05.16.
//

#ifndef TIN_SERVERNETWORKLAYER_H
#define TIN_SERVERNETWORKLAYER_H

#include "../Shared/TCPSocket.h"
#include "../Shared/MessageNetworkManager.h"

class ServerNetworkLayer {
 private:
  //TODO: Change this to some sort of container of sockets, so we can connect to multiple sockets at once
  TCPSocket nodeConnectionSocket;
  MessageNetworkManager networkManager;

 public:
  ServerNetworkLayer() : nodeConnectionSocket(), networkManager(nodeConnectionSocket) {}
  int connectToNodes(const std::string addressWithPort);
  int sendMessage(const std::string message) const;
};

#endif //TIN_SERVERNETWORKLAYER_H

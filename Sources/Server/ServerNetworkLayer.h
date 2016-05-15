//
// Created by Rafał Rzeuski on 09.05.16.
//

#ifndef TIN_SERVERNETWORKLAYER_H
#define TIN_SERVERNETWORKLAYER_H

#include "../Shared/TCPSocket.h"
#include "../Shared/MessageNetworkManager.h"

class ServerNetworkLayer {
 private:
  TCPSocket nodeConnectionSocket;
  MessageNetworkManager networkManager;

 public:
  ServerNetworkLayer() : nodeConnectionSocket(TCPSocket()), networkManager(nodeConnectionSocket) {}
  int connectToNode(const std::string addressWithPort);
  int sendMessage(const std::string message) const;
};

#endif //TIN_SERVERNETWORKLAYER_H

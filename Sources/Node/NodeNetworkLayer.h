//
// Created by Kacper Harasim on 08.05.2016.
//
#include "../Shared/TCPSocket.h"
#include "../Shared/MessageNetworkManager.h"

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <functional>

#ifndef TIN_NODENETWORKLAYER_H
#define TIN_NODENETWORKLAYER_H

#define NETWORK_PORT 46027


class NodeNetworkLayer {

 private:
  TCPSocket listeningSocket = TCPSocket();
  MessageNetworkManager networkManager;
  TCPSocket* clientConnectedSocket;
 public:

  NodeNetworkLayer(): networkManager(MessageNetworkManager(listeningSocket)) {}
  ~NodeNetworkLayer();
  void listenOnServerConnection();
  void startReceivingMessages(std::function<void(std::string)> messageReceivedCompletion);
  int sendMessage(const std::string message) const;

};


#endif //TIN_NODENETWORKLAYER_H

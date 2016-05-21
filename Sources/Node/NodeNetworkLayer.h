//
// Created by Kacper Harasim on 08.05.2016.
//


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../Shared/TCPSocket.h"
#include "../Shared/MessageNetworkManager.h"
#include <iostream>


#ifndef TIN_NODENETWORKLAYER_H
#define TIN_NODENETWORKLAYER_H

#define NETWORK_PORT 46027


class NodeNetworkLayer {

 private:
  TCPSocket listeningSocket = TCPSocket();
  TCPSocket* clientConnectedSocket;
 public:

  ~NodeNetworkLayer();
  void listenOnServerConnection();
  void startReceivingMessages(std::function<void(std::string)> messageReceivedCompletion);

};


#endif //TIN_NODENETWORKLAYER_H

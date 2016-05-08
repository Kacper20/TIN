//
// Created by Kacper Harasim on 08.05.2016.
//

#include "NodeNetworkLayer.h"
void NodeNetworkLayer::startListeningOnRequests() {

  TCPSocket socket = TCPSocket();
  SocketAddress myAddress = SocketAddress();
  socket.bind(myAddress);
}

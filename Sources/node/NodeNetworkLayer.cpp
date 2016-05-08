//
// Created by Kacper Harasim on 08.05.2016.
//

#include "NodeNetworkLayer.h"
void NodeNetworkLayer::startListeningOnRequests() {

  //TODO: Add error handling.
  TCPSocket socket = TCPSocket();
  SocketAddress myAddress = SocketAddress();
  socket.bind(myAddress);
  socket.listen(1);
  TCPSocket newSocket = socket.accept();
  this->clientConnectionSocket = &newSocket;
  //Close socket that was listening
  socket.close();
}

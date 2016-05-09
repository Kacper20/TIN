//
// Created by Kacper Harasim on 08.05.2016.
//

#include "NodeNetworkLayer.h"
void NodeNetworkLayer::startListeningOnRequests() {

  TCPSocket socket = TCPSocket();
  SocketAddress myAddress = SocketAddress();
  std::cout << "Binding socket to address";
  if (socket.bind(myAddress) == -1) {
    perror("Error while binding occured");
  }
  std::cout <<"Binded successfuly";
  if (socket.listen(1) == -1 ) {
    perror("Error while listening occured");
  }
  std::cout << "Listen called";
  TCPSocket newSocket = socket.accept();
  if (newSocket.internalDescriptor() == -1) {
    perror("Error while accepting connection");
  }
  std::cout << "Accepted connection";
  this->clientConnectionSocket = &newSocket;
  //Close socket that was listening
  socket.close();
}

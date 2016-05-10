//
// Created by Kacper Harasim on 08.05.2016.
//

#include "NodeNetworkLayer.h"
void NodeNetworkLayer::startListeningOnRequests() {

  TCPSocket socket = TCPSocket();
  SocketAddress myAddress = SocketAddress();
  std::cout << "Binding socket to address\n";
  if (socket.bind(myAddress) == -1) {
    perror("Error while binding occured");
  }
  std::cout <<"Binded successfuly\n";
  if (socket.listen(1) == -1 ) {
    perror("Error while listening occured");
  }
  std::cout << "Listen called\n";
  TCPSocket newSocket = socket.accept();
  if (newSocket.internalDescriptor() == -1) {
    perror("Error while accepting connection");
  }
  std::cout << "Accepted connection\n";
  //Close socket that was listening
  socket.close();
}

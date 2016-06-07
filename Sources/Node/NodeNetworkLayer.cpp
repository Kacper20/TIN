//
// Created by Kacper Harasim on 08.05.2016.
//

#include "NodeNetworkLayer.h"


NodeNetworkLayer::~NodeNetworkLayer() {
  delete(clientConnectedSocket);
}

void NodeNetworkLayer::listenOnServerConnection() {

  SocketAddress myAddress = SocketAddress(short(portNumber));
  std::cout << "Binding listeningSocket to address\n";
  if (listeningSocket.bind(myAddress) == -1) {
    perror("Error while binding occured");
    exit(-1);
  }
  std::cout <<"Binded successfuly\n";
  if (listeningSocket.listen(1) == -1 ) {
    perror("Error while listening occured");
    exit(-1);
  }
  std::cout << "Listen called\n";
  int newDescriptor = listeningSocket.accept();
  if (newDescriptor == -1) {
    perror("Error while accepting connection");
    exit(-1);
  }
  clientConnectedSocket = new TCPSocket(newDescriptor);

  std::cout << "Accepted connection\n";
  //Close listeningSocket that was listening - we only support one client by design.
  listeningSocket.close();
  std::cout << "Calling completion func" << std::endl;
  return;
}

void NodeNetworkLayer::startReceivingMessages(std::function<void(std::string)> messageReceivedCompletion) {
  MessageNetworkManager manager = MessageNetworkManager(*clientConnectedSocket);
  std::string buffer;
  while(1) {
    ssize_t receivedBytes = manager.receiveMessage(buffer);
    if (receivedBytes < 0) {
      return;
    }
    if (receivedBytes != 0) {
      messageReceivedCompletion(buffer);
    }
  }
}

int NodeNetworkLayer::sendMessage(const std::string message) const {
  MessageNetworkManager manager = MessageNetworkManager(*clientConnectedSocket);
  return manager.sendMessage(message);
}



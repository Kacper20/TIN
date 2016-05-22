//
// Created by Rafal Rzeuski on 5/21/16.
//

#include "AdminListener.h"
#include "../Shared/MessageNetworkManager.h"

#include <iostream>

void AdminListener::operator()() {
  connectToAdmin();

  // Start receiving messages
  MessageNetworkManager manager(*adminSocket);
  std::string buffer;
  while(true) {
    ssize_t messageSize = manager.receiveMessage(buffer);
    if(messageSize < 0) {
      //Something's wrong!
      continue;
    }
    // Put the message into outgoing queue
    std::shared_ptr<std::string> message(new std::string(buffer));
    q.push(message);
  }
}

void AdminListener::connectToAdmin() {
  //TODO: Error checking, bool return value for success checking
  SocketAddress myAddress("127.0.0.1:1666"); // temporary
  TCPSocket listeningSocket;
  listeningSocket.bind(myAddress);
  listeningSocket.listen(1);
  int newDescriptor = listeningSocket.accept();
  adminSocket = new TCPSocket(newDescriptor);
  listeningSocket.close();
}
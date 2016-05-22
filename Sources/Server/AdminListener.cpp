//
// Created by Rafal Rzeuski on 5/21/16.
//

#include "AdminListener.h"
#include "../Shared/MessageNetworkManager.h"

#include <iostream>
#include <chrono>
#include <thread>

void AdminListener::operator()() {
  waitForAdminToConnect();

  // Start receiving messages
  MessageNetworkManager manager(*adminSocket);
  std::string buffer;
  while(true) {
    std::cout << "AdminListener!\n";
    std::chrono::duration<int> s(2);
    std::this_thread::sleep_for(s);

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

void AdminListener::waitForAdminToConnect() {
  //TODO: Error checking, bool return value for success checking
  TCPSocket listeningSocket;
  SocketAddress myAddress = SocketAddress("127.0.0.1:1666");
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
  adminSocket = new TCPSocket(newDescriptor);

  std::cout << "Accepted connection\n";
  //Close listeningSocket that was listening - we only support one client by design.
  listeningSocket.close();
  std::cout << "Calling completion func" << std::endl;
  return;
}
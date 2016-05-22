//
// Created by Rafal Rzeuski on 5/22/16.
//

#include "NodeListener.h"
#include "../Shared/MessageNetworkManager.h"

#include <memory>
#include <iostream>
#include <thread>

void NodeListener::operator()() {
  // TODO: Make this a loop that checks all Node sockets for messages using non-blocking read()
  // I should probably change the sockets used for talking with Nodes to be non-blocking when I first set them up
  // That would require adjusting the MessageNetworkManager class a a bit
  // Ooor use the select() function and decide which sockets to ask for stuff based on its results

  // ...

  // But for now, since we only have one socket, let's just ask it to send us some stuff:
  MessageNetworkManager manager(nodeSocket);
  std::string buffer;
  while(true) {

    std::cout << "NodeListener!\n";
    std::chrono::duration<int> s(2);
    std::this_thread::sleep_for(s);

    ssize_t messageSize = manager.receiveMessage(buffer, true);
    if(messageSize < 0) {
      // TODO: error checking
      continue;
    }
    if(messageSize != 0) {
      std::cout << "NodeListener, message received : " << buffer << std::endl;
      // Put the message into the queue
      std::shared_ptr<std::string> message(new std::string(buffer));
      q.push(message);
    }
  }
}
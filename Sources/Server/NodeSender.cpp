//
// Created by Rafal Rzeuski on 5/22/16.
//

#include "NodeSender.h"
#include "../Shared/MessageNetworkManager.h"

void NodeSender::operator()() {
  MessageNetworkManager manager(nodeSocket);
  while(true) {
    // MessagesQueue does all the concurrency work for us - no need to worry about it
    std::shared_ptr<std::string> message = q.pop();
    // TODO: Decide which Node we should send the message to!
    if(message) {
      manager.sendMessage(*message);
    }
  }
}
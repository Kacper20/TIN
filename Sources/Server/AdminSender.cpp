//
// Created by Rafal Rzeuski on 5/22/16.
//

#include "AdminSender.h"
#include "../Shared/MessageNetworkManager.h"

#include <memory>

void AdminSender::operator()() {
  // Wait until adminSocket is not a nullptr, could reimplement this using a condition_variable, because this isn't very good
  while(!adminSocket) {}
  MessageNetworkManager manager(*adminSocket);
  while(true) {
    std::shared_ptr<std::string> message = q.pop();
    if(message) {
      manager.sendMessage(*message);
    }
  }
}
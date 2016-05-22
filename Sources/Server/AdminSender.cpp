//
// Created by Rafal Rzeuski on 5/22/16.
//

#include "AdminSender.h"
#include "../Shared/MessageNetworkManager.h"

#include <memory>
#include <thread>
#include <iostream>

void AdminSender::operator()() {
  // Wait until adminSocket is not a nullptr, could reimplement this using a condition_variable, because this isn't very good
  while(!adminSocket) {
    std::cout << "AdminSender - waiting for socket!\n";
    std::chrono::duration<int> s(2);
    std::this_thread::sleep_for(s);
  }
  MessageNetworkManager manager(*adminSocket);
  while(true) {

    std::cout << "AdminSender!\n";
    std::chrono::duration<int> s(2);
    std::this_thread::sleep_for(s);

    std::shared_ptr<std::string> message = q.pop();
    manager.sendMessage(*message);
  }
}
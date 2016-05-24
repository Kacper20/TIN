//
// Created by Rafal Rzeuski on 5/22/16.
//

#include "AdminSender.h"
#include "../Shared/MessageNetworkManager.h"

#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>

std::condition_variable waitingForConnection;

void AdminSender::operator()() {
  // Wait for the AdminListener thread to connect to the Administrator module
  // But ONLY if the connection hasn't been already established. We need to make sure we won't wait() on this condition
  // variable after the other thread called notify_one()!
  if(!adminSocket) {
    std::mutex m;
    std::unique_lock<std::mutex> lock(m);
    std::cout << "Condition_variable address (Sender) : " << &waitingForConnection << std::endl;
    waitingForConnection.wait(lock);
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
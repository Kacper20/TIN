//
// Created by Rafal Rzeuski on 5/16/16.
// Modified by Daria Danilenko on 20.05.2016
//

#include <iostream>
#include <cstring>
#include "../Shared/SocketAddress.h"
#include <thread>
#include "InputHandler.h"

struct InputHandlingTask {
    InputHandler* handler;
    InputHandlingTask(InputHandler* handler) {
      this->handler = handler;
    }
    void operator() () {
      handler->run();
    }
};


int main(int argc, char* argv[]) {
  InputHandler handler;
  InputHandlingTask inputTask(&handler);
  std::thread inputThread(inputTask);

  inputThread.join();
}

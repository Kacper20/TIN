//
// Created by Kacper Harasim on 15.05.2016.
//

#include <iostream>
#include "CommandDispatcher.h"
#include "../Shared/Commands/StartProcessCommand.h"


void CommandDispatcher::startDispatching() {
  processCommandsInfinitely();
}

void CommandDispatcher::processCommandsInfinitely()  {

  while(1) {
    std::cout << "command WILL be taken from queue\n";
    std::shared_ptr<Command> command = queue.pop();

    std::cout << "command taken from queue\n";
    std::shared_ptr<StartProcessCommand> processCommand = std::static_pointer_cast<StartProcessCommand>(command);
    if (processCommand != nullptr) {
      std::cout << "Received add process command\n";
      std::shared_ptr<StartProcessCommand> commandPtr(processCommand);
      handler.runProcess(commandPtr);
    }
  }
}

void CommandDispatcher::processCommand(std::shared_ptr<Command> command) {
  std::cout << "Command pushed to the queue\n";
  queue.push(command);
}

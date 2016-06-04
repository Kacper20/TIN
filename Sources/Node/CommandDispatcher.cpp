//
// Created by Kacper Harasim on 15.05.2016.
//

#include <iostream>
#include "CommandDispatcher.h"
#include "../Shared/Commands/StartProcessCommand.h"
#include "../Shared/Commands/DeleteProcessCommand.h"


void CommandDispatcher::startDispatching() {
  processCommandsInfinitely();
}

void CommandDispatcher::processCommandsInfinitely()  {

  while(1) {
    std::shared_ptr<Command> command = queue.pop();

    //Start new process command dispatching
    if (command->commandType == CommandType::START_NEW_PROCESS) {
      std::shared_ptr<StartProcessCommand> processCommand = std::static_pointer_cast<StartProcessCommand>(command);
      if (processCommand != nullptr) {
        processInstantRunHandler.runProcess(processCommand);
      }
    }

    if (command->commandType == CommandType::DELETE_PROCESS) {
      std::shared_ptr<DeleteProcessCommand>
          deleteProcessCommand = std::static_pointer_cast<DeleteProcessCommand>(command);
      if (deleteProcessCommand != nullptr) {
        std::cout << "Received delete process command";
        processScheduledRunHandler.removeProcessData(deleteProcessCommand->processId);
        processInstantRunHandler.removeProcessData(deleteProcessCommand->processId);
      }
    }

    if (command->commandType == CommandType::START_NEW_PROCESS_WITH_SCHEDULE) {
      std::shared_ptr<StartProcessWithScheduleCommand>
          processCommand = std::static_pointer_cast<StartProcessWithScheduleCommand>(command);
      if (processCommand != nullptr) {
        processScheduledRunHandler.scheduleProcess(processCommand);
      }
    }
    //TODO: Add other commands.
  }
}

void CommandDispatcher::processCommand(std::shared_ptr<Command> command) {
  std::cout << "Command pushed to the queue\n";
  queue.push(command);
}

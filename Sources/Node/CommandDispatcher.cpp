//
// Created by Kacper Harasim on 15.05.2016.
//

#include <iostream>
#include "CommandDispatcher.h"
#include "../Shared/Commands/StartProcessCommand.h"
#include "../Shared/Commands/DeleteProcessCommand.h"
#include "../Shared/Commands/LaunchProcessCommand.h"
#include "../Shared/Commands/RequestProcessStatisticsCommand.h"


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

    if (command->commandType == CommandType::LAUNCH_PROCESS) {
      std::shared_ptr<LaunchProcessCommand> processCommand = std::static_pointer_cast<LaunchProcessCommand>(command);
      if (processCommand != nullptr) {
        processInstantRunHandler.launchProcess(processCommand);
      }
    }

    if (command->commandType == CommandType::REQUEST_STATISTICS) {
      std::shared_ptr<RequestProcessStatisticsCommand> processCommand = std::static_pointer_cast<RequestProcessStatisticsCommand>(command);
      if (processCommand != nullptr) {
        collector.requestStatisticsForProcess(processCommand->processId);
      }
    }
    if (command->commandType == CommandType::REQUEST_DATA) {
      std::shared_ptr<RequestDataCommand> processCommand = std::static_pointer_cast<RequestDataCommand>(command);
      if (processCommand != nullptr) {

      }
    }


    //TODO: Add other commands.
  }
}

void CommandDispatcher::processCommand(std::shared_ptr<Command> command) {
  std::cout << "Command pushed to the queue\n";
  queue.push(command);
}

//
// Created by Kacper Harasim on 11.05.2016.
//

#ifndef TIN_COMMAND_H
#define TIN_COMMAND_H

#include "../../Libraries/json/json.h"
#include "../JSONConstants.h"

enum class CommandType {
  START_NEW_PROCESS, START_NEW_PROCESS_WITH_SCHEDULE, LAUNCH_PROCESS, DELETE_PROCESS, REQUEST_DATA
};

static std::string descriptionForCommandType(CommandType type) {
  switch (type) {
    case CommandType::START_NEW_PROCESS:
      return JSONConstants::CommandStartNewProcess;
    case CommandType ::START_NEW_PROCESS_WITH_SCHEDULE:
      return JSONConstants::CommandStartNewProcessWithSchedule;
    case CommandType :: LAUNCH_PROCESS:
      return JSONConstants::CommandLaunchProcess;
    case CommandType :: DELETE_PROCESS:
      return JSONConstants::CommandDeleteProcess;
    case CommandType :: REQUEST_DATA:
      return JSONConstants::CommandRequestData;
    }
}

class Command {

 public:
  CommandType commandType;
  Command(CommandType commandType) : commandType(commandType) {}
  virtual Json::Value generateJSON();

};


#endif //TIN_COMMAND_H

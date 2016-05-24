//
// Created by Kacper Harasim on 11.05.2016.
//

#ifndef TIN_COMMAND_H
#define TIN_COMMAND_H

#include "../../Libraries/json/json.h"
#include "../JSONConstants.h"

enum class CommandType {
  START_NEW_PROCESS, START_NEW_PROCESS_WITH_SCHEDULE, LAUNCH_PROCESS
};

static std::string descriptionForCommandType(CommandType type) {
  switch (type) {
    case CommandType::START_NEW_PROCESS:
      return "startNewProcess";
    case CommandType ::START_NEW_PROCESS_WITH_SCHEDULE:
      return "startNewProcessWithSchedule";
    case CommandType :: LAUNCH_PROCESS:
      return "launchProcess";
    }
}

class Command {

 private:
  CommandType commandType;
 public:
  Command(CommandType commandType) : commandType(commandType) {}
  virtual Json::Value generateJSON();

};


#endif //TIN_COMMAND_H

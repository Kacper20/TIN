//
// Created by Kacper Harasim on 11.05.2016.
//

#ifndef TIN_COMMAND_H
#define TIN_COMMAND_H

#include "../../Libraries/json/json.h"
#include "../JSONConstants.h"

enum class CommandType {
  START_NEW_PROCESS
};

static std::string descriptionForCommandType(CommandType type) {
  switch (type) {
    case CommandType::START_NEW_PROCESS:
      return "startNewProcess";
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

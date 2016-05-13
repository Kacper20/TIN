//
// Created by Kacper Harasim on 11.05.2016.
//

#ifndef TIN_COMMAND_H
#define TIN_COMMAND_H

#include "../../Libraries/json/json.h"

enum CommandType {
  NEW_PROCESS
};


class Command {

 private:
  CommandType commandType;
 public:
  Command(CommandType commandType) : commandType(commandType) {}
  virtual json::value generateJSON

};


#endif //TIN_COMMAND_H

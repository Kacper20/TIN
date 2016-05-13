//
// Created by Kacper Harasim on 11.05.2016.
//

#ifndef TIN_ADDPROCESSCOMMAND_H
#define TIN_ADDPROCESSCOMMAND_H
#include "Command.h"


class AddProcessCommand: public Command {

 private:
  std::string processContent;
  CommandType  command
 public:
  AddProcessCommand (Json::Value json);
};


#endif //TIN_ADDPROCESSCOMMAND_H

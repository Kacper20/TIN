//
// Created by Kacper Harasim on 11.05.2016.
//

#ifndef TIN_ADDPROCESSCOMMAND_H
#define TIN_ADDPROCESSCOMMAND_H
#include "Command.h"


class AddProcessCommand: public Command {

 private:

 public:
  std::string processContent;
  AddProcessCommand (Json::Value json);
  AddProcessCommand (std::string processContent);
  Json::Value generateJSON();
};
#endif //TIN_ADDPROCESSCOMMAND_H

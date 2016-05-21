//
// Created by Kacper Harasim on 11.05.2016.
//

#ifndef TIN_ADDPROCESSCOMMAND_H
#define TIN_ADDPROCESSCOMMAND_H
#include "Command.h"


class StartProcessCommand: public Command {

 private:

 public:
  std::string processContent;
  std::string processId;
  StartProcessCommand (Json::Value json);
  StartProcessCommand (std::string processId, std::string processContent): Command(CommandType::START_NEW_PROCESS),
  processId(processId), processContent(processContent) {}
  Json::Value generateJSON();
};
#endif //TIN_ADDPROCESSCOMMAND_H

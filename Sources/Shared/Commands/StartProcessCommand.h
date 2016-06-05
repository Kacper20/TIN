//
// Created by Kacper Harasim on 11.05.2016.
//

#ifndef TIN_ADDPROCESSCOMMAND_H
#define TIN_ADDPROCESSCOMMAND_H
#include "Command.h"

enum class StartType {
  NEW, LAUNCHED
};

class StartProcessCommand: public Command {

 private:

 public:
  StartType startType = StartType::NEW;
  std::string processContent;
  std::string processId;
  StartProcessCommand (Json::Value json);
  StartProcessCommand (std::string processId, std::string processContent): Command(CommandType::START_NEW_PROCESS),
  processId(processId), processContent(processContent) {}
  Json::Value generateJSON();
};
#endif //TIN_ADDPROCESSCOMMAND_H

//
// Created by Kacper Harasim on 21.05.2016.
//

#ifndef TIN_STARTPROCESSWITHSCHEDULECOMMAND_H
#define TIN_STARTPROCESSWITHSCHEDULECOMMAND_H


#include "Command.h"

class StartProcessWithScheduleCommand : public Command {

 private:

 public:
  std::string processContent;
  std::string processId;

  StartProcessWithScheduleCommand (Json::Value json);
  StartProcessWithScheduleCommand (std::string processId, std::string processContent): Command(CommandType::START_NEW_PROCESS),
  processId(processId), processContent(processContent) {}
  Json::Value generateJSON();

};


#endif //TIN_STARTPROCESSWITHSCHEDULECOMMAND_H

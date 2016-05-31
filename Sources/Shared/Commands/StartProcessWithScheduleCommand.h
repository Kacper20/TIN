//
// Created by Kacper Harasim on 21.05.2016.
//

#ifndef TIN_STARTPROCESSWITHSCHEDULECOMMAND_H
#define TIN_STARTPROCESSWITHSCHEDULECOMMAND_H


#include "Command.h"
#include "../Schedule/Schedule.h"

class StartProcessWithScheduleCommand : public Command {

 private:

 public:
  std::string processContent;
  std::string processId;
  Schedule schedule;

  StartProcessWithScheduleCommand (Json::Value json);
  StartProcessWithScheduleCommand (std::string processId, std::string processContent, Schedule schedule): Command(CommandType::START_NEW_PROCESS_WITH_SCHEDULE),
  processId(processId), processContent(processContent), schedule(schedule) {}
  Json::Value generateJSON();

};


#endif //TIN_STARTPROCESSWITHSCHEDULECOMMAND_H

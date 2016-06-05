//
// Created by Kacper Harasim on 05.06.2016.
//

#ifndef TIN_REQUESTNODESTATISTICSCOMMAND_H
#define TIN_REQUESTNODESTATISTICSCOMMAND_H


#include "Command.h"
class RequestProcessStatisticsCommand: public Command {

 private:

 public:
  std::string processId;
  RequestProcessStatisticsCommand (Json::Value json);
  RequestProcessStatisticsCommand (std::string processId): Command(CommandType::REQUEST_STATISTICS),
  processId(processId) {}
  Json::Value generateJSON();
};


#endif //TIN_REQUESTNODESTATISTICSCOMMAND_H

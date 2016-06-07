//
// Created by Kacper Harasim on 05.06.2016.
//

#include "RequestProcessStatisticsCommand.h"

RequestProcessStatisticsCommand::RequestProcessStatisticsCommand(Json::Value json) : Command(CommandType::REQUEST_STATISTICS) {
  Json::Value processDetails = json[JSONConstants::ProcessDetails];
  processId = processDetails[JSONConstants::ProcessIdentifier].asString();
}

Json::Value RequestProcessStatisticsCommand::generateJSON() {
  Json::Value root = Command::generateJSON();
  Json::Value details;
  details[JSONConstants::ProcessIdentifier] = processId;
  root[JSONConstants::ProcessDetails] = details;
  return root;
}
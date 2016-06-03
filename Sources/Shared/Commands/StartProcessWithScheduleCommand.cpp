//
// Created by Kacper Harasim on 21.05.2016.
// modified by dawid
//

#include "StartProcessWithScheduleCommand.h"

#include <algorithm>

StartProcessWithScheduleCommand::StartProcessWithScheduleCommand(Json::Value json):
    Command(CommandType::START_NEW_PROCESS_WITH_SCHEDULE) {

  Json::Value processDetails = json[JSONConstants::ProcessDetails];
  processContent = processDetails[JSONConstants::ProcessContent].asString();
  processId = processDetails[JSONConstants::ProcessIdentifier].asString();
  Json::Value array = processDetails[JSONConstants::SchedulesIdentifier];
  std::vector<int> vectorOfTimestamps;
  std::transform(array.begin(), array.end(), vectorOfTimestamps.begin(), [](Json::Value& elem) { return elem.asInt(); });
  schedule = Schedule(vectorOfTimestamps);
}

Json::Value StartProcessWithScheduleCommand::generateJSON() {
  Json::Value root = Command::generateJSON();
  Json::Value details;
  details[JSONConstants::ProcessContent] = processContent;
  details[JSONConstants::ProcessIdentifier] = processId;
  details[JSONConstants::SchedulesIdentifier] = schedule.generateJson();
  root[JSONConstants::ProcessDetails] = details;
  return root;
}
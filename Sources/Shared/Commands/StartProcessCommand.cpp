//
// Created by Kacper Harasim on 11.05.2016.
//

#include <iostream>
#include "StartProcessCommand.h"

StartProcessCommand::StartProcessCommand(Json::Value json) : Command(CommandType::START_NEW_PROCESS) {
  Json::Value processDetails = json[JSONConstants::ProcessDetails];
  processContent = processDetails[JSONConstants::ProcessContent].asString();
  processId = processDetails[JSONConstants::ProcessIdentifier].asString();
}

Json::Value StartProcessCommand::generateJSON() {
  Json::Value root = Command::generateJSON();
  Json::Value details;
  details[JSONConstants::ProcessContent] = processContent;
  details[JSONConstants::ProcessIdentifier] = processId;
  root[JSONConstants::ProcessDetails] = details;
  return root;
}



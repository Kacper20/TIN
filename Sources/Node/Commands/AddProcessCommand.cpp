//
// Created by Kacper Harasim on 11.05.2016.
//

#include "AddProcessCommand.h"
AddProcessCommand::AddProcessCommand(Json::Value json) : Command(CommandType::NEW_PROCESS){
  Json::Value processDetails = json[descriptionForCommandType(CommandType::NEW_PROCESS)];
  this->processContent = processDetails["content"].asString();
}

Json::Value AddProcessCommand::generateJSON() {
  Json::Value root = Command::generateJSON();
  Json::Value details;
  details[JSONConstants::ProcessContent] = this->processContent;
  root[JSONConstants::ProcessDetails] = details;
  return root;
}

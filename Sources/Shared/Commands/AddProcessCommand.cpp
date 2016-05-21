//
// Created by Kacper Harasim on 11.05.2016.
//

#include <iostream>
#include "AddProcessCommand.h"

AddProcessCommand::AddProcessCommand(Json::Value json) : Command(CommandType::START_NEW_PROCESS) {
  processContent = json[JSONConstants::ProcessDetails][JSONConstants::ProcessContent].asString();
}

Json::Value AddProcessCommand::generateJSON() {
  Json::Value root = Command::generateJSON();
  Json::Value details;
  details[JSONConstants::ProcessContent] = processContent;
  root[JSONConstants::ProcessDetails] = details;
  return root;
}

AddProcessCommand::AddProcessCommand(std::string processContent) : Command(CommandType::START_NEW_PROCESS) {
  this->processContent = processContent;
}


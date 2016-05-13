//
// Created by Kacper Harasim on 11.05.2016.
//

#include "AddProcessCommand.h"

AddProcessCommand::AddProcessCommand(Json::Value json) : Command(CommandType::NEW_PROCESS){
  Json::Value processDetails = json["processDetails"];
  this->processContent = processDetails["content"].asString()
}

Json::Value AddProcessCommand::generateJSON() {

}
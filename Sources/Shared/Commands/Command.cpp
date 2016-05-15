//
// Created by Kacper Harasim on 11.05.2016.
//

#include "Command.h"
#include "../JSONConstants.h"

Json::Value Command::generateJSON() {
  Json::Value root;
  root[JSONConstants::MessageType] = descriptionForCommandType(commandType);
  return root;
}
//
// Created by Kacper Harasim on 09.05.2016.
//

#include "CommandsDeserializer.h"
#include "Commands/AddProcessCommand.h"


Command CommandsDeserializer::parseToCommand(std::string json) {

  std::string typeSpecificator = "messageType";
  Json::Value root;
  const std::string type = root[typeSpecificator].asString();
  switch (type) {
        case "startNewProcess":



  }
  return nullptr;
}
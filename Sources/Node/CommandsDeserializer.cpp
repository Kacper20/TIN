//
// Created by Kacper Harasim on 09.05.2016.
//

#include <iostream>
#include "CommandsDeserializer.h"
#include "../Shared/Commands/AddProcessCommand.h"


std::shared_ptr<Command> CommandsDeserializer::parseToCommand(std::string json) {

  std::string typeSpecificator = "messageType";
  Json::Reader reader;
  Json::Value root;
  bool parsingSucceeded = reader.parse(json.c_str(), root);
  if (!parsingSucceeded) {
    //TODO: Create our own logger as singleton and run it here - error handle.
    std::cout << "Could not parse json" << std::endl;
    return nullptr;
  }
  const std::string type = root[typeSpecificator].asString();
  if (type == descriptionForCommandType(CommandType::START_NEW_PROCESS)) {
    std::shared_ptr<Command> deserializedCommand(new AddProcessCommand(root));
    return deserializedCommand;
  }
  return nullptr;
}
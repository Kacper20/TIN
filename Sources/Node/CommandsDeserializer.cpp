//
// Created by Kacper Harasim on 09.05.2016.
//

#include <iostream>
#include "CommandsDeserializer.h"
#include "../Shared/Commands/StartProcessCommand.h"


std::shared_ptr<Command> CommandsDeserializer::parseToCommand(std::string json) {

  Json::Reader reader;
  Json::Value root;
  bool parsingSucceeded = reader.parse(json.c_str(), root);
  if (!parsingSucceeded) {
    //TODO: Create our own logger as singleton and run it here - error handle.
    std::cout << "Could not parse json" << std::endl;
    return nullptr;
  }
  const std::string type = root[JSONConstants::CommandType].asString();
  if (type == descriptionForCommandType(CommandType::START_NEW_PROCESS)) {
    std::shared_ptr<Command> deserializedCommand(new StartProcessCommand(root));
    return deserializedCommand;
  }
  return nullptr;
}
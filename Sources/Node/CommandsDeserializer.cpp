//
// Created by Kacper Harasim on 09.05.2016.
//

#include <iostream>
#include "CommandsDeserializer.h"
#include "../Shared/Commands/StartProcessCommand.h"
#include "../Shared/Commands/DeleteProcessCommand.h"
#include "../Shared/Commands/LaunchProcessCommand.h"
#include "../Shared/Commands/RequestDataCommand.h"
#include "../Shared/Commands/RequestProcessStatisticsCommand.h"


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
    std::shared_ptr<Command> deserializedCommand = std::make_shared<StartProcessCommand>(root);
    return deserializedCommand;
  }
  if (type == descriptionForCommandType(CommandType::START_NEW_PROCESS_WITH_SCHEDULE)) {
    std::shared_ptr<Command> deserializedCommand = std::make_shared<StartProcessCommand>(root);
    return deserializedCommand;
  }
  if (type == descriptionForCommandType(CommandType::DELETE_PROCESS)) {
    std::shared_ptr<Command> deserializedCommand = std::make_shared<DeleteProcessCommand>(root);
    return deserializedCommand;
  }
  if (type == descriptionForCommandType(CommandType::LAUNCH_PROCESS)) {
    std::shared_ptr<Command> deserializedCommand = std::make_shared<LaunchProcessCommand>(root);
    return deserializedCommand;
  }
  if (type == descriptionForCommandType(CommandType::REQUEST_DATA)) {
    std::shared_ptr<Command> deserializedCommand = std::make_shared<RequestDataCommand>(root);
    return deserializedCommand;
  }
  if (type == descriptionForCommandType(CommandType::REQUEST_STATISTICS)) {
    std::shared_ptr<Command> deserializedCommand = std::make_shared<RequestProcessStatisticsCommand>(root);
    return deserializedCommand;
  }
  return nullptr;
}
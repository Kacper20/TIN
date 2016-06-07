//
// Created by dawid on 24.05.16.
//

#include <iostream>
#include "LaunchProcessCommand.h"

LaunchProcessCommand::LaunchProcessCommand(Json::Value json) : Command(CommandType::LAUNCH_PROCESS) {
    Json::Value processDetails = json[JSONConstants::ProcessDetails];
    processId = processDetails[JSONConstants::ProcessIdentifier].asString();
}

Json::Value LaunchProcessCommand::generateJSON() {
    Json::Value root = Command::generateJSON();
    Json::Value details;
    details[JSONConstants::ProcessIdentifier] = processId;
    root[JSONConstants::ProcessDetails] = details;
    return root;
}


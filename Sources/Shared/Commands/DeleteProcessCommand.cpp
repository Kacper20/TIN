//
// Created by dawid on 25.05.16.
//

#include "DeleteProcessCommand.h"
#include <iostream>

DeleteProcessCommand::DeleteProcessCommand(Json::Value json) : Command(CommandType::DELETE_PROCESS){
    Json::Value processDetails = json[JSONConstants::ProcessDetails];
    processId = processDetails[JSONConstants::ProcessIdentifier].asString();
}

Json::Value DeleteProcessCommand::generateJSON() {
    Json::Value root = Command::generateJSON();
    root[JSONConstants::ProcessIdentifier] = processId;
    return root;
}
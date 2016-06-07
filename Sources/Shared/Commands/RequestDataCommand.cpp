//
// Created by dawid on 26.05.16.
//

#include "RequestDataCommand.h"
#include <iostream>

RequestDataCommand::RequestDataCommand(Json::Value json) : Command(CommandType::REQUEST_DATA) {
    Json::Value processDetails = json[JSONConstants::ProcessDetails];
    processId = processDetails[JSONConstants::ProcessIdentifier].asString();
    date = processDetails[JSONConstants::Date].asString();
    timestamp = std::stoi(processDetails[JSONConstants::Timestamp].asString());
}

Json::Value RequestDataCommand::generateJSON() {
    Json::Value root = Command::generateJSON();
    Json::Value details;
    details[JSONConstants::ProcessIdentifier] = processId;
    details[JSONConstants::Date] = date;
    details[JSONConstants::Timestamp] = timestamp;
    root[JSONConstants::ProcessDetails] = details;
    return root;
}

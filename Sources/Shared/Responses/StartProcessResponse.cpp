//
// Created by Kacper Harasim on 21.05.2016.
//

#include "StartProcessResponse.h"

StartProcessResponse::StartProcessResponse(Json::Value json) : Response(ResponseType::START_NEW_PROCESS,
ResponseStatus::SUCCESS) {
  Json::Value processDetails = json[JSONConstants::ProcessDetails];
  standardError = processDetails[JSONConstants::StandardError].asString();
  standardOutput = processDetails[JSONConstants::StandardOutput].asString();
  processId = processDetails[JSONConstants::ProcessIdentifier].asString();
}

Json::Value StartProcessResponse::generateJSON() {
  Json::Value root = Response::generateJSON();
  Json::Value details;
  details[JSONConstants::StandardError] = standardError;
  details[JSONConstants::StandardOutput] = standardOutput;
  details[JSONConstants::ProcessIdentifier] = processId;
  root[JSONConstants::ProcessDetails] = details;
  return root;
}

//
// Created by Kacper Harasim on 05.06.2016.
//

#include "LaunchProcessResponse.h"

LaunchProcessResponse::LaunchProcessResponse(Json::Value json): Response(ResponseType::LAUNCH_PROCESS,
                                                                         ResponseStatus::SUCCESS) {
  Json::Value processDetails = json[JSONConstants::ProcessDetails];
  standardError = processDetails[JSONConstants::StandardError].asString();
  standardOutput = processDetails[JSONConstants::StandardOutput].asString();
  processId = processDetails[JSONConstants::ProcessIdentifier].asString();
}

Json::Value LaunchProcessResponse::generateJSON() {
  Json::Value root = Response::generateJSON();
  Json::Value details;
  details[JSONConstants::StandardError] = standardError;
  details[JSONConstants::StandardOutput] = standardOutput;
  details[JSONConstants::ProcessIdentifier] = processId;
  root[JSONConstants::ProcessDetails] = details;
  return root;
}
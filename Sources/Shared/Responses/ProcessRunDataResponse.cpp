//
// Created by Kacper Harasim on 07.06.2016.
//

#include "ProcessRunDataResponse.h"

ProcessRunDataResponse::ProcessRunDataResponse(Json::Value json) : Response(ResponseType::PROCESS_RUN_DATA,
                                                                        ResponseStatus::SUCCESS) {
  Json::Value processDetails = json[JSONConstants::ProcessDetails];
  standardError = processDetails[JSONConstants::StandardError].asString();
  standardOutput = processDetails[JSONConstants::StandardOutput].asString();
  processId = processDetails[JSONConstants::ProcessIdentifier].asString();
  timestamp  = processDetails[JSONConstants::Timestamp].asInt();
}

Json::Value ProcessRunDataResponse::generateJSON() {
  Json::Value root = Response::generateJSON();
  Json::Value details;
  details[JSONConstants::StandardError] = standardError;
  details[JSONConstants::StandardOutput] = standardOutput;
  details[JSONConstants::ProcessIdentifier] = processId;
  details[JSONConstants::Timestamp] = timestamp;
  root[JSONConstants::ProcessDetails] = details;
  return root;
}

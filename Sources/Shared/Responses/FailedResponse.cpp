//
// Created by Kacper Harasim on 05.06.2016.
//

#include "FailedResponse.h"


ResponseType responseTypeBasedOnString(std::string string) {
  if (string == JSONConstants::ResponseStartNewProcess) {
    return ResponseType::START_NEW_PROCESS;
  } else if (string == JSONConstants::ResponseScheduledProcessEnded) {
    return ResponseType::SCHEDULED_PROCESS_ENDED;
  } else if (string == JSONConstants::ResponseProcessDeleted) {
    return ResponseType::DELETE_PROCESS;
  } else if (string == JSONConstants::ResponseProcessLaunched) {
    return ResponseType::LAUNCH_PROCESS;
  } else {
    throw "Unrecognized process";
  }
}

FailedResponse::FailedResponse(Json::Value json): Response(ResponseType::SCHEDULED_PROCESS_ENDED, ResponseStatus::FAIL) {
  errorMessage = json[JSONConstants::Error].asString();
  responseType = responseTypeBasedOnString(json[JSONConstants::ResponseType].asString());
}

Json::Value FailedResponse::generateJSON() {
  Json::Value root = Response::generateJSON();
  root[JSONConstants::Error] = errorMessage;
  root[JSONConstants::ResponseType] = descriptionForResponseType(responseType);
  return root;
}

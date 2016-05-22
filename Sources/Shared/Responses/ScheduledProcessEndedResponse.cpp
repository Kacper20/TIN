//
// Created by Kacper Harasim on 21.05.2016.
//

#include "ScheduledProcessEndedResponse.h"

ScheduledProcessEndedResponse::ScheduledProcessEndedResponse(Json::Value json):
    Response(ResponseType::SCHEDULED_PROCESS_ENDED) {
  Json::Value processDetails = json[JSONConstants::ProcessDetails];
  processId = processDetails[JSONConstants::ProcessIdentifier].asString();
  dayDate = processDetails[JSONConstants::Date].asString();
  timestamp = processDetails[JSONConstants::Timestamp].asInt();
}

Json::Value ScheduledProcessEndedResponse::generateJSON() {
  Json::Value root = Response::generateJSON();
  Json::Value details;
  details[JSONConstants::Date] = dayDate;
  details[JSONConstants::Timestamp] = timestamp;
  details[JSONConstants::ProcessIdentifier] = processId;
  root[JSONConstants::ProcessDetails] = details;
  return root;
}
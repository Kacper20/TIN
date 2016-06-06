//
// Created by Kacper Harasim on 06.06.2016.
//

#include "ProcessStatisticsResponse.h"

ProcessStatisticsResponse::ProcessStatisticsResponse(Json::Value json): Response(ResponseType::GET_STATISTICS_ABOUT_PROCESS,
                                                                         ResponseStatus::SUCCESS) {
  Json::Value processDetails = json[JSONConstants::ProcessDetails];
  secondsSystemRun = json[JSONConstants::ProcessSecondsSystemRunTime].asInt();
  millisecondsSystemRun = json[JSONConstants::ProcessMillisecondsSystemRunTime].asInt();
  secondsUserRun = json[JSONConstants::ProcessSecondsUserRunTime].asInt();
  millisecondsUserRun = json[JSONConstants::ProcessMillisecondsUserRunTime].asInt();

  processId = processDetails[JSONConstants::ProcessIdentifier].asString();
}

Json::Value ProcessStatisticsResponse::generateJSON() {
  Json::Value root = Response::generateJSON();
  Json::Value details;
  details[JSONConstants::ProcessSecondsSystemRunTime] = secondsSystemRun;
  details[JSONConstants::ProcessMillisecondsSystemRunTime] = millisecondsSystemRun;
  details[JSONConstants::ProcessSecondsUserRunTime] = secondsUserRun;
  details[JSONConstants::ProcessMillisecondsUserRunTime] = millisecondsUserRun;
  details[JSONConstants::ProcessIdentifier] = processId;
  root[JSONConstants::ProcessDetails] = details;
  return root;
}
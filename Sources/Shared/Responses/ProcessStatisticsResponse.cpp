//
// Created by Kacper Harasim on 06.06.2016.
//

#include "ProcessStatisticsResponse.h"

ProcessStatisticsResponse::ProcessStatisticsResponse(Json::Value json): Response(ResponseType::GET_STATISTICS_ABOUT_PROCESS,
                                                                         ResponseStatus::SUCCESS) {
  Json::Value processDetails = json[JSONConstants::ProcessDetails];
  secondsSystemRun = processDetails[JSONConstants::ProcessSecondsSystemRunTime].asInt();
  millisecondsSystemRun = processDetails[JSONConstants::ProcessMillisecondsSystemRunTime].asInt();
  secondsUserRun = processDetails[JSONConstants::ProcessSecondsUserRunTime].asInt();
  millisecondsUserRun = processDetails[JSONConstants::ProcessMillisecondsUserRunTime].asInt();

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
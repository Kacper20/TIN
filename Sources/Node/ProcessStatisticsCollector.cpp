//
// Created by Kacper Harasim on 05.06.2016.
//

#include "ProcessStatisticsCollector.h"
#include "../Shared/Responses/FailedResponse.h"
#include "../Shared/Responses/ProcessStatisticsResponse.h"

void ProcessStatisticsCollector::requestStatisticsForProcess(std::string processId) {

  auto mapResult = processesInfo.find(processId);
  if(mapResult != processesInfo.end()) {
    //element found;
    auto currentRunningTime = mapResult->second;

    std::shared_ptr<ProcessStatisticsResponse> succResponse = std::make_shared<ProcessStatisticsResponse>(processId,
    currentRunningTime.secondsSystem, currentRunningTime.millisecondsSystem, currentRunningTime.secondsUser, currentRunningTime.millisecondsUser);
    responseCompletion(succResponse);
  } else {
    std::shared_ptr<FailedResponse> failedResp = std::make_shared<FailedResponse>("Proces o takim identyfikatorze"
                                                                                      " nie był uruchamiany na serwerze");
    responseCompletion(failedResp);
  }
}

void ProcessStatisticsCollector::addDataForProcessWithId(std::string processId,
                                                         timeval userTime,
                                                         timeval systemTime) {
  std::lock_guard<mutex> lock(resourceMutex);
  auto currentData = processesInfo.find(processId);

  if (currentData != processesInfo.end()) {
    auto runningTime = currentData->second;

    auto newSecSystem = (int)systemTime.tv_sec + runningTime.secondsSystem;
    int newMilliSystem = (int)(systemTime.tv_sec / 1000.0);
    int sumMilliSystem = newMilliSystem + runningTime.millisecondsSystem;
    if (sumMilliSystem >= 1000) {newSecSystem++; sumMilliSystem = (int)sumMilliSystem % 1000; }
    runningTime.secondsSystem = newSecSystem;
    runningTime.millisecondsSystem = sumMilliSystem;

    auto newSecUser = (int)userTime.tv_sec + runningTime.secondsUser;
    int newMilliUser = (int)(userTime.tv_sec / 1000.0);
    int sumMilliUser = newMilliUser + runningTime.millisecondsUser;
    if (sumMilliUser >= 1000) {newSecUser++; sumMilliUser = (int)sumMilliUser % 1000; }
    runningTime.secondsUser = newSecUser;
    runningTime.millisecondsUser = sumMilliUser;
    processesInfo[processId] = runningTime;
  } else {
    ProcessRunningTime runningTime;
    runningTime.secondsSystem = (int)systemTime.tv_sec;
    runningTime.millisecondsSystem = (int)(systemTime.tv_usec / 1000.0);
    runningTime.secondsUser = (int)userTime.tv_sec;
    runningTime.millisecondsUser= (int)(userTime.tv_usec / 1000.0);
    processesInfo[processId] = runningTime;
  }
}
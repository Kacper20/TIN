//
// Created by Kacper Harasim on 05.06.2016.
//

#ifndef TIN_PROCESSSTATISTICSCOLLECTOR_H
#define TIN_PROCESSSTATISTICSCOLLECTOR_H

#include <memory>
#include <mutex>
#import "../Shared/Responses/Response.h"
#include "ProcessRunningTime.h"

#include <functional>
#include <memory>
#include <mutex>

typedef std::function<void(std::shared_ptr<Response>)> ResponseCompletion;

class ProcessStatisticsCollector {

public:

 private:
  std::mutex resourceMutex;
  //Values of map are in miliseconds
  std::map<std::string, ProcessRunningTime > processesInfo;

 public:
  ResponseCompletion responseCompletion;
  //Function called when someone

  //Function that takes care of gathering stats and sending it to server
  void requestStatisticsForProcess(std::string processId);

  void addDataForProcessWithId(std::string processId, timeval userTime, timeval systemTime);
};


#endif //TIN_PROCESSSTATISTICSCOLLECTOR_H

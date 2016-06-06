//
// Created by Kacper Harasim on 21.05.2016.
//

#ifndef TIN_RESPONSE_H
#define TIN_RESPONSE_H

#include "../../Libraries/json/json.h"
#include "../JSONConstants.h"

#include <string>


enum class ResponseType {
  START_NEW_PROCESS,
  SCHEDULED_PROCESS_ENDED,
  DELETE_PROCESS,
  LAUNCH_PROCESS,
  GET_STATISTICS_ABOUT_PROCESS,
};

enum class ResponseStatus {
  SUCCESS, FAIL
};

static std::string descriptionForResponseType(ResponseType type) {
  switch (type) {
    case ResponseType::START_NEW_PROCESS:
      return JSONConstants::ResponseStartNewProcess;
    case ResponseType::SCHEDULED_PROCESS_ENDED:
      return JSONConstants::ResponseScheduledProcessEnded;
    case ResponseType::DELETE_PROCESS:
      return JSONConstants::ResponseProcessDeleted;
    case ResponseType::LAUNCH_PROCESS:
      return JSONConstants::ResponseProcessLaunched;
    case ResponseType::GET_STATISTICS_ABOUT_PROCESS:
      return JSONConstants::ResponseProcessStatistics;
  }
}

static std::string descriptionForResponseStatus(ResponseStatus status) {
  switch (status) {
    case ResponseStatus::FAIL:
      return JSONConstants::ResponseFailed;
    case ResponseStatus::SUCCESS:
      return JSONConstants::ResponseSuccess;
    }
}

class Response {
 public:
  ResponseType responseType;
  ResponseStatus responseStatus;
  std::string message;
  Response(ResponseType responseType, ResponseStatus responseStatus)
      : responseType(responseType), responseStatus(responseStatus) { }
  virtual Json::Value generateJSON();
};


#endif //TIN_RESPONSE_H

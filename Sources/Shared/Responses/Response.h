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
  DELETE_PROCESS
};

enum class ResponseStatus {
  SUCCESS, FAIL
};

static std::string descriptionForResponseType(ResponseType type) {
  switch (type) {
    case ResponseType::START_NEW_PROCESS:
      return "startNewProcess";
    case ResponseType ::SCHEDULED_PROCESS_ENDED:
      return "scheduledProcessEnded";
    case ResponseType::DELETE_PROCESS:
      return "";
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

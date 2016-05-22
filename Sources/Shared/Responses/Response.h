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
  SCHEDULED_PROCESS_ENDED
};

static std::string descriptionForResponseType(ResponseType type) {
  switch (type) {
    case ResponseType::START_NEW_PROCESS:
      return "startNewProcess";
    case ResponseType ::SCHEDULED_PROCESS_ENDED:
      return "scheduledProcessEnded";
  }
}

class Response {
 private:
  ResponseType responseType;
 public:
  Response(ResponseType responseType) : responseType(responseType) {}
  virtual Json::Value generateJSON();
};


#endif //TIN_RESPONSE_H

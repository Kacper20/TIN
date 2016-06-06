//
// Created by Kacper Harasim on 05.06.2016.
//

#ifndef TIN_FAILEDRESPONSE_H
#define TIN_FAILEDRESPONSE_H

#import "Response.h"

using namespace std;
class FailedResponse: public Response {
 public:
  string errorMessage;
  FailedResponse (Json::Value json);

  FailedResponse (ResponseType responseType, string errorMessage):
  Response(responseType, ResponseStatus::FAIL), errorMessage(errorMessage) {}
  Json::Value generateJSON();
};



#endif //TIN_FAILEDRESPONSE_H

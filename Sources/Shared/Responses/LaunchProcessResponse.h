//
// Created by Kacper Harasim on 05.06.2016.
//

#ifndef TIN_LAUNCHPROCESSRESPONSE_H
#define TIN_LAUNCHPROCESSRESPONSE_H

#import "Response.h"
#include "../../Libraries/json/json.h"
using namespace std;
class LaunchProcessResponse: public Response {
  string processId;
  string standardError;
  string standardOutput;
  LaunchProcessResponse(Json::Value json);

  LaunchProcessResponse(string processId, string standardError, string standardOutput) :
      Response(ResponseType::START_NEW_PROCESS, ResponseStatus::SUCCESS), processId(processId),
      standardError(standardError),
      standardOutput(standardOutput) { }
  Json::Value generateJSON();
};


#endif //TIN_LAUNCHPROCESSRESPONSE_H

//
// Created by Kacper Harasim on 21.05.2016.
//

#ifndef TIN_STARTPROCESSRESPONSE_H
#define TIN_STARTPROCESSRESPONSE_H


#include "Response.h"
using namespace std;
class StartProcessResponse: public Response {

 public:
  string processId;
  string standardError;
  string standardOutput;
  StartProcessResponse (Json::Value json);
  StartProcessResponse (string processId, string standardError, string standardOutput):
      Response(ResponseType::START_NEW_PROCESS, ResponseStatus::SUCCESS), processId(processId), standardError(standardError),
      standardOutput(standardOutput) {}
  Json::Value generateJSON();
};


#endif //TIN_STARTPROCESSRESPONSE_H

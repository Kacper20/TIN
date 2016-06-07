//
// Created by Kacper Harasim on 07.06.2016.
//

#ifndef TIN_PROCESSRUNDATARESPONSE_H
#define TIN_PROCESSRUNDATARESPONSE_H


#include "Response.h"

using namespace std;
class ProcessRunDataResponse: public Response {

 public:
  string processId;
  string standardError;
  string standardOutput;
  int timestamp;
  ProcessRunDataResponse (Json::Value json);
  ProcessRunDataResponse (string processId, string standardError, string standardOutput, int timestamp):
      Response(ResponseType::PROCESS_RUN_DATA, ResponseStatus::SUCCESS), processId(processId), standardError(standardError),
      standardOutput(standardOutput), timestamp(timestamp) {}
  Json::Value generateJSON();
};


#endif //TIN_PROCESSRUNDATARESPONSE_H

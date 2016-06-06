//
// Created by Kacper Harasim on 06.06.2016.
//

#ifndef TIN_PROCESSSTATISTICSRESPONSE_H
#define TIN_PROCESSSTATISTICSRESPONSE_H


#include "Response.h"
#include <stdint.h>
using namespace std;

class ProcessStatisticsResponse: public Response {
 public:
  string processId;
  int secondsUserRun;
  int millisecondsUserRun;
  int secondsSystemRun;
  int millisecondsSystemRun;

  ProcessStatisticsResponse(Json::Value json);


  ProcessStatisticsResponse(
                            const string &processId,
                            int secondsUserRun,
                            int millisecondsUserRun,
                            int secondsSystemRun,
                            int millisecondsSystemRun) : Response(ResponseType::GET_STATISTICS_ABOUT_PROCESS, ResponseStatus::SUCCESS), processId(processId),
                                                         secondsUserRun(secondsUserRun),
                                                         millisecondsUserRun(millisecondsUserRun),
                                                         secondsSystemRun(secondsSystemRun),
                                                         millisecondsSystemRun(millisecondsSystemRun) { }
  Json::Value generateJSON();
};

#endif //TIN_PROCESSSTATISTICSRESPONSE_H

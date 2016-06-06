//
// Created by Kacper Harasim on 21.05.2016.
//

#ifndef TIN_STARTPROCESSWITHSCHEDULERESPONSE_H
#define TIN_STARTPROCESSWITHSCHEDULERESPONSE_H

#include "Response.h"

using namespace std;

class ScheduledProcessEndedResponse: public Response {

 public:
  string processId;
  string dayDate;
  int timestamp;
  ScheduledProcessEndedResponse (Json::Value json);
  ScheduledProcessEndedResponse (string processId, string dayDate, int timestamp):
  Response(ResponseType::SCHEDULED_PROCESS_ENDED, ResponseStatus::SUCCESS), processId(processId), dayDate(dayDate), timestamp(timestamp) {}
  Json::Value generateJSON();
};


#endif //TIN_STARTPROCESSWITHSCHEDULERESPONSE_H

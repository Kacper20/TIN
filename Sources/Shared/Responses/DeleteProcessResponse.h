//
// Created by Kacper Harasim on 07.06.2016.
//

#ifndef TIN_DELETE_H
#define TIN_DELETE_H

#import "Response.h"

using namespace std;
class DeleteProcessResponse: public Response {
 public:
  string processId;

  DeleteProcessResponse (Json::Value json);
  DeleteProcessResponse (string processId, string dayDate, int timestamp):
  Response(ResponseType::DELETE_PROCESS, ResponseStatus::SUCCESS), processId(processId) {}
  Json::Value generateJSON();

};


#endif //TIN_DELETE_H

//
// Created by Kacper Harasim on 07.06.2016.
//

#include "DeleteProcessResponse.h"

DeleteProcessResponse::DeleteProcessResponse(Json::Value json):
    Response(ResponseType::DELETE_PROCESS, ResponseStatus::SUCCESS) {
  Json::Value processDetails = json[JSONConstants::ProcessDetails];
  processId = processDetails[JSONConstants::ProcessIdentifier].asString();

}

Json::Value DeleteProcessResponse::generateJSON() {
  Json::Value root = Response::generateJSON();
  Json::Value details;
  details[JSONConstants::ProcessIdentifier] = processId;
  root[JSONConstants::ProcessDetails] = details;
  return root;
}
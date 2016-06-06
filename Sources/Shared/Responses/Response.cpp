//
// Created by Kacper Harasim on 21.05.2016.
//

#include "Response.h"

Json::Value Response::generateJSON() {
  Json::Value root;
  root[JSONConstants::ResponseType] = descriptionForResponseType(responseType);
  root[JSONConstants::ResponseStatus] =
  return root;
}
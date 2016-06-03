//
// Created by Kacper Harasim on 02.06.2016.
//

#ifndef TIN_PROCESSUTILITIES_H
#define TIN_PROCESSUTILITIES_H


#include "../Libraries/json/json.h"
class ProcessUtilities {
 public:
  static void writeProcessToPersistentStorage(Json::Value commandJson, const std::string& processContent,
                                                const std::string& identifier);
  static std::string directoryForProcessWithId(const std::string& id);
};


#endif //TIN_PROCESSUTILITIES_H

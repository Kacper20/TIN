//
// Created by Kacper Harasim on 02.06.2016.
//

#ifndef TIN_PROCESSUTILITIES_H
#define TIN_PROCESSUTILITIES_H


#include "../Libraries/json/json.h"

enum class ProcessInfo {Error, Output};
class ProcessUtilities {
 public:
  static void writeProcessToPersistentStorage(Json::Value commandJson, const std::string& processContent,
                                                const std::string& identifier);
  static std::string readProcessContentFromPersistentStorage(std::string identifier);
  static std::string readProcessInfoFromPersistentStorage(std::string identifier, ProcessInfo processInfo);
  static std::string directoryForProcessWithId(const std::string& id);
  static int runProcess(std::string basePath, std::string additionToPath);
};


#endif //TIN_PROCESSUTILITIES_H

//
// Created by Kacper Harasim on 02.06.2016.
//

#include "ProcessUtilities.h"
#include "../Shared/FileManager.h"
#include "PathConstants.h"

void ProcessUtilities::writeProcessToPersistentStorage(Json::Value commandJson,
                                                       const std::string &processContent,
                                                       const std::string &identifier) {

  std::string directoryForProcess = directoryForProcessWithId(identifier);
  int result = FileManager::createDirectoryAtPath(directoryForProcess);
  if (result < 0) {
    perror("Cannot create directory");
  }
  std::string processContentPath = FileManager::buildPath(directoryForProcess, PathConstants::RunnableScript);
  std::string jsonContentPath = FileManager::buildPath(directoryForProcess, PathConstants::CommandJSON);

  Json::FastWriter fastWriter;
  std::string jsonInString = fastWriter.write(commandJson);

  FileManager::writeToFile(processContentPath, processContent);
  FileManager::writeToFile(jsonContentPath, jsonInString);
  chmod(processContentPath.c_str(), S_IRWXU);
}

std::string ProcessUtilities::directoryForProcessWithId(const std::string &id) {
  std::string base = FileManager::homeDir();
  return base + "/" + "TIN_NODE/"  + id;
}
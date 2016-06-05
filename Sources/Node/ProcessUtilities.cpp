//
// Created by Kacper Harasim on 02.06.2016.
//

#include <fstream>
#include "ProcessUtilities.h"
#include "../Shared/FileManager.h"
#include "PathConstants.h"
#include "../Exceptions/ProcessDoNotExistOnNode.h"

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

std::string ProcessUtilities::readProcessContentFromPersistentStorage(std::string identifier) {
  std::string directoryForProcess = directoryForProcessWithId(identifier);
  std::string processContentPath = FileManager::buildPath(directoryForProcess, PathConstants::RunnableScript);
  std::ifstream file(processContentPath.c_str());
  if (!file.is_open()) {
    throw ProcessDoNotExistOnNode("Proces nie istnieje", -1);
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string str = buffer.str();
  return directoryForProcess;
}

std::string ProcessUtilities::directoryForProcessWithId(const std::string &id) {
  std::string base = FileManager::homeDir();
  return base + "/" + "TIN_NODE/"  + id;
}
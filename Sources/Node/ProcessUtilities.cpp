//
// Created by Kacper Harasim on 02.06.2016.
//

#include "ProcessUtilities.h"
#include "../Shared/FileManager.h"
#include "PathConstants.h"
#include "../Exceptions/ProcessDoNotExistOnNode.h"

#include <fcntl.h>
#include <iostream>
#include <thread>
#include <csignal>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/wait.h>
#include <fstream>


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

int ProcessUtilities::runProcess(std::string basePath, std::string additionToPath) {
  pid_t newProcessId;
  int childProcessStatus;
  newProcessId = fork();
  if (newProcessId < 0) {
    exit(-1);
  } else if (newProcessId == 0) {
    char *params[4] = {0};
    auto outPath = FileManager::buildPath(basePath, PathConstants::ProcessStandardOutput);
    auto errPath = FileManager::buildPath(basePath, PathConstants::ProcessStandardError);
    if (additionToPath.size() != 0) {
      outPath += "_" + additionToPath;
      errPath += "_" + additionToPath;
    }
    auto processFilePath = FileManager::buildPath(basePath, PathConstants::RunnableScript);
    int stdOutFd = open(outPath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    int stdErrFd = open(errPath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    dup2(stdOutFd, 1);
    dup2(stdErrFd, 2);
    close(stdOutFd);
    close(stdErrFd);
    execvp(processFilePath.c_str(), params);
  } else {
    return newProcessId;
  }
}
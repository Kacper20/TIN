//
// Created by Kacper Harasim on 09.05.2016.
//
#include "ProcessHandler.h"
#include "../Shared/FileManager.h"
#include "PathConstants.h"
#include "../Shared/Responses/StartProcessResponse.h"

#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <csignal>
#include <sys/wait.h>

#define PROCESSES_BASE_DIRECTORY "/Users/kacperh/Developer/TIN_TEMP"



void ProcessHandler::runProcess(std::shared_ptr<StartProcessCommand> process) {
  processesToRunQueue.push(process);
}

std::string directoryForProcessWithId(const std::string& id) {
  return std::string(PROCESSES_BASE_DIRECTORY) + "/" + id;
}

void ProcessHandler::startMonitoringForProcessesToRun() {
  while (1) {
    std::shared_ptr<StartProcessCommand> command = processesToRunQueue.pop();
    writeProcessToPersistentStorage(command->generateJSON(), command->processContent, command->processId);
    runProcessWithCommand(command, directoryForProcessWithId(command->processId));
  }
}

void ProcessHandler::writeProcessToPersistentStorage(Json::Value commandJson, const std::string& processContent,
                                                     const std::string& identifier) {
  //First, ensure that processes have its
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

//TODO: We need to queue this methods calls and provide not mocked locations
void ProcessHandler::runProcessWithCommand(std::shared_ptr<StartProcessCommand> command, const std::string& basePath) {
  pid_t newProcessId;
  int childProcessStatus;
  std::cout << "RUN PROCESS!\n";
  newProcessId = fork();
  if (newProcessId < 0) {
    exit(-1);
  } else if (newProcessId == 0) {
    char *params[4]  = {0};
    auto outPath = FileManager::buildPath(basePath, PathConstants::ProcessStandardOutput);
    auto errPath = FileManager::buildPath(basePath, PathConstants::ProcessStandardError);
    auto processFilePath = FileManager::buildPath(basePath, command->processId);
    int stdOutFd = open(outPath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    int stdErrFd = open(errPath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    dup2(stdOutFd, 1);
    dup2(stdErrFd, 2);
    execvp(processFilePath.c_str(), params);
  } else {
    std::unique_lock<std::mutex> lock(startedProcessMutex);
    auto pair = std::pair<int, std::shared_ptr<StartProcessCommand> >(newProcessId, command);
    runningProcesses.insert(pair);
    conditionVariable.notify_one();
  }
}

void ProcessHandler::monitorProcessesEndings(ResponseCompletion responseCompletion) {
  int status;
  pid_t childPid;

  //TODO: Implement counting semaphore... Here we have rare race condition.
  while(1) {
    std::unique_lock<std::mutex> lock(startedProcessMutex);
    conditionVariable.wait(lock);
    while ((childPid = waitpid(-1, &status, 0)) > 0) {
      std::cout << "Process ended" << childPid << std::endl;
      auto processInfo = runningProcesses.find(int(childPid));
      if (processInfo == runningProcesses.end()) {
        std::cout << "Error has occured - element not found in map!";
        exit(-1);
      }
      auto command = processInfo->second;
      auto basePath = directoryForProcessWithId(command->processId);
      auto stdError = FileManager::readFromFile(FileManager::buildPath(basePath,
                                                                            PathConstants::ProcessStandardError));
      auto stdOutput = FileManager::readFromFile(FileManager::buildPath(basePath,
                                                                     PathConstants::ProcessStandardOutput));
      auto response = std::make_shared<StartProcessResponse>(command->processId, stdError, stdOutput);

      responseCompletion(response);
    }
    if (childPid < 0 ) {
      perror("Waitpid error");
    }
  }
}

ProcessHandler::ProcessHandler() {
  FileManager::createDirectoryAtPath(PROCESSES_BASE_DIRECTORY);
}
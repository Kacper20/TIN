//
// Created by Kacper Harasim on 09.05.2016.
//
#include "ProcessInstantRunHandler.h"
#include "../Shared/FileManager.h"
#include "PathConstants.h"
#include "../Shared/Responses/StartProcessResponse.h"
#include "../Shared/DateUtilities.h"
#include "ProcessUtilities.h"

#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <csignal>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/wait.h>


void ProcessInstantRunHandler::runProcess(std::shared_ptr<StartProcessCommand> process) {
  processesToRunQueue.push(process);
}

void ProcessInstantRunHandler::startMonitoringForProcessesToInstantRun() {
  while (1) {
    std::shared_ptr<StartProcessCommand> command = processesToRunQueue.pop();
    ProcessUtilities::writeProcessToPersistentStorage(command->generateJSON(),
                                                      command->processContent,
                                                      command->processId);
    runProcessWithCommand(command, ProcessUtilities::directoryForProcessWithId(command->processId));
  }
}


//TODO: We need to queue this methods calls and provide not mocked locations
void ProcessInstantRunHandler::runProcessWithCommand(std::shared_ptr<StartProcessCommand> command, const std::string& basePath) {
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
    auto processFilePath = FileManager::buildPath(basePath, PathConstants::RunnableScript);
    int stdOutFd = open(outPath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    int stdErrFd = open(errPath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    dup2(stdOutFd, 1);
    dup2(stdErrFd, 2);
    close(stdOutFd);
    close(stdErrFd);

    execvp(processFilePath.c_str(), params);
  } else {
    auto monitoringTask = std::make_shared<ProcessOneTimeRunMonitoringTask>(ProcessOneTimeRunMonitoringTask(*this,
                                                                                        newProcessId, command, responseCompletion));
    std::thread monitoringThread(*monitoringTask);
    std::lock_guard<std::mutex> guard(threadsInfoMutex);
    tasksInProgress.insert(std::make_pair(newProcessId, monitoringTask));
    monitoringThread.detach();
  }
}

void ProcessInstantRunHandler::monitorProcessesEndings(std::shared_ptr<StartProcessCommand> command, int pidToWait, ResponseCompletion responseCompletion) {
  int status;
  pid_t childPid;

  childPid = waitpid(pidToWait, &status, 0);

  std::lock_guard<std::mutex> guard(threadsInfoMutex);
  tasksInProgress.erase(childPid);

  std::cout << "Process ended" << childPid << std::endl;
  auto basePath = ProcessUtilities::directoryForProcessWithId(command->processId);
  auto stdError = FileManager::readFromFile(FileManager::buildPath(basePath,
                                                                   PathConstants::ProcessStandardError));
  auto stdOutput = FileManager::readFromFile(FileManager::buildPath(basePath,
                                                                       PathConstants::ProcessStandardOutput));
  auto response = std::make_shared<StartProcessResponse>(command->processId, stdError, stdOutput);
  responseCompletion(response);
  if (childPid < 0 ) {
    perror("Waitpid error");
  }
}

void ProcessInstantRunHandler::removeProcessData(std::string processId) {
  FileManager::deleteDirectoryAtPath(ProcessUtilities::directoryForProcessWithId(processId));
}

ProcessInstantRunHandler::ProcessInstantRunHandler() {
  FileManager::createDirectoryAtPath(FileManager::homeDir() + "/TIN_NODE");
}
//
// Created by Kacper Harasim on 09.05.2016.
//
#include "ProcessInstantRunHandler.h"
#include "../Shared/FileManager.h"
#include "PathConstants.h"
#include "../Shared/Responses/StartProcessResponse.h"
#include "../Shared/DateUtilities.h"
#include "ProcessUtilities.h"
#include "../Shared/Commands/LaunchProcessCommand.h"
#include "../Exceptions/ProcessDoNotExistOnNode.h"
#include "../Shared/Responses/FailedResponse.h"
#include "../Shared/Responses/LaunchProcessResponse.h"

#include <fcntl.h>
#include <iostream>
#include <fstream>
#include <thread>
#include <csignal>
#include <unistd.h>
#include <sys/types.h>
#include<sys/resource.h>
#include <pwd.h>
#include <sys/wait.h>
#include <sys/resource.h>


void ProcessInstantRunHandler::runProcess(std::shared_ptr<StartProcessCommand> process) {
  processesToRunQueue.push(process);
}

void ProcessInstantRunHandler::launchProcess(std::shared_ptr<LaunchProcessCommand> process) {
  try {
    std::string content = ProcessUtilities::readProcessContentFromPersistentStorage(process->processId);
    std::shared_ptr<StartProcessCommand>
        startCommand = std::make_shared<StartProcessCommand>(process->processId, content);
    startCommand->startType = StartType::LAUNCHED;
    processesToRunQueue.push(startCommand);
  }
  catch (ProcessDoNotExistOnNode &e) {
    std::shared_ptr<FailedResponse> response = std::make_shared<FailedResponse>(ResponseType::LAUNCH_PROCESS, "Proces nie został znaleziony w bazie");
    responseCompletion(response);
  }
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
void ProcessInstantRunHandler::runProcessWithCommand(std::shared_ptr<StartProcessCommand> command,
                                                     const std::string &basePath) {

  int newProcessId = ProcessUtilities::runProcess(basePath, "");
  auto monitoringTask = std::make_shared<ProcessOneTimeRunMonitoringTask>(ProcessOneTimeRunMonitoringTask(*this,
                                                                                                            newProcessId,
                                                                                                            command,
                                                                                                            responseCompletion));
  std::thread monitoringThread(*monitoringTask);
  std::lock_guard<std::mutex> guard(threadsInfoMutex);
  tasksInProgress.insert(std::make_pair(newProcessId, monitoringTask));
  monitoringThread.detach();
}

void ProcessInstantRunHandler::monitorProcessesEndings(std::shared_ptr<StartProcessCommand> command,
                                                       int pidToWait,
                                                       ResponseCompletion responseCompletion) {
  int status;
  pid_t childPid;

  struct rusage processUsage;
  childPid = wait4(pidToWait, &status, 0, &processUsage);
  collector.addDataForProcessWithId(command->processId, processUsage.ru_utime, processUsage.ru_stime);
  std::lock_guard<std::mutex> guard(threadsInfoMutex);
  tasksInProgress.erase(childPid);

  std::cout << "Process ended" << childPid << std::endl;
  auto basePath = ProcessUtilities::directoryForProcessWithId(command->processId);
  auto stdError = FileManager::readFromFile(FileManager::buildPath(basePath,
                                                                   PathConstants::ProcessStandardError));
  auto stdOutput = FileManager::readFromFile(FileManager::buildPath(basePath,
                                                                    PathConstants::ProcessStandardOutput));

  if (command->startType == StartType::NEW) {
      auto response = std::make_shared<StartProcessResponse>(command->processId, stdError, stdOutput);
      responseCompletion(response);
  } else {
    auto response = std::make_shared<LaunchProcessResponse>(command->processId, stdError, stdOutput);
    responseCompletion(response);
  }
}

void ProcessInstantRunHandler::removeProcessData(std::string processId) {
  FileManager::deleteDirectoryAtPath(ProcessUtilities::directoryForProcessWithId(processId));
}

ProcessInstantRunHandler::ProcessInstantRunHandler(ProcessStatisticsCollector &collector) : collector(collector) { 
  FileManager::createDirectoryAtPath(FileManager::homeDir() + "/TIN_NODE");
}
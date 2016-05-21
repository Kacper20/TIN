//
// Created by Kacper Harasim on 09.05.2016.
//

#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include "ProcessHandler.h"
#include "../Shared/FileManager.h"
#include <csignal>



void ProcessHandler::runProcess(std::shared_ptr<AddProcessCommand> process) {
  processesToRunQueue.push(process);
}

void ProcessHandler::startMonitoringForProcessesToRun() {
  while (1) {
    std::shared_ptr<AddProcessCommand> command = processesToRunQueue.pop();
    writeProcessToPersistenceStorage(command->processContent);
    runProcessWithCommand(command);
  }
}

void ProcessHandler::writeProcessToPersistenceStorage(std::string processContent) {
  //First, ensure that processes have its
  int result = FileManager::createDirectoryAtPath(processesLocation);
  if (result == -1) {
    perror("Cannot create dir");
  }
  std::string processPath =  processesLocation + "/" + "1";
  std::ofstream file(processPath);
  file << processContent;
  file.close();
  chmod(processPath.c_str(), S_IRWXU);
}

//TODO: We need to queue this methods calls and provide not mocked locations
void ProcessHandler::runProcessWithCommand(std::shared_ptr<AddProcessCommand> command) {
  pid_t newProcessId;
  int childProcessStatus;
  newProcessId = fork();
  if (newProcessId < 0) {
    exit(-1);
  } else if (newProcessId == 0) {
    char *params[4]  = {0};
    std::string outPath = processesLocation + "/" + "out.txt";
    std::string errPath = processesLocation + "/" + "err.txt";
    std::string processFilePath = processesLocation + "/" + "1";
    int stdOutFd = open(outPath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    int stdErrFd = open(errPath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    dup2(stdOutFd, 1);
    dup2(stdErrFd, 2);
    execvp(processFilePath.c_str(), params);
  } else {
    runningProcessesQueue.push(std::make_tuple(command, newProcessId));
  }
}
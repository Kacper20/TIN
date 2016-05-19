//
// Created by Kacper Harasim on 09.05.2016.
//

#include <cstdlib>
#include <fcntl.h>
#include <iostream>
#include <fstream>
#include "ProcessHandler.h"
#include "../Shared/FileManager.h"

static void signalChildTerminate(int) {
  pid_t childPid;
  int status;
  while ((childPid = waitpid(-1, &status, WNOHANG)) > 0) {
    std::cout << "Child ended!!";
  }
}



void ProcessHandler::writeProcessToPersistenceStorage(std::string processContent) {
  //First, ensure that processes have its
  FileManager::createDirectoryAtPath(processesLocation);
  std::ofstream file(processesLocation + "/" + "1");
  file << processContent;
  file.close();
}

//TODO: We need to queue this methods calls
void ProcessHandler::runProcessWithIdentifier(std::string processIdentifier) {
  pid_t newProcessId;
  int childProcessStatus;
  if ((newProcessId = fork()) < 0) {
    exit(-1);
  } else if (newProcessId == 0) {
    char *params[4]  = {0};
    std::string outPath = processesLocation + "/" + "out.txt";
    std::string errPath = processesLocation = "/" = "err.txt";
    std::string processFilePath = processesLocation + "/" + "1";
    int stdOutFd = open(outPath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    int stdErrFd = open(errPath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    dup2(stdOutFd, 1);
    dup2(stdErrFd, 2);
    execvp(processFilePath.c_str(), params);
  } else {
    wait(&childProcessStatus);
  }

}



ProcessHandler::ProcessHandler() {
  //We need to register to the signal function, that fire every time when child process status changes
  if (signal(SIGCHLD, signalChildTerminate) == SIG_ERR)
    perror("Signal error has occured");

}
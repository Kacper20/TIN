//
// Created by Kacper Harasim on 09.05.2016.
//

#include <cstdlib>
#include <fcntl.h>
#include "ProcessRunner.h"

void ProcessRunner::runProcessAtPath(std::string processFilePath,
                                     std::string processErrorPath,
                                     std::string processStdOutputPath) {
  pid_t newProcessId;
  int childProcessStatus;
  if ((newProcessId = fork()) < 0) {
    exit(-1);
  } else if (newProcessId == 0) {
    char *params[4]  = {0};
    int stdOutFd = open(processStdOutputPath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    int stdErrFd = open(processErrorPath.c_str(), O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    dup2(stdOutFd, 1);
    dup2(stdErrFd, 2);
    execvp(processFilePath.c_str(), params);
  } else {
    wait(&childProcessStatus);
  }

}

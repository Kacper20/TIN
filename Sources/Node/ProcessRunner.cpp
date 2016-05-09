//
// Created by Kacper Harasim on 09.05.2016.
//

#include <cstdlib>
#include "ProcessRunner.h"

void ProcessRunner::runProcessAtPath(std::string processFilePath) {
  pid_t newProcessId;
  if ((newProcessId = fork()) < 0) {
    exit(-1);
  } else if (newProcessId == 0) {

  } else {
    
  }

}

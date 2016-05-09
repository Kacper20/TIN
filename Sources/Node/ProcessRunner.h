//
// Created by Kacper Harasim on 09.05.2016.
//

#ifndef TIN_PROCESSRUNNER_H
#define TIN_PROCESSRUNNER_H


#include <string>
#include <unistd.h>

class ProcessRunner {

 public:
  void runProcessAtPath(std::string processFilePath,
                        std::string processErrorPath,
                        std::string processStdOutputPath);
};


#endif //TIN_PROCESSRUNNER_H

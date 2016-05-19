//
// Created by Kacper Harasim on 09.05.2016.
//

#ifndef TIN_PROCESSRUNNER_H
#define TIN_PROCESSRUNNER_H


#include <string>
#include <unistd.h>

//Class that handles all of the interaction with processes that are computing data.

//Instance that is
class ProcessHandler {


 private:
  const std::string processesLocation = "temp";

 public:

  ProcessHandler();
//TODO: Later, we'll be writing process with its harmonogram to the file(json)
  void writeProcessToPersistenceStorage(std::string processContent);
  void runProcessWithIdentifier(std::string processIdentifier);
};


#endif //TIN_PROCESSRUNNER_H

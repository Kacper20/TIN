//
// Created by Kacper Harasim on 09.05.2016.
//

#ifndef TIN_PROCESSRUNNER_H
#define TIN_PROCESSRUNNER_H


#include <string>
#include <unistd.h>
#include "../Shared/MessagesQueue.h"
#include "../Shared/Commands/AddProcessCommand.h"

//Class that handles all of the interaction with processes that are computing data.



//Instance that is
class ProcessHandler {

 private:
  std::condition_variable conditionVariable;
  std::mutex startedProcessMutex;
  const std::string processesLocation = "/Users/kacperh/mod1";
  void writeProcessToPersistenceStorage(std::string processContent);
  void runProcessWithCommand(std::shared_ptr<AddProcessCommand> command);
  std::queue<std::tuple<std::shared_ptr<AddProcessCommand>, int> > runningProcessesQueue;
  MessagesQueue<AddProcessCommand> processesToRunQueue;

 public:

//TODO: Think about transforming AddProcessCommand -> Process to run structure.

  void runProcess(std::shared_ptr<AddProcessCommand> process);
  void startMonitoringForProcessesToRun();
  void monitorProcessesEndings();
//TODO: Later, we'll be writing process with its harmonogram to the file(json)
};


#endif //TIN_PROCESSRUNNER_H

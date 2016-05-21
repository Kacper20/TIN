//
// Created by Kacper Harasim on 09.05.2016.
//

#ifndef TIN_PROCESSRUNNER_H
#define TIN_PROCESSRUNNER_H


#include <string>
#include <unistd.h>
#include "../Shared/MessagesQueue.h"
#include "../Shared/Commands/StartProcessCommand.h"

//Class that handles all of the interaction with processes that are computing data.
#define PROCESSES_BASE_DIRECTORY "/Users/kacperh/Developer/TIN_TEMP"


//Instance that is
class ProcessHandler {

 private:
  std::condition_variable conditionVariable;
  std::mutex startedProcessMutex;
  void writeProcessToPersistentStorage(Json::Value commandJson, const std::string& processContent,
                                       const std::string& identifier);
  void runProcessWithCommand(std::shared_ptr<StartProcessCommand> command, const std::string& basePath);
  std::queue<std::tuple<std::shared_ptr<StartProcessCommand>, int> > runningProcessesQueue;
  MessagesQueue<StartProcessCommand> processesToRunQueue;

 public:

//TODO: Think about transforming StartProcessCommand -> Process to run structure.
  ProcessHandler();
  void runProcess(std::shared_ptr<StartProcessCommand> process);
  void startMonitoringForProcessesToRun();
  void monitorProcessesEndings();
//TODO: Later, we'll be writing process with its harmonogram to the file(json)
};


#endif //TIN_PROCESSRUNNER_H

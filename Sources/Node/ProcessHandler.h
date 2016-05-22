//
// Created by Kacper Harasim on 09.05.2016.
//

#ifndef TIN_PROCESSRUNNER_H
#define TIN_PROCESSRUNNER_H


#include <string>
#include <unistd.h>
#include <set>
#include "../Shared/MessagesQueue.h"
#include "../Shared/Commands/StartProcessCommand.h"
#include "../Shared/Responses/Response.h"

//Class that handles all of the interaction with processes that are computing data.

typedef std::function<void(std::shared_ptr<Response>)> ResponseCompletion;

//Instance that is
class ProcessHandler {

 private:
  std::condition_variable conditionVariable;
  std::mutex startedProcessMutex;
  void writeProcessToPersistentStorage(Json::Value commandJson, const std::string& processContent,
                                       const std::string& identifier);
  void runProcessWithCommand(std::shared_ptr<StartProcessCommand> command, const std::string& basePath);
  std::map<int, std::shared_ptr<StartProcessCommand>> runningProcesses;
  MessagesQueue<StartProcessCommand> processesToRunQueue;

 public:

//TODO: Think about transforming StartProcessCommand -> Process to run structure.
  ProcessHandler();
  void runProcess(std::shared_ptr<StartProcessCommand> process);
  void startMonitoringForProcessesToRun();
  void monitorProcessesEndings(ResponseCompletion responseCompletion);
//TODO: Later, we'll be writing process with its harmonogram to the file(json)
};


#endif //TIN_PROCESSRUNNER_H

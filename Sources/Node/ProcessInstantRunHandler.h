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
#include "../Shared/Commands/StartProcessWithScheduleCommand.h"
#include "../Shared/Commands/LaunchProcessCommand.h"

class ProcessInstantRunHandler;

typedef std::function<void(std::shared_ptr<Response>)> ResponseCompletion;

//Class that handles all of the interaction with processes that are computing data.

class ProcessInstantRunHandler {

  struct ProcessOneTimeRunMonitoringTask {
    ProcessInstantRunHandler &processHandler;
    int pidToWait;
    ResponseCompletion &completion;
    std::shared_ptr<StartProcessCommand> command;
    ProcessOneTimeRunMonitoringTask(ProcessInstantRunHandler &handler,
                          int pidToWait,
                          std::shared_ptr<StartProcessCommand> command,
                          ResponseCompletion &completion) : processHandler(handler),
                                                            pidToWait(pidToWait),
                                                            completion(completion), command(command) { }
    void operator()() {
      processHandler.monitorProcessesEndings(command, pidToWait, completion);
    }
  };

 private:
  std::mutex threadsInfoMutex;

  void runProcessWithCommand(std::shared_ptr<StartProcessCommand> command, const std::string& basePath);

  std::map<int, std::shared_ptr<ProcessOneTimeRunMonitoringTask> > tasksInProgress;
  MessagesQueue<StartProcessCommand> processesToRunQueue;

 public:

//TODO: Think about transforming StartProcessCommand -> Process to run structure.
  ProcessInstantRunHandler();
  ResponseCompletion responseCompletion;
  void runProcess(std::shared_ptr<StartProcessCommand> process);
  void launchProcess(std::shared_ptr<LaunchProcessCommand> process);
  void startMonitoringForProcessesToInstantRun();
  void monitorProcessesEndings(std::shared_ptr<StartProcessCommand>, int pidToWait, ResponseCompletion responseCompletion);
  void removeProcessData(std::string processId);

};




#endif //TIN_PROCESSRUNNER_H

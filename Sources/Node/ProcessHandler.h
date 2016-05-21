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

//Class that handles all of the interaction with processes that are computing data.

typedef std::tuple<std::shared_ptr<StartProcessCommand>, int> CommandWithPid;

struct CommandWithPidCompare {
  bool operator() (const CommandWithPid& lhs, const CommandWithPid& rhs) const
  {
    return std::get<1>(lhs) < std::get<1>(rhs);
  }
};

//Instance that is
class ProcessHandler {

 private:
  std::condition_variable conditionVariable;
  std::mutex startedProcessMutex;
  void writeProcessToPersistentStorage(Json::Value commandJson, const std::string& processContent,
                                       const std::string& identifier);
  void runProcessWithCommand(std::shared_ptr<StartProcessCommand> command, const std::string& basePath);
  std::set<CommandWithPid, CommandWithPidCompare> runningProcesses;
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

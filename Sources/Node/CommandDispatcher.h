//
// Created by Kacper Harasim on 15.05.2016.
//

#ifndef TIN_COMMANDDISPATCHER_H
#define TIN_COMMANDDISPATCHER_H

#include "../Shared/Commands/Command.h"
#include "../Shared/MessagesQueue.h"
#include <queue>
#include <condition_variable>
#include <mutex>
#include "ProcessInstantRunHandler.h"
#include "ProcessScheduledRunHandler.h"
#include "ProcessStatisticsCollector.h"
/*
 * Class that takes care of dispatching methods ie. recognizes them, and performs all of the logic.
 */
typedef std::function<void(std::shared_ptr<Response>)> ResponseCompletion;

class CommandDispatcher {

 private:
  MessagesQueue<Command> queue;
  void processCommandsInfinitely();
  ProcessInstantRunHandler& processInstantRunHandler;
  ProcessScheduledRunHandler& processScheduledRunHandler;
  ProcessStatisticsCollector& collector;

 public:
  ResponseCompletion responseCompletion;

  CommandDispatcher(ProcessInstantRunHandler &processInstantRunHandler,
                    ProcessScheduledRunHandler &processScheduledRunHandler,
                    ProcessStatisticsCollector& collector) :
      processInstantRunHandler(processInstantRunHandler), processScheduledRunHandler(processScheduledRunHandler),
      collector(collector) { }
  void processCommand(std::shared_ptr<Command>);
  void startDispatching();
};


#endif //TIN_COMMANDDISPATCHER_H

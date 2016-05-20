//
// Created by Kacper Harasim on 15.05.2016.
//

#ifndef TIN_COMMANDDISPATCHER_H
#define TIN_COMMANDDISPATCHER_H

#include "../Shared/Commands/Command.h"
#include <queue>
#include <condition_variable>
#include <mutex>
#include <memory>
/*
 * Class that takes care of dispatching methods ie. recognizes them, and performs all of the logic.
 */


class CommandDispatcher {

 private:
  std::queue<Command> commandsQueue;
  std::condition_variable conditionVariable;
  std::mutex mutex;
  void processCommandFromQueue();
 public:

  void addCommandToQueue(std::shared_ptr<Command> commandToExecute);
  void startLookingForTasks();
};


#endif //TIN_COMMANDDISPATCHER_H

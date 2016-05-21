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
#include "ProcessHandler.h"
/*
 * Class that takes care of dispatching methods ie. recognizes them, and performs all of the logic.
 */


class CommandDispatcher {

 private:
  MessagesQueue<Command> queue;
  void processCommandsInfinitely();
  ProcessHandler& handler;
 public:

  CommandDispatcher(ProcessHandler& handler): handler(handler) {}
  void processCommand(std::shared_ptr<Command>);
  void startDispatching();

};


#endif //TIN_COMMANDDISPATCHER_H

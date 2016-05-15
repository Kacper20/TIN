//
// Created by Kacper Harasim on 15.05.2016.
//

#ifndef TIN_COMMANDDISPATCHER_H
#define TIN_COMMANDDISPATCHER_H

#include "../Shared/Commands/Command.h"
/*
 * Class that takes care of dispatching methods ie. recognizes them, and performs all of the logic.
 */
class CommandDispatcher {

 public:
  void addCommandToQueue(std::shared_ptr<Command> commandToExecute);
};


#endif //TIN_COMMANDDISPATCHER_H

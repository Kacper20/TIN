//
// Created by Kacper Harasim on 15.05.2016.
//

#include "CommandDispatcher.h"

//TODO: Extract queue to another object - synchronized queue. This way it'll be easy to use ;)
void CommandDispatcher::addCommandToQueue(std::shared_ptr<Command> commandToExecute) {
  std::unique_lock<std::mutex> lock(mutex);
  commandsQueue.push(*commandToExecute);
  conditionVariable.notify_one();
}

void CommandDispatcher::startLookingForTasks() {
  processCommandFromQueue();
  return;
}

void CommandDispatcher::processCommandFromQueue() {
  std::unique_lock<std::mutex> lock(mutex);
  conditionVariable.wait(lock, [this]() { return !(this->commandsQueue.empty()); });
  Command received =  commandsQueue.front();
  commandsQueue.pop();
  //TODO: Do action with command
  processCommandFromQueue();
}

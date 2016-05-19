#include <iostream>
#include <thread>
#include "CommandsDeserializer.h"
#include "CommandDispatcher.h"
#include "NodeServer.h"
using namespace std;

struct ServerReceivingTask {
  NodeServer server;
  ServerReceivingTask(NodeServer server): server(server) {}
  void operator() () {
    server.startReceiving();
  }
};

struct CommandsDispatchingTask {
  CommandDispatcher* dispatcher;
  CommandsDispatchingTask(CommandDispatcher* dispatcher) {
    this->dispatcher = dispatcher;
  }
  void operator() () {
    dispatcher->startLookingForTasks();
  }
};

int main() {

  CommandDispatcher dispatcher;
  NodeServer server = NodeServer([&dispatcher](std::shared_ptr<Command> commandToDispatch) {
    //WARN: It's called from another thread -
    std::cout << "Ready to dispatch" << std::endl;
    dispatcher.addCommandToQueue(commandToDispatch);
  });
  CommandsDispatchingTask dispatcherTask(&dispatcher);
  std::thread dispatcherThread(dispatcherTask);

  ServerReceivingTask serverTask(server);
  std::thread serverThread(serverTask);
  serverThread.join();
  dispatcherThread.join();
}
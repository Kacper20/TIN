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

int main() {

  CommandDispatcher dispatcher = CommandDispatcher();
  NodeServer server = NodeServer([](std::shared_ptr<Command> commandToDispatch) {
    //WARN: It's called from another thread -
    //TODO: Add it to dispatcher queue :-) This queue adding should run on ANOTHER thread so that main is only synchronizing everything
    std::cout << "Ready to dispatch" << std::endl;
    dispatcher.addCommandToQueue(commandToDispatch);
  });

  ServerReceivingTask task(server);
  std::thread serverThread(task);
  serverThread.join();
}
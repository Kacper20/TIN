#include <iostream>
#include <thread>
#include "NodeNetworkLayer.h"
#include "CommandsDeserializer.h"
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

  NodeServer server = NodeServer([](std::shared_ptr<Command> commandToDispatch) {
    //WARN: It's called from another thread -
    //TODO: Add it to dispatcher queue :-)
    std::cout << "Ready to dispatch" << std::endl;
  });
  cout << "Hello, World!" << endl;

  ServerReceivingTask task(server);
  std::thread serverThread(task);
  serverThread.join();

  std::cout << "END EXEC" << std::endl;
}
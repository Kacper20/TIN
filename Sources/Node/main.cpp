#include <iostream>
#include <thread>
#include "CommandsDeserializer.h"
#include "CommandDispatcher.h"
#include "NodeServer.h"
#include <csignal>
using namespace std;

struct ServerReceivingTask {
  NodeServer server;
  ServerReceivingTask(NodeServer server): server(server) {}
  void operator() () {
    server.startReceiving();
  }
};

struct CommandsDispatchingTask {
  CommandDispatcher& dispatcher;
  CommandsDispatchingTask(CommandDispatcher& dispatcher): dispatcher(dispatcher) {}
  void operator() () {
    dispatcher.startDispatching();
  }
};

struct ProcessRunningTask {
  ProcessHandler &processHandler;
  ProcessRunningTask(ProcessHandler &handler): processHandler(handler) {}
  void operator() () {
    processHandler.startMonitoringForProcessesToRun();
  }
};

struct ProcessMonitoringTask {
  ProcessHandler& processHandler;
  ProcessMonitoringTask(ProcessHandler &handler) : processHandler(handler) {}
  void operator() () {
    processHandler.monitorProcessesEndings();
  }
};

int main() {

  ProcessHandler handler;
  CommandDispatcher dispatcher(handler);

  NodeServer server = NodeServer([&dispatcher](std::shared_ptr<Command> commandToDispatch) {
    //WARN: It's called from another thread -
    std::cout << "Ready to dispatch" << std::endl;
    dispatcher.processCommand(commandToDispatch);
  });

  ProcessMonitoringTask processMonitoringTask(handler);
  std::thread processMonitoringThread(processMonitoringTask);

  ProcessRunningTask processRunningTask(handler);
  std::thread processRunningThread(processRunningTask);

  CommandsDispatchingTask dispatcherTask(dispatcher);
  std::thread dispatcherThread(dispatcherTask);

  ServerReceivingTask serverTask(server);
  std::thread serverThread(serverTask);

  processMonitoringThread.join();
  processRunningThread.join();
  serverThread.join();
  dispatcherThread.join();
}
#include <iostream>
#include <thread>
#include "CommandsDeserializer.h"
#include "CommandDispatcher.h"
#include "NodeServer.h"
#include <csignal>
using namespace std;

void signalChildTerminate(int signum) {
  pid_t childPid;
  std::cout << "Signal CHLD procedure\n";
  int status;
  while ((childPid = waitpid(-1, &status, WNOHANG)) > 0) {
    std::cout << "Child ended!!";
  }
}

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
  ProcessMonitoringTask
};

int main() {

  std::signal(SIGCHLD, signalChildTerminate);


  ProcessHandler handler;
  CommandDispatcher dispatcher(handler);

  NodeServer server = NodeServer([&dispatcher](std::shared_ptr<Command> commandToDispatch) {
    //WARN: It's called from another thread -
    std::cout << "Ready to dispatch" << std::endl;
    dispatcher.processCommand(commandToDispatch);
  });

  ProcessRunningTask processRunningTask(handler);
  std::thread processRunningThread(processRunningTask);

  CommandsDispatchingTask dispatcherTask(dispatcher);
  std::thread dispatcherThread(dispatcherTask);

  ServerReceivingTask serverTask(server);
  std::thread serverThread(serverTask);
  processRunningThread.join();
  serverThread.join();
  dispatcherThread.join();
}
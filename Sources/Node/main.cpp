#include <iostream>
#include <thread>
#include "CommandsDeserializer.h"
#include "CommandDispatcher.h"
#include "NodeServer.h"
#import "../Shared/Responses/Response.h"
using namespace std;

typedef std::function<void(std::shared_ptr<Response>)> ResponseCompletion;

struct ServerReceivingTask {
  NodeServer& server;
  ServerReceivingTask(NodeServer& server): server(server) {}
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

struct ServerSendingTask {
  NodeServer &server;
  ServerSendingTask(NodeServer &server): server(server) {}
  void operator() () {
    server.startMonitorForSendings();
  }
};

int main() {

  ProcessHandler handler;
  CommandDispatcher dispatcher(handler);

  std::shared_ptr<NodeServer> server = std::make_shared<NodeServer>([&dispatcher](std::shared_ptr<Command> commandToDispatch) {
    //WARN: It's called from another thread -
    dispatcher.processCommand(commandToDispatch);
  });

  handler.responseCompletion = [&server](std::shared_ptr<Response> response) {
    server->sendResponse(response);
  };

  ServerSendingTask serverSendingTask(*server);
  std::thread serverSendingThread(serverSendingTask);


  ProcessRunningTask processRunningTask(handler);
  std::thread processRunningThread(processRunningTask);

  CommandsDispatchingTask dispatcherTask(dispatcher);
  std::thread dispatcherThread(dispatcherTask);

  ServerReceivingTask serverTask(*server);
  std::thread serverThread(serverTask);

  serverSendingThread.join();
  processRunningThread.join();
  serverThread.join();
  dispatcherThread.join();
}
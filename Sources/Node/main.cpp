#include <iostream>
#include <thread>
#include "CommandsDeserializer.h"
#include "CommandDispatcher.h"
#include "NodeServer.h"
#import "../Shared/Responses/Response.h"
#include "../Shared/DateUtilities.h"
#include "ProcessScheduledRunHandler.h"
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
  ProcessInstantRunHandler &processHandler;
  ProcessRunningTask(ProcessInstantRunHandler &handler): processHandler(handler) {}
  void operator() () {
    processHandler.startMonitoringForProcessesToInstantRun();
  }
};

struct ProcessSchedulingTask {
  ProcessScheduledRunHandler &processHandler;
  ProcessSchedulingTask(ProcessScheduledRunHandler &handler): processHandler(handler) {}
  void operator() () {
    processHandler.monitorScheduledProcessesToRun();
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

  ProcessInstantRunHandler instantRunHandler;
  ProcessScheduledRunHandler scheduledRunHandler;
  CommandDispatcher dispatcher(instantRunHandler, scheduledRunHandler);

  std::shared_ptr<NodeServer> server = std::make_shared<NodeServer>([&dispatcher](std::shared_ptr<Command> commandToDispatch) {
    //WARN: It's called from another thread -
    dispatcher.processCommand(commandToDispatch);
  });

  instantRunHandler.responseCompletion = [&server](std::shared_ptr<Response> response) {
    server->sendResponse(response);
  };

  scheduledRunHandler.responseCompletion = [&server](std::shared_ptr<Response> response) {
    server->sendResponse(response);
  };

  ProcessSchedulingTask processSchedulingTask(scheduledRunHandler);
  std::thread processSchedulingThread(processSchedulingTask);

  ServerSendingTask serverSendingTask(*server);
  std::thread serverSendingThread(serverSendingTask);


  ProcessRunningTask processRunningTask(instantRunHandler);
  std::thread processRunningThread(processRunningTask);

  CommandsDispatchingTask dispatcherTask(dispatcher);
  std::thread dispatcherThread(dispatcherTask);

  ServerReceivingTask serverTask(*server);
  std::thread serverThread(serverTask);

  processSchedulingThread.join();
  serverSendingThread.join();
  processRunningThread.join();
  serverThread.join();
  dispatcherThread.join();
}
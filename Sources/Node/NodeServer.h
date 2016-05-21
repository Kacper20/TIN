//
// Created by Kacper Harasim on 15.05.2016.
//

#ifndef TIN_NODESERVER_H
#define TIN_NODESERVER_H
#include "../Shared/Commands/Command.h"
#include "../Shared/Responses/Response.h"
#include "../Shared/MessagesQueue.h"
#include "NodeNetworkLayer.h"

class NodeServer {

 private:
  //TODO: Maybe give something different like queue to synchronize it in a better way? Reference to queue of commands in which commands will land :-)
  std::function<void(std::shared_ptr<Command>)> receivedMessageFunc;
  MessagesQueue<Response> messagesToSendQueue;
  NodeNetworkLayer layer = NodeNetworkLayer();
 public:
  NodeServer(std::function<void(std::shared_ptr<Command>)> completionFunc) : receivedMessageFunc(completionFunc) {}
  void startReceiving();
  void sendResponse(std::shared_ptr<Response> response);
  void startMonitorForSendings();
};


#endif //TIN_NODESERVER_H

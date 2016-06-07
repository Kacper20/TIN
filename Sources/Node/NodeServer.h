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
  std::function<void(std::shared_ptr<Command>)> receivedMessageFunc;
  MessagesQueue<Response> messagesToSendQueue;
  NodeNetworkLayer layer;
  int portNumber;

 public:
  NodeServer(int portNumber, std::function<void(std::shared_ptr<Command>)> completionFunc) : receivedMessageFunc(completionFunc),
  portNumber(portNumber), layer(NodeNetworkLayer(portNumber)){}
  void startReceiving();
  void sendResponse(std::shared_ptr<Response> response);
  void startMonitorForSendings();
};


#endif //TIN_NODESERVER_H

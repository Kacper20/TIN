//
// Created by Rafal Rzeuski on 5/21/16.
//

#ifndef TIN_SERVER_H
#define TIN_SERVER_H

#include "../Shared/Commands/Command.h"
#include "../Shared/MessagesQueue.h"
#include "../Shared/Responses/Response.h"
#include "NodeListener.h"
#include "AdminListener.h"
#include "NodeSender.h"
#include "AdminSender.h"
#include "ServerNetworkLayer.h"

#include <memory>

class Server {
  // Does this make sense?
  MessagesQueue<std::string> AdminNodeQ;
  AdminListener aListener;

  //TODO: Node_s_, a container of sockets
  TCPSocket node;
  TCPSocket admin;

 public:
};

#endif // TIN_SERVER_H

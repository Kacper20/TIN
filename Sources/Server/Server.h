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
  MessagesQueue<std::string> adminNodeQ;
  MessagesQueue<std::string> nodeAdminQ;

  // Maybe these would be more readable, and their initialization would be easier,
  // if they were just methods of this class and not separate function objects
  AdminListener aListener;
  NodeSender nSender;
  NodeListener nListener;
  AdminSender aSender;

  // TODO: Node_S_, a container of sockets
  // TODO: (Not sure about this yet, need to discuss with the team) add a way to remember state, as in: which socket each process was sent to
  TCPSocket nodeSocket;
  TCPSocket* adminSocket;

 public:
  Server() : adminSocket(nullptr), aListener(adminSocket, adminNodeQ), nSender(nodeSocket, adminNodeQ),
             nListener(nodeSocket, nodeAdminQ), aSender(adminSocket, nodeAdminQ) {}
  void connectToNodes();
};

#endif // TIN_SERVER_H

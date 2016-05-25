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
#include <condition_variable>
#include <mutex>

class Server {
  // Queues used for passing messages between threads
  // Messages receive from the Administrator that should be sent to Nodes
  MessagesQueue<std::string> adminNodeQ;
  // Messages receive from Nodes that should reach the Administrator
  MessagesQueue<std::string> nodeAdminQ;

  // TODO: A container of sockets so we can have multiple nodes in the system (work in progress).
//  std::vector<TCPSocket*> nodeSockets;
//  std::vector<SocketAddress> nodeAddresses;
  // TODO: Add a way to remember state, as in: which socket each process was sent to and the process' id.
  TCPSocket adminSocket;
  TCPSocket nodeSocket;
  MessageNetworkManager adminMessageManager;
  std::condition_variable adminConnected;
  bool connectedToAdmin;

  void prepareAddresses();
  void connectToNodes();
  void waitForAdminToConnect();

  // Functions that will be run in parallel
  void receiveFromAdmin();
  void receiveFromNodes();
  void sendToAdmin();
  void sendToNodes();

  // Temporary functions to make testing easier
  void pushMessage(const std::string);
  void fakeAdminFunction();
  bool fake_admin;

 public:
  Server(bool);
  void run();
};

#endif // TIN_SERVER_H
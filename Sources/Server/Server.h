//
// Created by Rafal Rzeuski on 5/21/16.
//

#ifndef TIN_SERVER_H
#define TIN_SERVER_H

#include "../Shared/Commands/Command.h"
#include "../Shared/MessagesQueue.h"
#include "../Shared/Responses/Response.h"
#include "../Shared/MessageNetworkManager.h"

#include <memory>
#include <condition_variable>
#include <mutex>

class Server {
  // Queues used for passing messages between threads
  // Messages receive from the Administrator that should be sent to Nodes
  MessagesQueue<std::string> adminNodeQ;
  // Messages receive from Nodes that should reach the Administrator
  MessagesQueue<std::string> nodeAdminQ;

  // All the TCPSockets that will be connected to nodes
  std::vector<TCPSocket> nodeSockets;
  // The corresponding IP addresses
  std::vector<SocketAddress> nodeAddresses;
  // An object that simplifies sending and receiving messages for each node
  std::vector<MessageNetworkManager> nodeManagers;
  // For mapping process identifiers to Nodes, so we know where each process was sent to
  std::map<std::string, int> processNodeMap;
  TCPSocket adminSocket;
  MessageNetworkManager adminMessageManager;
  std::condition_variable adminConnected;
  bool connectedToAdmin;

  void prepareAddresses();
  void connectToNodes();
  void prepareNodeManagers();
  void waitForAdminToConnect();
  std::pair<std::string, bool> analyzeJson(const std::string&);

  // Functions that will be run in parallel
  void receiveFromAdmin();
  void receiveFromNodes();
  void sendToAdmin();
  void sendToNodes();

  // Temporary functions to make testing easier
  void pushFakeMessage(const std::string);
  void fakeAdminFunction();
  bool fake_admin;

 public:
  // A rather spartan public interface
  Server(bool);
  void run();
};

#endif // TIN_SERVER_H
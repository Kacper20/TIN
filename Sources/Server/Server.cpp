//
// Created by Rafal Rzeuski on 5/21/16.
//

#include "Server.h"
#include "../Shared/Commands/StartProcessCommand.h"
#include "../Shared/Commands/StartProcessWithScheduleCommand.h"

#include <thread>
#include <fcntl.h>

Server::Server(bool admin) : connectedToAdmin(false), fake_admin(admin) {
  prepareAddresses();
  connectToNodes();
  prepareNodeManagers();

  // For testing purposes
//  Json::FastWriter fastWriter;
//  std::string processContent = "#!/bin/bash\necho \"Hello World\"\necho $(date)\n";
//  StartProcessCommand command = StartProcessCommand("666", processContent);
//  std::string output = fastWriter.write(command.generateJSON());
//  adminNodeQ.push(std::shared_ptr<std::string>(new std::string(output)));
}

void Server::pushMessage(const std::string s) {
  static int processId = 666;
  std::stringstream ss;
  ss << processId;
  std::string finalId = ss.str();
  processId++;
  Json::FastWriter fastWriter;
  std::string processContent = "#!/bin/bash\necho \"Hello World\"\necho $(date)\n";
  if(s == "s") {
    StartProcessCommand command(finalId, processContent);
    std::string output = fastWriter.write(command.generateJSON());
    std::cout << "Pushing message : " << output << std::endl;
    adminNodeQ.push(std::shared_ptr<std::string>(new std::string(output)));
  }
  else if(s == "h") {
    std::vector<int> timeStamps{3600, 4800};
    Schedule sched(timeStamps);
    StartProcessWithScheduleCommand command(finalId, processContent, sched);
    std::string output = fastWriter.write(command.generateJSON());
    std::cout << "Pushing message : " << output << std::endl;
    adminNodeQ.push(std::shared_ptr<std::string>(new std::string(output)));
  }
}

void Server::fakeAdminFunction() {
  while(true) {
    std::string input;
    std::cin >> input;
    pushMessage(input);
  }
}

void Server::prepareAddresses() {
  // 3 seems like a reasonable number of nodes for now
  nodeAddresses.push_back(SocketAddress("127.0.0.1:40617"));
  nodeAddresses.push_back(SocketAddress("127.0.0.1:40667"));
  nodeAddresses.push_back(SocketAddress("127.0.0.1:40668"));
}

void Server::connectToNodes() {
  // TODO: Multiple nodes
//  SocketAddress nodeAddress("127.0.0.1:40666");
//  if(nodeSocket.connect(nodeSocket.internalDescriptor(), nodeAddress) == -1) {
//    perror("Couldn't connect to Node, exiting");
//    exit(-1);
//  }

  // Make the sockets non-blocking so we can perform a receive() on all of them in succession.
  // TODO: Use select() when receiving instead of making the sockets non-blocking?
  for(auto p : nodeSockets) {
    fcntl(p.internalDescriptor(), F_SETFL, O_NONBLOCK);
  }

  for(int i = 0; i < nodeAddresses.size(); i++) {
    nodeSockets.push_back(TCPSocket());
    if(nodeSockets[i].connect(nodeSockets[i].internalDescriptor(), nodeAddresses[i]) == -1) {
//      perror("Couldn't connect to a Node, exiting");
//      exit(-1);
      // If we can't connect to a Node, we can just pop it out of the vector!
      std::cerr << "Couldn't connect to one of the Nodes, ignore it" << std::endl;
      nodeSockets.pop_back();
    }
    else {
      std::cout << "Connected to Node under the index of: " << i << std::endl;
    }
  }
}

void Server::prepareNodeManagers() {
  for(auto p : nodeSockets) {
    nodeManagers.push_back(MessageNetworkManager(p));
  }
}

void Server::waitForAdminToConnect() {
  //TODO: Error checking, bool return value for success checking?
  TCPSocket listeningSocket;
  SocketAddress myAddress = SocketAddress("127.0.0.1:1666");
  std::cout << "Binding listeningSocket to address\n";
  if (listeningSocket.bind(myAddress) == -1) {
    perror("Error while binding occured");
    exit(-1);
  }
  std::cout <<"Binded successfuly\n";
  if (listeningSocket.listen(1) == -1 ) {
    perror("Error while listening occured");
    exit(-1);
  }
  std::cout << "Listen called\n";
  int newDescriptor = listeningSocket.accept();
  if (newDescriptor == -1) {
    perror("Error while accepting connection");
    exit(-1);
  }
  adminSocket = TCPSocket(newDescriptor);

  std::cout << "Accepted connection\n";
  //Close listeningSocket that was listening - we only support one client by design.
  listeningSocket.close();
  std::cout << "Closing listeningSocket" << std::endl;
  return;
}

void Server::run() {
  std::thread receiveFromAdminThread;
  if(fake_admin) {
    receiveFromAdminThread = std::thread(&Server::fakeAdminFunction, this);
  }
  else {
    receiveFromAdminThread = std::thread(&Server::receiveFromAdmin, this);
  }
  std::thread sendToAdminThread(&Server::sendToAdmin, this);
  std::thread receiveFromNodesThread(&Server::receiveFromNodes, this);
  std::thread sendToNodesThread(&Server::sendToNodes, this);

  std::cout << "All threads started, have fun!" << std::endl;

  receiveFromAdminThread.join();
  sendToAdminThread.join();
  receiveFromNodesThread.join();
  sendToNodesThread.join();
}

void Server::receiveFromAdmin() {
  waitForAdminToConnect();
  adminMessageManager = MessageNetworkManager(adminSocket);
  adminConnected.notify_one();
  std::string buffer;

  while (true) {
    ssize_t messageSize = adminMessageManager.receiveMessage(buffer);
    if (messageSize < 0) {
      //Something's wrong!
      continue;
    }
    // Put the message into outgoing queue
    std::shared_ptr<std::string> message(new std::string(buffer));
    adminNodeQ.push(message);
  }
}

void Server::sendToAdmin() {
  // Wait for the AdminListener thread to connect to the Administrator module
  // But ONLY if the connection hasn't been already established. We need to make sure we won't wait() on this condition
  // variable after the other thread called notify_one()!
  if(!connectedToAdmin) {
    std::cout << "Send To Admin: waiting for admin to connect!" << std::endl;
    std::mutex m;
    std::unique_lock<std::mutex> lock(m);
    adminConnected.wait(lock);
  }

  while(true) {
    std::shared_ptr<std::string> message = nodeAdminQ.pop();
    adminMessageManager.sendMessage(*message);
  }
}

void Server::receiveFromNodes() {
  // TODO: Make this a loop that checks all Node sockets for messages using non-blocking read()
  // I should probably change the sockets used for talking with Nodes to be non-blocking when I first set them up
  // That would require adjusting the MessageNetworkManager class a a bit
  // Or just implement it here.
  // Actually, MessageNetworkManager already returns -1 if it gets a -1 form the receive function (which is just a wrapper for recv(),
  // So I'm _probably_ good if I just check for that.
  // Ooor use the select() function and decide which sockets to ask for stuff based on its results

  // ...

  std::string buffer;
  while(true) {
    ssize_t messageSize = nodeManagers[0].receiveMessage(buffer, true);
    if (messageSize < 0) {
      continue;
    }
    if (messageSize != 0) {
      std::cout << "Receive From Nodes, message received : " << buffer << std::endl;
      std::shared_ptr<std::string> message(new std::string(buffer));
      nodeAdminQ.push(message);
    }
  }
//
//  while(true) {
//    for(int i = 0; i < nodeSockets.size(); i++) {
//      ssize_t messageSize = nodeManagers[i].receiveMessage(buffer, true);
//      if(messageSize == -1) {
//         Nothing to receive, go to next socket
//        continue;
//      }
//      if(messageSize != 0) {
//        std::cout << "Receive From Nodes, message received : " << buffer << std::endl;
//        std::shared_ptr<std::string> message(new std::string(buffer));
//        nodeAdminQ.push(message);
//      }
//    }
//  }
}

void Server::sendToNodes() {
  static int currentNode = 0;
  while(true) {
    // MessagesQueue does all the concurrency work for us - no need to worry about it
    std::shared_ptr<std::string> message = adminNodeQ.pop();
    // TODO: Decide which Node we should send the message to!
    nodeManagers[0].sendMessage(*message);
  }
}

int Server::checkAdminMessageContents(const std::string& msg) {
  // TODO: Work in progress.
  Json::Reader reader;
  Json::Value root;
  reader.parse(msg, root);
  if(root["commandType"] == "startNewProcess" || root["commandType"] == "startNewProcessWithSchedule") {
    // It's a new process - send it to a Node
    return -1;
  }
  // It's a query - choose which Node to send it to
}
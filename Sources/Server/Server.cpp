//
// Created by Rafal Rzeuski on 5/21/16.
//

#include "Server.h"
#include "../Shared/Commands/StartProcessCommand.h"

#include <thread>
#include <cassert>

Server::Server() : connectedToAdmin(false) {
  prepareSockets();
  connectToNodes();

  // For testing purposes
  Json::FastWriter fastWriter;
  std::string processContent = "#!/bin/bash\necho \"Hello World\"\necho $(date)\n";
  StartProcessCommand command = StartProcessCommand("666", processContent);
  std::string output = fastWriter.write(command.generateJSON());
  adminNodeQ.push(std::shared_ptr<std::string>(new std::string(output)));
}

void Server::prepareSockets() {
  // TODO: Implement
//  nodeAddresses.push_back(SocketAddress("127.0.0.1:40666"));
//  nodeAddresses.push_back(SocketAddress("127.0.0.1:40667"));
//  nodeAddresses.push_back(SocketAddress("127.0.0.1:40668"));
}

void Server::connectToNodes() {
  // TODO: Multiple nodes
  SocketAddress nodeAddress("127.0.0.1:40667");
  if(nodeSocket.connect(nodeSocket.internalDescriptor(), nodeAddress) == -1) {
    perror("Couldn't connect to Node, exiting");
    exit(-1);
  }
}

void Server::waitForAdminToConnect() {
  // TODO: Condition variable for the sender thread
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
  std::thread receiveFromAdminThread(&Server::receiveFromAdmin, this);
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
  waitForAdminToConnect(); // TODO: Move to constructor/somewhere else entirely?
  adminMessageManager = MessageNetworkManager(adminSocket);
  adminConnected.notify_one();
  std::string buffer;

  while(true) {
    std::cout << "Receive From Admin!\n";
    std::chrono::duration<int> s(2);
    std::this_thread::sleep_for(s);

    ssize_t messageSize = adminMessageManager.receiveMessage(buffer);
    if(messageSize < 0) {
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
    std::cout << "Send To Admin!\n";
    std::chrono::duration<int> s(2);
    std::this_thread::sleep_for(s);
    std::shared_ptr<std::string> message = nodeAdminQ.pop();
    adminMessageManager.sendMessage(*message);
  }
}

void Server::receiveFromNodes() {
  // TODO: Make this a loop that checks all Node sockets for messages using non-blocking read()
  // I should probably change the sockets used for talking with Nodes to be non-blocking when I first set them up
  // That would require adjusting the MessageNetworkManager class a a bit
  // Ooor use the select() function and decide which sockets to ask for stuff based on its results

  // ...

  // But for now, since we only have one socket, let's just ask it to receive some stuff for us
  MessageNetworkManager manager(nodeSocket);
  std::string buffer;
  while(true) {

    std::cout << "Receive From Nodes!\n";
    std::chrono::duration<int> s(2);
    std::this_thread::sleep_for(s);

    ssize_t messageSize = manager.receiveMessage(buffer, true);
    if(messageSize < 0) {
      // TODO: error checking
      continue;
    }
    if(messageSize != 0) {
      std::cout << "Receive From Nodes, message received : " << buffer << std::endl;
      // Put the message into the queue
      std::shared_ptr<std::string> message(new std::string(buffer));
      nodeAdminQ.push(message);
    }
  }
}

void Server::sendToNodes() {
  // TODO: Make the MessageNetworkManagers part of the class, so we don't create multiple for the same socket?
  MessageNetworkManager manager(nodeSocket);
  while(true) {
    std::cout << "Send To Nodes!\n";
    // MessagesQueue does all the concurrency work for us - no need to worry about it
    std::shared_ptr<std::string> message = adminNodeQ.pop();
    // TODO: Decide which Node we should send the message to!
    manager.sendMessage(*message);
  }
}
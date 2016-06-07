//
// Created by Rafal Rzeuski on 5/21/16.
//

#include "Server.h"
#include "../Shared/Commands/StartProcessCommand.h"
#include "../Shared/Commands/StartProcessWithScheduleCommand.h"

#include <thread>

Server::Server(bool admin) : connectedToAdmin(false), fake_admin(admin) {
  prepareAddresses();
  connectToNodes();
  prepareNodeManagers();
}

void Server::pushFakeMessage(const std::string s) {
  static int processId = 666;
  std::stringstream ss;
  ss << processId;
  std::string finalId = ss.str();
  processId++;
  Json::FastWriter fastWriter;
  std::string processContent = "#!/bin/bash\necho \"Hello World\"\necho $(date)\n";
  if(s == "q") {
    exit(0);
  }
  else if(s == "s") {
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
  else if(s[0] == 'd') {
    std::string deleteMsg = "{\"commandType\" : \"deleteProcess\"\"processDetails\" : {\"processIdentifier\" :";
    deleteMsg += s[1];
    deleteMsg += s[2];
    deleteMsg += s[3];
    deleteMsg += ";}}";
    std::cout << "Pushing message : " << deleteMsg << std::endl;
    adminNodeQ.push(std::shared_ptr<std::string>(new std::string(deleteMsg)));
  }
}

void Server::fakeAdminFunction() {
  while(true) {
    std::string input;
    std::cin >> input;
    pushFakeMessage(input);
  }
}

void Server::prepareAddresses() {
  nodeAddresses.push_back(SocketAddress("127.0.0.1:40500"));
  nodeAddresses.push_back(SocketAddress("127.0.0.1:40501"));
  nodeAddresses.push_back(SocketAddress("127.0.0.1:40646"));
  nodeAddresses.push_back(SocketAddress("127.0.0.1:40636"));
}

// Connect to all the (hardcoded) addresses. If we can't connect to one of them, it's not a problem - this function can handle it.
// If we can't connect to any of them, the application will exit with an error message.
void Server::connectToNodes() {
  for(int i = 0; i < nodeAddresses.size(); i++) {
    nodeSockets.push_back(TCPSocket());
    if(nodeSockets.back().connect(nodeSockets.back().internalDescriptor(), nodeAddresses[i]) == -1) {
       // If we can't connect to a Node, we can just pop it out of the vector!
      std::cerr << "Couldn't connect to one of the Nodes, ignoring it" << std::endl;
      nodeSockets.pop_back();
    }
    else {
      std::cout << "Connected to the node with the index of: " << nodeSockets.size() - 1 << std::endl;
    }
  }
  if(nodeSockets.empty()) {
    std::cerr << "Couldn't connect to any of the nodes, exiting!" << std::endl;
    exit(-1);
  }
}

void Server::prepareNodeManagers() {
  for(auto p : nodeSockets) {
    nodeManagers.push_back(MessageNetworkManager(p));
  }
}

void Server::waitForAdminToConnect() {
  TCPSocket listeningSocket;
  SocketAddress myAddress = SocketAddress("127.0.0.1:1666");
  if (listeningSocket.bind(myAddress) == -1) {
    perror("ADMIN : Error while binding occured");
    exit(-1);
  }
  if (listeningSocket.listen(1) == -1 ) {
    perror("ADMIN : Error while listening occured");
    exit(-1);
  }
  std::cout << "Listening for connection from ADMIN\n";
  int newDescriptor = listeningSocket.accept();
  if (newDescriptor == -1) {
    perror("ADMIN : Error while accepting connection");
    exit(-1);
  }
  adminSocket = TCPSocket(newDescriptor);
  connectedToAdmin = true;

  std::cout << "Accepted connection from ADMIN\n";
  //Close listeningSocket that was listening - we only support one client by design.
  listeningSocket.close();
  return;
}

// Creates a separate thread for each part of the system's communication
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
  std::string buffer;
  while (true) {
    if(!connectedToAdmin) {
      waitForAdminToConnect();
      adminMessageManager = MessageNetworkManager(adminSocket);
      adminConnected.notify_one();
    }
    else {
      ssize_t messageSize = adminMessageManager.receiveMessage(buffer);
      if (messageSize > 0) {
        // We received a message, now we need to put it into the right queue
        std::cout << "Received message from ADMIN!" << std::endl;
        std::shared_ptr<std::string> message(new std::string(buffer));
        adminNodeQ.push(message);
      }
      else if (messageSize == 0) {
        // recv() returns 0 if the remote side has closed the connection on us!
        // If the Administrator module decided to disconnect, we need to handle it and start listening for a new connection
        std::cout << "ADMIN disconnected! Starting to listen for new connection..." << std::endl;
        connectedToAdmin = false;
        adminSocket.close(); // close this socket, we don't need it anymore
      }
    }
  }
}

void Server::sendToAdmin() {
  while(true) {
    // Wait for the AdminListener thread to connect to the Administrator module
    // But ONLY if the connection hasn't been already established. We need to make sure we won't wait() on this condition
    // variable after the other thread called notify_one()!
    if(!connectedToAdmin) {
      std::cout << "Send To Admin Thread: waiting for admin to connect!" << std::endl;
      std::mutex m;
      std::unique_lock<std::mutex> lock(m);
      adminConnected.wait(lock);
    }
    // We are connected and can proceed with sending messages to the administrator
    else {
      std::shared_ptr<std::string> message = nodeAdminQ.pop();
      std::cout << "Sending a message to ADMIN" << std::endl;
      int bytesSent = adminMessageManager.sendMessage(*message);
      if (bytesSent == -1) {
        // send() returns -1 and sets errno to EPIPE (broken pipe) if the other side decided to give us the boot
        if (errno == EPIPE) {
          // We better put the message back into the queue, lest we lose it!
          nodeAdminQ.push(message);
          // We are tired and want to catch some z's.
          // Making sure the boolean connectedToAdmin is false will allow us to do that on the next iteration of the while loop.
          connectedToAdmin = false;
        }
        else {
          // Something bad happened - an error occurred while sending, but it's not EPIPE. What now?
          exit(-616);
        }
      }
    }
  }
}

void Server::receiveFromNodes() {
  while(true) {
    fd_set readyToRead;
    int top_fd = -100;
    for(auto p : nodeSockets) {
      FD_SET(p.internalDescriptor(), &readyToRead);
      if(p.internalDescriptor() > top_fd) {
        top_fd = p.internalDescriptor();
      }
    }
    struct timeval timeout;
    // Timeout immediately - just poll
    timeout.tv_sec = INT32_MAX;
    timeout.tv_usec = 0;
    select(top_fd + 1, &readyToRead, nullptr, nullptr, &timeout);
    // readyToRead should now contain all the fd-s that we can read from, so let's do that
    // Am I making any sense?
    for(auto p : nodeSockets) {
      if(FD_ISSET(p.internalDescriptor(), &readyToRead)) {
        // The socket's fd is in the set, so let's call receive on it
        // We need to find it's MessageMenager, which sucks. But those are not that important! It will be easier and probably faster
        // to just make a new one here.
        MessageNetworkManager manager(p);
        std::string buffer;
        manager.receiveMessage(buffer, true);
        std::cout << "Received a message from a node : \n" << buffer << std::endl;
        std::shared_ptr<std::string> message(new std::string(buffer));
        nodeAdminQ.push(message);
      }
    }
  }
}

void Server::sendToNodes() {
  static int currentNodeIndex = 0;
  while(true) {
    std::shared_ptr<std::string> message = adminNodeQ.pop();
    auto messageInfo = analyzeJson(*message);
    std::string processId = messageInfo.first;
    if(processNodeMap.find(processId) != processNodeMap.end()) {
      // The process already exists in the system, so we need to send the message to the correct Node
      nodeManagers[processNodeMap[processId]].sendMessage(*message);
      // If the command says to delete the process, we need to remove it from our map, too. The second element of the pair that
      // analyzeJson returned tells us about it.
      if(messageInfo.second) {
        processNodeMap.erase(processId);
      }
    }
    else {
      // It's a new process - it doesn't matter where we send it. However, we need to remember it.
      nodeManagers[currentNodeIndex].sendMessage(*message);
      processNodeMap[processId] = currentNodeIndex;
      currentNodeIndex = (currentNodeIndex + 1) % nodeManagers.size();
    }
  }
}

std::pair<std::string, bool> Server::analyzeJson(const std::string& msg) {
  Json::Reader reader;
  Json::Value root;
  reader.parse(msg, root);
  if(root["commandType"].asString() == "deleteProcess") {
    return std::make_pair(root["processDetails"]["processIdentifier"].asString(), true);
  }
  return std::make_pair(root["processDetails"]["processIdentifier"].asString(), false);
}
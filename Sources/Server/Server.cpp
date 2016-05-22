//
// Created by Rafal Rzeuski on 5/21/16.
//

#include "Server.h"
#include "../Shared/Commands/AddProcessCommand.h"

#include <memory>
#include <thread>

Server::Server() : adminSocket(nullptr), aListener(adminSocket, adminNodeQ), nSender(nodeSocket, adminNodeQ),
                   nListener(nodeSocket, nodeAdminQ), aSender(adminSocket, nodeAdminQ) {
  connectToNodes();

  // For testing purposes
  Json::FastWriter fastWriter;
  std::string processContent = "#!/bin/bash\necho \"Hello World\"\necho $(date)\n";
  AddProcessCommand command = AddProcessCommand(processContent);
  std::string output = fastWriter.write(command.generateJSON());
  adminNodeQ.push(std::shared_ptr<std::string>(new std::string(output)));
}

void Server::connectToNodes() {
  SocketAddress nodeAddress("127.0.0.1:46030");
  if(nodeSocket.connect(nodeSocket.internalDescriptor(), nodeAddress) == -1) {
    perror("Couldn't connect to Node, exiting");
    exit(-1);
  }
}

void Server::run() {
  std::thread adminListeningThread(aListener);
  std::thread nodeListeningThread(nListener);
  std::thread adminSendingThread(aSender);
  std::thread nodeSendingThread(nSender);

  adminListeningThread.join();
  nodeListeningThread.join();
  adminSendingThread.join();
  nodeSendingThread.join();
}
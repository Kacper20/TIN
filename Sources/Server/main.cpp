//
// Created by Rafał Rzeuski on 09.05.16.
//
#include "../Shared/Commands/StartProcessCommand.h"
#include "Server.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  /*
  ServerNetworkLayer networkLayer;
  if (networkLayer.connectToNode("127.0.0.1:46027") != 0) {
    return -1;
  }

  //TODO: This will go to another object. We need to have threads & in main loop that will take commands from user.
  Json::FastWriter fastWriter;
  std::string processContent = "#!/bin/bash\necho \"Hello World\"\necho $(date)\n";
  AddProcessCommand command = AddProcessCommand(processContent);
  std::string output = fastWriter.write(command.generateJSON());

  if (networkLayer.sendMessage(output) < 0) {
    std::cout << "Failed to send script" << std::endl;
    return -2;
  }
  if (networkLayer.sendMessage(output) < 0) {
    std::cout << "Failed to send script" << std::endl;
    return -2;
  }
  return 0;
  */

  // For testing purposes
//  Json::FastWriter fastWriter;
//  std::string processContent = "#!/bin/bash\necho \"Hello World\"\necho $(date)\n";
//  StartProcessCommand command = StartProcessCommand("666", processContent);
//  std::string output = fastWriter.write(command.generateJSON());
//
//  Json::Reader reader;
//  Json::Value root;
//  bool success = reader.parse(output, root);
//  string type = root["commandType"].asString();
//  string processId;
//  if(type == "startNewProcess") {
//    processId = root["processDetails"]["processIdentifier"].asString();
//  }
//  cout << "type: " << type << endl;
//  cout << "processId: " << processId << endl;

  Server s;
  s.run();

//  TCPSocket sock;
//  cout << sock.internalDescriptor() << endl;
//  TCPSocket fapsock;
//  cout << fapsock.internalDescriptor() << endl;
//  cout << "Elo" << endl;
}
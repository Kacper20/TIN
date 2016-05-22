//
// Created by Rafał Rzeuski on 09.05.16.
//
#include "../Shared/Commands/AddProcessCommand.h"
#include "ServerNetworkLayer.h"
#include "Server.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  /*TODO: Here's an idea. Based on startup parameters, we will launch the server into either the setup mode or work mode.
   * Setup mode takes Node addresses in and writes them down somewhere. Later, when launched in work mode, the server will connect
   * to those addresses. This way we can change the configuration of the system.
  */
  //TODO: a nice CheckParms() function
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
  Server s;
  s.run();
}
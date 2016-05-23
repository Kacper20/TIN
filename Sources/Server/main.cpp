//
// Created by Rafał Rzeuski on 09.05.16.
//

#include <iostream>
#include "ServerNetworkLayer.h"
#include "../Shared/Commands/StartProcessCommand.h"
using namespace std;

int main(int argc, char* argv[]) {
    //TODO: a nice CheckParms() function
    ServerNetworkLayer networkLayer;
    if(networkLayer.connectToNode("127.0.0.1:46027") != 0) {
        return -1;
    }

  //TODO: This will go to another object. We need to have threads & in main loop that will take commands from user.
  Json::FastWriter fastWriter;
  std::string processContent =  "#!/bin/bash\necho \"Hello World\"\necho $(date)\n";
  StartProcessCommand command = StartProcessCommand("Identifier", processContent);
  std::string output = fastWriter.write(command.generateJSON());

  if(networkLayer.sendMessage(output) < 0) {
    std::cout << "Failed to send script" << std::endl;
    return -2;
  }
    return 0;
}
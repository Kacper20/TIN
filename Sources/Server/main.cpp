//
// Created by Rafał Rzeuski on 09.05.16.
//

#include <iostream>
#include "ServerNetworkLayer.h"
#include "../Shared/Commands/AddProcessCommand.h"
using namespace std;

int main(int argc, char* argv[]) {
    //TODO: a nice CheckParms() function
//    if(argc < 2) {
//        cout << "You need to specify node IP address!" << endl;
//    }
    cout << "Yo, what is up, world?" << endl;
    ServerNetworkLayer networkLayer;
    // localhost for testing
    if(networkLayer.connectToNode("127.0.0.1:46027") != 0) {
        return -1;
    }

  Json::FastWriter fastWriter;
  std::string processContent =  "#!/bin/bash\necho \"Hello World\"\nToday is $(date)\n";
  AddProcessCommand command = AddProcessCommand(processContent);
  std::string output = fastWriter.write(command.generateJSON());


  if(networkLayer.sendMessage(output) < 0) {
    std::cout << "Failed to send script" << std::endl;
    return -2;
  }

  if(networkLayer.sendMessage(output) < 0) {
    std::cout << "Failed to send script" << std::endl;
    return -2;
  }
    std::cout << "Send..." << std::endl;
    return 0;
}
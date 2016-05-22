//
// Created by daria on 21.05.16.
//

#ifndef TIN_INPUTHANDLER_H
#define TIN_INPUTHANDLER_H

#include <string>

class InputHandler
{
private:
  void printHelp();
  int checkAddress(const std::string& address_with_port);
  void handleConnect(const std::string& full_command);
  void handleDisconnect();
  void sendProcess(const std::string& full_command);
  void launchProcess(const std::string& full_command);

public:
  void run();
};

#endif //TIN_INPUTHANDLER_H


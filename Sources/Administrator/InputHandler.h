//
// Created by daria on 21.05.16.
//

#ifndef TIN_INPUTHANDLER_H
#define TIN_INPUTHANDLER_H

#include <string>

class InputHandler
{

public:
    void run();
    void printHelp();
    int checkAddress(std::string address_with_port);
    void handleConnect(std::string full_command);
    void handleDisconnect();
    void sendProcess(std::string full_command);
    void launchProcess(std::string full_command);
};

#endif //TIN_INPUTHANDLER_H

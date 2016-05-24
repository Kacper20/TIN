//
// Created by daria on 21.05.16.
//

#ifndef TIN_INPUTHANDLER_H
#define TIN_INPUTHANDLER_H

#include <string>
//#include <unordered_set>
#include "AdministratorNetworkLayer.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>

class InputHandler
{
private:
    AdminNetworkLayer admin;
    //std::unordered_set<std::pair<std::string, boost::uuids::uuid>> process_uuids;
    void printHelp();
    int checkAddress(const std::string& address_with_port);
    void handleConnect(const std::string& full_command);
    void handleDisconnect();
    void sendProcess(const std::string& full_command);
    void launchProcess(const std::string& full_command);

public:
    InputHandler(AdminNetworkLayer admin): admin(admin){};// { process_uuids = std::unordered_set();}
    void run();
};

#endif //TIN_INPUTHANDLER_H


//
// Created by daria on 21.05.16.
//

#ifndef TIN_INPUTHANDLER_H
#define TIN_INPUTHANDLER_H

#include <string>
#include "AdministratorNetworkLayer.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <map>

class InputHandler
{
private:
    AdminNetworkLayer admin;
    boost::uuids::uuid dns_namespace_uuid;
    std::map<std::string, boost::uuids::uuid> process_uuids;
    void printHelp();
    int checkAddress(const std::string& address_with_port);
    void handleConnect(const std::string& full_command);
    void handleDisconnect();
    void sendProcess(const std::string& full_command);
    void sendScheluedProcess(const std::string& full_command);
    void launchProcess(const std::string& full_command);
    void deleteProcess(const std::string& full_command);
    void showUploaded();
    int writeUuidsToFile(std::map<std::string, boost::uuids::uuid> process_uuids);

public:
    InputHandler(AdminNetworkLayer admin);
    void run();
};

#endif //TIN_INPUTHANDLER_H


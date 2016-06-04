//
// Created by daria on 21.05.16.
// modified by dawid
//

#ifndef TIN_INPUTHANDLER_H
#define TIN_INPUTHANDLER_H

#include <string>
#include "AdministratorNetworkLayer.h"
#include "../Shared/Commands/Command.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/name_generator.hpp>
#include <map>

class InputHandler
{
private:
    AdminNetworkLayer admin;
    boost::uuids::uuid dns_namespace_uuid;
    std::map<std::string, boost::uuids::uuid> process_uuids;
    std::function<void(std::shared_ptr<Command>)> receivedMessageFunc;

    void printHelp();
    void handleConnect(const std::string& full_command);
    void handleDisconnect();
    void sendProcess(const std::string& full_command);
    void sendScheduledProcess(const std::string &full_command);
    void launchProcess(const std::string& full_command);
    void deleteProcess(const std::string& full_command);
    void requestData(const std::string& full_command);
    void showUploaded();

    int isDate(const std::string& date);
    int isNumber(const char& c);
    int checkAddress(const std::string& address_with_port);
    bool isFile(std::string path);
    int writeUuidsToFile(std::map<std::string, boost::uuids::uuid> process_uuids);

public:
    InputHandler(AdminNetworkLayer admin);
    void run();
};

#endif //TIN_INPUTHANDLER_H


//
// Created by daria on 21.05.16.
//

#include <iostream>
#include <memory>
#include "AdministratorNetworkLayer.h"
#include "../Shared/Commands/Command.h"
#include "../Shared/Commands/StartProcessCommand.h"
#include "../Node/CommandsDeserializer.h"

using namespace std;

int AdminNetworkLayer::connectToServer(const string addressWithPort) {
    SocketAddress serverAddress(addressWithPort);

    if(serverConnectionSocket.connect(serverConnectionSocket.internalDescriptor(), serverAddress) == -1) {
        perror("Failed to connect target address");

        return -1;
    }

    std::cout << "Connected to server.\n";
    return 0;
}

int AdminNetworkLayer::sendMessage(const std::string message) const {
    std::cout << "Sending message: " <<  message << std::endl;

    if (networkManager.sendMessage(message) != -1 )
    {
        std::cout << "Message sent properly.\n";
        return 0;
    }
    else
    {
        std::cout << "Failed to send message.\n";
        return -1;
    }
}

int AdminNetworkLayer::disconnectFromServer() {
    if (shutdown(serverConnectionSocket.internalDescriptor(), 2) == 0)
        std::cout << "Disconnected properly.\n";
    else
        std::cout << "Failed to disconnect properly.\n";
    return 0;
}

void AdminNetworkLayer::receiveMessage() {
    MessageNetworkManager manager = MessageNetworkManager(serverConnectionSocket);
    std::string buffer;

    ssize_t receivedBytes = manager.receiveMessage(buffer);
    if (receivedBytes < 0) {
        return;
    }
    if (receivedBytes != 0) {
        showMessage(buffer);
    }
}

void AdminNetworkLayer::showMessage(std::string newMessage)
{
    std::cout << "New message received" << newMessage << std::endl;
    std::shared_ptr<Command> command = AdminNetworkLayer::parseToCommand(newMessage);

    Json::Value json = command.get()->generateJSON();
    Json::FastWriter fastWriter;
    std::string output = fastWriter.write(json);
    std::cout << "JSON" << output << std::endl;
}

std::shared_ptr<Command> AdminNetworkLayer::parseToCommand(std::string json) {

    Json::Reader reader;
    Json::Value root;
    bool parsingSucceeded = reader.parse(json.c_str(), root);

    if (!parsingSucceeded) {
        std::cout << "Could not parse json.\n";
        return nullptr;
    }

    const std::string type = root[JSONConstants::CommandType].asString();
    if (type == descriptionForCommandType(CommandType::START_NEW_PROCESS)) {
        std::shared_ptr<Command> deserializedCommand(new StartProcessCommand(root));
        return deserializedCommand;
    }
    return nullptr;
}
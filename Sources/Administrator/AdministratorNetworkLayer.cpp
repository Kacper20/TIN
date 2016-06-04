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

    cout << "Connected to server.\n";
    connected = true;
    return 0;
}

int AdminNetworkLayer::sendMessage(const string message) const {
    cout << "Sending message: " <<  message << endl;

    if (networkManager.sendMessage(message) != -1 )
    {
        cout << "Message sent properly.\n";
        return 0;
    }
    else
    {
        cout << "Failed to send message.\n";
        return -1;
    }
}

int AdminNetworkLayer::disconnectFromServer() {
    if (shutdown(serverConnectionSocket.internalDescriptor(), 2) == 0)
    {
        serverConnectionSocket.close();
        connected = false;
        cout << "Disconnected properly.\n";
    }
    else
        cout << "Failed to disconnect properly.\n";
    return 0;
}

void AdminNetworkLayer::receiveMessage()
{
    cout << "Jestem w odbieraniu wiadomosci\n";
    string buffer;
    while (true) {
        if(!connected)
        {
            continue;
        }
        else {
            ssize_t messageSize = networkManager.receiveMessage(buffer);
            if (messageSize > 0) {
                cout << "Received message from Server!\n";
                cout << buffer << endl;
            }
            else if (messageSize == 0) {
                cout << "Server disconnected... Close the socket\n";
                connected = false;
                serverConnectionSocket.close();
            }
        }
    }
}

void AdminNetworkLayer::showMessage(std::string newMessage)
{
    cout << "New message received" << newMessage << endl;
    shared_ptr<Command> command = AdminNetworkLayer::parseToCommand(newMessage);

    Json::Value json = command.get()->generateJSON();
    Json::FastWriter fastWriter;
    string output = fastWriter.write(json);
    cout << "JSON" << output << endl;
}

std::shared_ptr<Command> AdminNetworkLayer::parseToCommand(string json) {

    Json::Reader reader;
    Json::Value root;
    bool parsingSucceeded = reader.parse(json.c_str(), root);

    if (!parsingSucceeded) {
        cout << "Could not parse json.\n";
        return nullptr;
    }

    const string type = root[JSONConstants::CommandType].asString();
    if (type == descriptionForCommandType(CommandType::START_NEW_PROCESS)) {
        shared_ptr<Command> deserializedCommand(new StartProcessCommand(root));
        return deserializedCommand;
    }
    return nullptr;
}
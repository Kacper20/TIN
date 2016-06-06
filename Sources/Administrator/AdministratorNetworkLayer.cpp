//
// Created by daria on 21.05.16.
// Modified by Dawid
//

#include <iostream>
#include <memory>
#include <boost/uuid/name_generator.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
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
                int find = buffer.find("\"responseType\"");
                find += 16;
                int dl = buffer.find_first_of("\"", find);
                dl -= find;
                string response = buffer.substr(find, dl);
                cout << response << "\n";
                if(response == "startNewProcess"){
                    cout << "Started new process.\n";
                }
                else if(response == "scheduledProcessEnded"){
                    cout << "Scheduled process ended.\n";
                }
                else if(response == "processDelete"){
                    cout << "Delete process.\n";
                }
                else if(response == "processLaunch"){
                    cout << "Launched prcess.\n";
                }
                find = buffer.find("processIden");
                if(find != std::string::npos) {
                    find += 20;
                    dl = buffer.find_first_of("\"");
                    dl -= find;
                    string pName = buffer.substr(find, dl);
                    boost::uuids::string_generator gen;
                    boost::uuids::uuid a = gen(pName);
                    cout << "Process name: " << a << "\n";
                }

                find = buffer.find("errorMessage");
                if(find != string::npos){
                    find += 15;
                    dl = buffer.find_first_of("\"", find);
                    dl -= find;
                    cout<< "Error message: " << buffer.substr(find, dl) << "\n";
                }

                find = buffer.find("standardError");
                if(find != string::npos) {

                    cout << "Standard error: ";
                    find += 16;
                    dl = buffer.find_first_of("\"", find);
                    dl -= find;
                    if (dl > 1) {
                        cout << buffer.substr(find, dl) << "\n";
                    }
                    else {
                        cout << "none\n";
                    }
                }
                find = buffer.find("standardOut");
                if(find != string::npos) {
                    find += 17;
                    dl = buffer.find_first_of("\"", find);
                    dl -= find;
                    cout << "Standard output: " << buffer.substr(find, dl) << "\n";
                }
                find = buffer.find("date");
                if(find != string::npos){
                    find += 7;
                    dl = buffer.find_first_of("\"");
                    dl -= find;
                    cout << "Date: " << buffer.substr(find, dl) << "\n";
                }
                find = buffer.find("timestamp");
                if(find != string::npos){
                    find += 12;
                    dl = buffer.find_first_of("\"");
                    dl -= find;
                    cout << "Timestamp: " << buffer.substr(find, dl) << "\n";
                }

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
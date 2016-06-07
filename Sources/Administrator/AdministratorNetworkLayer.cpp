//
// Created by daria on 21.05.16.
// Modified by Dawid
//

#include <iostream>
#include <memory>
#include "AdministratorNetworkLayer.h"
#include <boost/uuid/name_generator.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include "../Shared/Commands/Command.h"
#include "../Shared/Commands/StartProcessCommand.h"
#include "../Node/CommandsDeserializer.h"
#include "../Shared/Responses/Response.h"
#include "ResponseDeserializer.h"
#include "../Shared/Responses/StartProcessResponse.h"
#include "../Shared/Responses/ScheduledProcessEndedResponse.h"
#include "../Shared/Responses/LaunchProcessResponse.h"
#include "../Shared/Responses/ProcessStatisticsResponse.h"
#include "../Shared/Responses/FailedResponse.h"
#include "../Shared/Responses/DeleteProcessResponse.h"

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
    string buffer;
    while (true) {
        if(!connected)
        {
            continue;
        }
        else {
            ssize_t messageSize = networkManager.receiveMessage(buffer);
            if (messageSize > 0) {
                std::shared_ptr<Response> response = ResponseDeserializer::parseToResponse(buffer);
                if(response->responseStatus == ResponseStatus::FAIL){
                    std::shared_ptr<FailedResponse> processStatus = std::static_pointer_cast<FailedResponse>(response);
                    if(processStatus != nullptr){
                        cout << "\n\nError! " << processStatus->errorMessage << "\n\n\n";
                    }
                }
                if(response->responseType == ResponseType::START_NEW_PROCESS){
                    std::shared_ptr<StartProcessResponse> processResponse = std::static_pointer_cast<StartProcessResponse>(response);
                    if(processResponse != nullptr){
                        cout << "\n\nStarting new process response.\nProcess UUID: " << processResponse->processId <<"\n";
                        cout << "Standard error: " << processResponse->standardError << "\n";
                        cout << "Standard output: " << processResponse->standardOutput << "\n\n\n";
                    }
                }
                if(response->responseType == ResponseType::DELETE_PROCESS) {
                    std::shared_ptr<DeleteProcessResponse> deleteResponse = std::static_pointer_cast<DeleteProcessResponse>(response);
                    if(deleteResponse != nullptr){
                        cout << "\n\nDeleting process response.\n";
                        cout << "Process UUID: " << deleteResponse->processId << "\n";
                    }
                }
                if(response->responseType == ResponseType::SCHEDULED_PROCESS_ENDED) {
                    std::shared_ptr<ScheduledProcessEndedResponse> scheduleResponse = std::static_pointer_cast<ScheduledProcessEndedResponse>(response);
                    if (scheduleResponse != nullptr) {
                        cout << "\n\nScheduled process ended.\n";
                        cout << "Process UUID: " << scheduleResponse->processId << "\n";
                        cout << "Timestamps: " << scheduleResponse->timestamp << "\n";
                    }
                }
                if(response->responseType == ResponseType::LAUNCH_PROCESS) {
                    std::shared_ptr<LaunchProcessResponse> launchResponse = std::static_pointer_cast<LaunchProcessResponse>(
                            response);
                    if (launchResponse != nullptr) {
                        cout << "\n\nLaunching process response.\nProcess UUID: " << launchResponse->processId << "\n";
                        cout << "Standard error: " << launchResponse->standardError << "\n";
                        cout << "Standard output: " << launchResponse->standardOutput << "\n\n\n";
                    }
                }
                if(response->responseType == ResponseType::GET_STATISTICS_ABOUT_PROCESS){
                    std::shared_ptr<ProcessStatisticsResponse> statResponse = std::static_pointer_cast<ProcessStatisticsResponse>(
                            response);
                    if(statResponse != nullptr){
                        cout << "\n\nStatistics response.\nProcess UUID: " << statResponse->processId <<"\n";
                        cout << "Process system run: " << statResponse->secondsSystemRun << "s " << statResponse->millisecondsSystemRun << "ms\n";
                        cout << "User run time: " << statResponse->secondsUserRun << "s " << statResponse->millisecondsUserRun << "ms\n\n\n";
                    }
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

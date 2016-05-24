//
// Created by Kacper Harasim on 15.05.2016.
//

#include "NodeServer.h"
#include "NodeNetworkLayer.h"
#include "../Shared/Commands/Command.h"
#include "CommandsDeserializer.h"

void NodeServer::startReceiving() {
  layer.listenOnServerConnection();
  layer.startReceivingMessages([this](std::string newMessage){
    std::cout << "New message received" << newMessage << std::endl;
    std::shared_ptr<Command> command = CommandsDeserializer::parseToCommand(newMessage);

    //Logging
    Json::Value json = command.get()->generateJSON();
    Json::FastWriter fastWriter;
    std::string output = fastWriter.write(json);
    std::cout << "JSON" << output << std::endl;
    this->receivedMessageFunc(command);
  });

  std::cout << "Ending work" << std::endl;
}


void NodeServer::startMonitorForSendings() {
  while(1) {
    std::shared_ptr<Response> responseToSend = messagesToSendQueue.pop();
    Json::FastWriter fastWriter;
    std::string message = fastWriter.write(responseToSend->generateJSON());
    std::cout << message << std::endl;
    layer.sendMessage(message);
  }
}
void NodeServer::sendResponse(std::shared_ptr<Response> response) {
  messagesToSendQueue.push(response);
}
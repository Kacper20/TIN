//
// Created by daria on 21.05.16.
//

#ifndef TIN_ADMINISTRATORNETWORKLAYER_H
#define TIN_ADMINISTRATORNETWORKLAYER_H


#include <functional>
#include "../Shared/TCPSocket.h"
#include "../Shared/MessageNetworkManager.h"
#include "../Shared/Commands/Command.h"
#include <memory>

class AdminNetworkLayer
{
private:
    TCPSocket serverConnectionSocket;
    MessageNetworkManager networkManager;
    bool connected;

public:
    AdminNetworkLayer() : serverConnectionSocket(TCPSocket()), networkManager(serverConnectionSocket), connected(false)
    { // Enable address reuse
        int on = 1;
        int ret = setsockopt( serverConnectionSocket.internalDescriptor(), SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );
    }
    int connectToServer(const std::string addressWithPort);
    int sendMessage(const std::string message) const;
    int disconnectFromServer();
    void receiveMessage();
    std::shared_ptr<Command> parseToCommand(std::string json);
    void showMessage(std::string newMessage);
};


#endif //TIN_ADMINISTRATORNETWORKLAYER_H

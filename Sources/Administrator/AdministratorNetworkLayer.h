//
// Created by daria on 21.05.16.
//

#ifndef TIN_ADMINISTRATORNETWORKLAYER_H
#define TIN_ADMINISTRATORNETWORKLAYER_H


#include <functional>
#include "../Shared/TCPSocket.h"
#include "../Shared/MessageNetworkManager.h"

#define NETWORK_ADMIN_PORT 46028


class AdminNetworkLayer
{
private:
    TCPSocket serverConnectionSocket;
    MessageNetworkManager networkManager;

public:
    AdminNetworkLayer() : serverConnectionSocket(TCPSocket()), networkManager(serverConnectionSocket) {}
    int connectToServer(const std::string addressWithPort);
    int sendMessage(const std::string message) const;
    int disconnectFromServer();
};


#endif //TIN_ADMINISTRATORNETWORKLAYER_H

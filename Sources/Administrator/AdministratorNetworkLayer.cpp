//
// Created by daria on 21.05.16.
//

#include <iostream>
#include "AdministratorNetworkLayer.h"

using namespace std;

int AdminNetworkLayer::connectToServer(const string addressWithPort) {
    SocketAddress serverAddress(addressWithPort);

    if(serverConnectionSocket.connect(serverConnectionSocket.internalDescriptor(), serverAddress) == -1) {
        perror("Failed to connect target address");

        return -1;
    }

    return 0;
}

int AdminNetworkLayer::sendMessage(const std::string message) const {
    std::cout << "Sending message: " <<  message << std::endl;

    return networkManager.sendMessage(message);
}

int AdminNetworkLayer::launchProcess(const std::string processName) const {
    std::cout << "Launching process " << processName << std::endl;

}

int AdminNetworkLayer::disconnectFromServer() {
    serverConnectionSocket.close();
    return 0;
}
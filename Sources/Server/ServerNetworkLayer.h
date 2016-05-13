//
// Created by Rafał Rzeuski on 09.05.16.
//

#ifndef TIN_SERVERNETWORKLAYER_H
#define TIN_SERVERNETWORKLAYER_H

#include "../Shared/TCPSocket.h"

class ServerNetworkLayer {
    TCPSocket* nodeConnectionSocket;

public:
    ServerNetworkLayer() : nodeConnectionSocket(nullptr) {}
    int connectToNode(const std::string addressWithPort);
    int sendScript(const std::string filename) const;
};

#endif //TIN_SERVERNETWORKLAYER_H

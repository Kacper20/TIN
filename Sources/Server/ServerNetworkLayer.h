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
    int connectToNode();
    //int readScript(std::string filename);
};

#endif //TIN_SERVERNETWORKLAYER_H

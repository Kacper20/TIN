//
// Created by Kacper Harasim on 08.05.2016.
//


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "../Shared/TCPSocket.h"

#ifndef TIN_NODENETWORKLAYER_H
#define TIN_NODENETWORKLAYER_H

#define NETWORK_PORT 3490


class NodeNetworkLayer {


 private:

 public:
  void startListeningOnRequests();




};


#endif //TIN_NODENETWORKLAYER_H

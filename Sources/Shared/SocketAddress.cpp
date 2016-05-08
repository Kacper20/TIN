//
// Created by Kacper Harasim on 08.05.2016.
//

#include <arpa/inet.h>
#include "SocketAddress.h"

SocketAddress::SocketAddress(int address, int portNumber) {
  this->address.sin_family = AF_INET;
  this->address.sin_port = htons(portNumber);
  this->address.sin_addr.s_addr = htonl(address);
}

SocketAddress::SocketAddress(std::string addressWithPort) {


}

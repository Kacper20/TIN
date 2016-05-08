//
// Created by Kacper Harasim on 08.05.2016.
//

#include <arpa/inet.h>
#include <cstdlib>
#include "SocketAddress.h"

SocketAddress::SocketAddress(int address, short portNumber) {
  configure();
  this->address.sin_port = htons(portNumber);
  this->address.sin_addr.s_addr = htonl(address);
}

SocketAddress::SocketAddress() {
  this->address.sin_port = 0;
  this->address.sin_addr.s_addr = INADDR_ANY;
}

void SocketAddress::configure() {
  this->address.sin_family = AF_INET;
  memset(&this->address.sin_zero, 0, 8);
}

SocketAddress::SocketAddress(std::string addressWithPort) {
  configure();
  auto positionOfSeparator = addressWithPort.find_first_of(":");
  auto addressSubstring = addressWithPort.substr(0, positionOfSeparator);
  auto portSubstring = addressWithPort.substr(positionOfSeparator + 1, addressWithPort.size());
  short port = atoi(portSubstring.c_str());
  this->address.sin_port = htons(port);
  inet_aton(addressWithPort.c_str(), &this->address.sin_addr);
}

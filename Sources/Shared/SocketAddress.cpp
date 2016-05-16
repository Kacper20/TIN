//
// Created by Kacper Harasim on 08.05.2016.
//

#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include "SocketAddress.h"

SocketAddress::SocketAddress(short portNumber) {
  configure();
  this->address.sin_port = htons(portNumber);
  this->address.sin_addr.s_addr = INADDR_ANY;
}

SocketAddress::SocketAddress(int address, short portNumber) {
  configure();
  this->address.sin_port = htons(portNumber);
  this->address.sin_addr.s_addr = htonl(address);
}

SocketAddress::SocketAddress() {
  configure();
  address.sin_port = 0;
  address.sin_addr.s_addr = INADDR_ANY;
}

void SocketAddress::configure() {
  address.sin_family = AF_INET;
  memset(&address.sin_zero, 0, 8);
}

SocketAddress::SocketAddress(std::string addressWithPort) {
  configure();
  auto positionOfSeparator = addressWithPort.find_first_of(":");
  auto addressSubstring = addressWithPort.substr(0, positionOfSeparator);
  auto portSubstring = addressWithPort.substr(positionOfSeparator + 1, addressWithPort.size());
  short port = atoi(portSubstring.c_str());
  address.sin_port = htons(port);
  inet_aton(addressSubstring.c_str(), &address.sin_addr);
}

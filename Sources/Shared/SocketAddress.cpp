//
// Created by Kacper Harasim on 08.05.2016.
// IPv6 support added by Rafal Rzeuski
//


#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <netdb.h>
#include <iostream>

#include "SocketAddress.h"

#ifdef TIN_IPV6

SocketAddress::SocketAddress(std::string addressWithPort) {
  // IPv4, a bit messy
  auto separatorPos = addressWithPort.find_first_of(":");
  auto addrStr = addressWithPort.substr(0, separatorPos);
  auto portStr = addressWithPort.substr(separatorPos + 1, addressWithPort.size());
  if(addressWithPort[0] == '[') {
    // if IPv6
    separatorPos = addressWithPort.find_first_of("]");
    addrStr = addressWithPort.substr(1, separatorPos - 1);
    portStr = addressWithPort.substr(separatorPos + 2, addressWithPort.size());
  }

  struct addrinfo hints;
  struct addrinfo *res;

  memset(&hints, 0, sizeof hints);
  hints.ai_family = AF_UNSPEC; // Don't care whether IPv4 or IPv6
  hints.ai_socktype = SOCK_STREAM;

  if(getaddrinfo(addrStr.c_str(), portStr.c_str(), &hints, &res) < 0) {
    std::cerr << "Address error!" << std::endl;
    exit(-123);
  }
  memcpy(&address, res->ai_addr, res->ai_addrlen);

  freeaddrinfo(res);
}

socklen_t SocketAddress::getLength() const {
  if(address.ss_family == AF_INET) {
    return sizeof(sockaddr_in);
  }
  else {
    return sizeof(sockaddr_in6);
  }
};

#else

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

#endif // TIN_IPV6
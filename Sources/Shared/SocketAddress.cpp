//
// Created by Kacper Harasim on 08.05.2016.
//  Modified by Daria Danilenko on 18.05.2016
//

#include <arpa/inet.h>
#include <cstdlib>
#include <cstring>
#include <netinet/in.h>
#include "SocketAddress.h"

SocketAddress::SocketAddress() {
  configure();
  address.sin_port = 0;
  address.sin_addr.s_addr = INADDR_ANY;

  address_v6.sin6_port = 0;
  address_v6.sin6_addr = IN6ADDR_ANY_INIT;
}

SocketAddress::SocketAddress(short portNumber) {
  configure();
  this->address.sin_port = htons(portNumber);
  this->address.sin_addr.s_addr = INADDR_ANY;

  this->address_v6.sin6_port = htons(portNumber);
  this->address_v6.sin6_addr = IN6ADDR_ANY_INIT;
}

SocketAddress::SocketAddress(std::string addressWithPort) {
  configure();
  auto positionOfSeparator = addressWithPort.find_first_of(":");
  auto addressSubstring = addressWithPort.substr(0, positionOfSeparator);
  auto portSubstring = addressWithPort.substr(positionOfSeparator + 1, addressWithPort.size());
  short port = atoi(portSubstring.c_str());
  address.sin_port = htons(port);
  address_v6.sin6_port = htons(port);

  if(strlen(addressSubstring.c_str()) > INET_ADDRSTRLEN )
    inet_pton(AF_INET6, addressSubstring.c_str(), &(address_v6.sin6_addr)); // IPv6
  else
    inet_aton(addressSubstring.c_str(), &address.sin_addr); // IPv4

}

SocketAddress::SocketAddress(int address, short portNumber) {
  configure();
  this->address.sin_port = htons(portNumber);
  this->address.sin_addr.s_addr = htonl(address);
  
  //this->address_v6.sin6_port = htons(portNumber);
  //******this->address_v6.sin6_addr = htonl(address); //how to map the address to the union?
}

void SocketAddress::configure() {
  address.sin_family = AF_INET;
  memset(&address.sin_zero, 0, 8);

  address_v6.sin6_family = AF_INET6;
}

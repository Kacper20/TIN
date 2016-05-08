//
// Created by Kacper Harasim on 08.05.2016.
//

#ifndef TIN_SOCKETADDRESS_H
#define TIN_SOCKETADDRESS_H

#include <netinet/in.h>
#include <string>
//Class that represents Socket Address - it's actually C++ wrapper over C UNIX API.
//It's a value type so it doesn't allow any mutation.
struct SocketAddress {

 private:
  void configure();

 public:
  sockaddr_in address;
  SocketAddress();
  SocketAddress(int address, short portNumber);
  SocketAddress(std::string addressWithPort);
};


#endif //TIN_SOCKETADDRESS_H

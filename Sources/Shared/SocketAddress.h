//
// Created by Kacper Harasim on 08.05.2016.
//

#ifndef TIN_SOCKETADDRESS_H
#define TIN_SOCKETADDRESS_H

#include <netinet/in.h>
#include <string>

#define TIN_IPV6

//Class that represents Socket Address - it's actually C++ wrapper over C UNIX API.
//It's a value type so it doesn't allow any mutation.

#ifdef TIN_IPV6

struct SocketAddress {
 public:
  SocketAddress() {};
  SocketAddress(std::string addressWithPort);
  sockaddr_storage address;
  socklen_t getLength() const;
};

#else

struct SocketAddress {

 private:
  void configure();

 public:
  sockaddr_in address;
  SocketAddress();
  SocketAddress(short portNumber);
  SocketAddress(int address, short portNumber);
  SocketAddress(std::string addressWithPort);
};

#endif // TIN_IPV6

#endif // TIN_SOCKETADDRESS_H

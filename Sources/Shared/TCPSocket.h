//
// Created by Kacper Harasim on 08.05.2016.
//

#ifndef TIN_TCPSOCKET_H
#define TIN_TCPSOCKET_H
//#include <sys/_types/_timeval.h>
#include "SocketAddress.h"
#include <unistd.h>
enum ShutdownOption {
  READ, READ_WRITE, WRITE
};

class TCPSocket {

 private:
  SocketAddress* socketAddress;
  //Internal descriptor of a socket
  int socketDescriptor;

//  timeval timeoutValue;

 public:
  TCPSocket();
  TCPSocket(int socketDescriptor);
//  void setTimeout(long sec, long uSec);
  int bind(const SocketAddress & socketAddress);
  TCPSocket accept();
  int connect(int socketDescriptor, SocketAddress & socketAddress);
  int listen(int allowedConnectionNumber);
  int send(const std::string &data);
  int receive(std::string &data, int bytes);
  int shutdownSocket(ShutdownOption option);
  int internalDescriptor();
  void close();

};


#endif //TIN_TCPSOCKET_H

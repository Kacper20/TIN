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
  //Internal descriptor of a listeningSocket
  int socketDescriptor;

//  timeval timeoutValue;

 public:
  TCPSocket();
  TCPSocket(int socketDescriptor);
//  void setTimeout(long sec, long uSec);
  int bind(const SocketAddress & socketAddress);
  int accept();
  int connect(int socketDescriptor, SocketAddress & socketAddress);
  int listen(int allowedConnectionNumber);
  ssize_t send(const void *data, size_t size, int flags) const ;
  ssize_t receive(void *data, size_t size, int flags) const ;
  int shutdownSocket(ShutdownOption option);
  int internalDescriptor() const;
  void close();
};


#endif //TIN_TCPSOCKET_H

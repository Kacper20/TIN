//
// Created by Kacper Harasim on 08.05.2016.
//

#include "TCPSocket.h"

TCPSocket::TCPSocket() {
  this->socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  this->socketAddress = NULL;
}

TCPSocket::TCPSocket(int socketDescriptor) {
  this->socketDescriptor = socketDescriptor;
  this->socketAddress = NULL;
}

//void TCPSocket::setTimeout(long sec, long uSec) {
//  this->timeoutValue.tv_sec = sec;
//  this->timeoutValue.tv_usec = uSec;
//}

int TCPSocket::bind(const SocketAddress &socketAddress) {
  return ::bind(this->socketDescriptor, (sockaddr *)&socketAddress.address, sizeof(struct sockaddr));
}

int TCPSocket::listen(int allowedConnectionNumber) {
  return ::listen(this->socketDescriptor, allowedConnectionNumber);
}

TCPSocket TCPSocket::accept() {
  int newSocketDescriptor = ::accept(this->socketDescriptor, 0, 0);
  TCPSocket clientTalkingSocket = *this;
  clientTalkingSocket.socketDescriptor = newSocketDescriptor;
  return clientTalkingSocket;
}


void TCPSocket::close() {
  ::close(this->socketDescriptor);
}
int TCPSocket::shutdownSocket(ShutdownOption option) {
  int shutdownType = [option] () {
    switch (option) {
      case READ: return SHUT_RD;
      case READ_WRITE: return SHUT_RDWR;
      case WRITE: return SHUT_WR;
    }
  }();

  return shutdown(this->socketDescriptor, shutdownType);
}
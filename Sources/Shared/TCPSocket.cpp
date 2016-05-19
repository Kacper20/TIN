//
// Created by Kacper Harasim on 08.05.2016.
//

#include "TCPSocket.h"

TCPSocket::TCPSocket() {
  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  socketAddress = NULL;
}

TCPSocket::TCPSocket(int socketDescriptor) {
  this->socketDescriptor = socketDescriptor;
  socketAddress = NULL;
}

//void TCPSocket::setTimeout(long sec, long uSec) {
//  this->timeoutValue.tv_sec = sec;
//  this->timeoutValue.tv_usec = uSec;
//}

int TCPSocket::bind(const SocketAddress &socketAddress) {
  if(1==1)
    return ::bind(socketDescriptor, (sockaddr *)&socketAddress.address, sizeof(struct sockaddr));
  else
    return ::bind(socketDescriptor, (sockaddr *)&socketAddress.address_v6, sizeof(struct sockaddr));
}

int TCPSocket::listen(int allowedConnectionNumber) {
  return ::listen(socketDescriptor, allowedConnectionNumber);
}

int TCPSocket::connect(int socketDescriptor, SocketAddress & socketAddress) {
  if(1==1)
    return ::connect(socketDescriptor, (sockaddr *)&socketAddress.address, sizeof(sockaddr));
  else
    return ::connect(socketDescriptor, (sockaddr *)&socketAddress.address_v6, sizeof(sockaddr));
}

int TCPSocket::accept() {
  return ::accept(socketDescriptor, 0, 0);
}

ssize_t TCPSocket::send(const void *data, size_t size, int flags) const {
  return ::send(socketDescriptor, data, size, flags);
}

ssize_t TCPSocket::receive(void *data, size_t size, int flags) const {
  return ::recv(socketDescriptor, data, size, flags);
}

void TCPSocket::close() {
  ::close(socketDescriptor);
}

int TCPSocket::shutdownSocket(ShutdownOption option) {
  int shutdownType = [option] () {
    switch (option) {
      case READ: return SHUT_RD;
      case READ_WRITE: return SHUT_RDWR;
      case WRITE: return SHUT_WR;
    }
  }();

  return shutdown(socketDescriptor, shutdownType);
}

int TCPSocket::internalDescriptor() {
  return socketDescriptor;
}
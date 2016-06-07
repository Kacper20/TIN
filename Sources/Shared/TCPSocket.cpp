//
// Created by Kacper Harasim on 08.05.2016.
//

#include "TCPSocket.h"

#ifndef TIN_IPV6
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
  return ::bind(socketDescriptor, (sockaddr *)&socketAddress.address, sizeof(struct sockaddr));
}

int TCPSocket::listen(int allowedConnectionNumber) {
  return ::listen(socketDescriptor, allowedConnectionNumber);
}

int TCPSocket::connect(int socketDescriptor, SocketAddress & socketAddress) {
  return ::connect(socketDescriptor, (sockaddr *)&socketAddress.address, sizeof(sockaddr));
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

int TCPSocket::internalDescriptor() const {
  return socketDescriptor;
}

#else

TCPSocket::TCPSocket() : socketAddress(nullptr) {
  //socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  socketDescriptor = socket(PF_UNSPEC, SOCK_STREAM, 0);
}

TCPSocket::TCPSocket(int sd) : socketDescriptor(sd), socketAddress(nullptr) {}

int TCPSocket::bind(const SocketAddress &socketAddress) {
  if(socketAddress.address.ss_family == AF_INET) {
    socketDescriptor = socket(PF_INET, SOCK_STREAM, 0);
  }
  else if(socketAddress.address.ss_family == AF_INET6) {
    socketDescriptor = socket(PF_INET6, SOCK_STREAM, 0);
  }
  return ::bind(socketDescriptor, (sockaddr *)&socketAddress.address, socketAddress.getLength());
}

int TCPSocket::listen(int allowedConnectionNumber) {
  return ::listen(socketDescriptor, allowedConnectionNumber);
}

int TCPSocket::connect(int socketDescriptor, SocketAddress & socketAddress) {
  if(socketAddress.address.ss_family == AF_INET) {
    socketDescriptor = socket(PF_INET, SOCK_STREAM, 0);
  }
  else if(socketAddress.address.ss_family = AF_INET6) {
    socketDescriptor = socket(PF_INET6, SOCK_STREAM, 0);
  }
  return ::connect(socketDescriptor, (sockaddr *)&socketAddress.address, socketAddress.getLength());
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

int TCPSocket::internalDescriptor() const {
  return socketDescriptor;
}

#endif // TIN_IPV6
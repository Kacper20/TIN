//
// Created by Kacper Harasim on 08.05.2016.
//

#include "TCPSocket.h"

TCPSocket::TCPSocket() {
  socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
  socketAddress = NULL;
}

TCPSocket::TCPSocket(int socketDescriptor) {
  socketDescriptor = socketDescriptor;
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

TCPSocket TCPSocket::accept() {
  int newSocketDescriptor = ::accept(socketDescriptor, 0, 0);
  TCPSocket clientTalkingSocket = *this;
  clientTalkingSocket.socketDescriptor = newSocketDescriptor;
  return clientTalkingSocket;
}

int TCPSocket::send(const std::string &data) {
  return ::send(socketDescriptor, data.c_str(), data.size(), 0);
}

int TCPSocket::receive(std::string &data, int bytes) {
  char buffer[bytes];
  //TODO: Fill out the implementation

  return 0;
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
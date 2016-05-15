//
// Created by Kacper Harasim on 13.05.2016.
//

#ifndef TIN_MESSAGECOMPOSER_H
#define TIN_MESSAGECOMPOSER_H


#include "TCPSocket.h"
class MessageNetworkManager {

 private:
  TCPSocket socket;
 public:
  MessageNetworkManager(TCPSocket socket): socket(socket) {}
  MessageNetworkManager();
  ssize_t sendMessage(const std::string content) const;
  ssize_t receiveMessage(std::string &buffer) const;
};


#endif //TIN_MESSAGECOMPOSER_H
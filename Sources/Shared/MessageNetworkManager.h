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
  MessageNetworkManager() {};
  MessageNetworkManager(TCPSocket socket): socket(socket) {}
  ssize_t sendMessage(const std::string content) const;
  ssize_t receiveMessage(std::string &buffer, bool = false) const;
};


#endif //TIN_MESSAGECOMPOSER_H

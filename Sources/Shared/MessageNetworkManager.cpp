//
// Created by Kacper Harasim on 13.05.2016.
//

#include <vector>
#include "MessageNetworkManager.h"

ssize_t MessageNetworkManager::sendMessage(std::string content) const {
  uint32_t dataLength = htonl(content.size());

  if (socket.send(&dataLength, sizeof(uint32_t), 0) == -1) {
    perror("Error while sending number of bytes occured");
    return -1;
  }

  int numberOfBytes = socket.send(content.data(), content.size(), 0);
  if (numberOfBytes == -1) {
    perror("Error while sending message occured");
    return -1;
  }
  return numberOfBytes;
}

ssize_t MessageNetworkManager::receiveMessage(std::string &buffer) const {
  uint32_t dataLength;
  ssize_t numberOfBytesInHeader = socket.receive(&dataLength, sizeof(uint32_t), 0);
  if (numberOfBytesInHeader == -1) {
    perror("Error while receiving message length from listeningSocket");
    return -1;
  }
  dataLength = ntohl(dataLength);

  std::vector<char> receiveBuffer(dataLength, 0);
  ssize_t numberOfContentBytes = socket.receive(&receiveBuffer[0], dataLength, 0);
  if (numberOfContentBytes == -1) {
    perror("Error while receiving message content from listeningSocket");
    return -1;
  }
  buffer.assign(&(receiveBuffer[0]),receiveBuffer.size());
  return numberOfBytesInHeader + numberOfContentBytes;
}
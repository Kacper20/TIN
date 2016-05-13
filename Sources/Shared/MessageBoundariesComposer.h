//
// Created by Kacper Harasim on 11.05.2016.
//

#ifndef TIN_MESSAGESOCKETCOMPOSER_H
#define TIN_MESSAGESOCKETCOMPOSER_H


#include <string>
class MessageBoundariesComposer {
 public:
  std::string createMessageWithBoundariesFromMessage(std::string message);

};


#endif //TIN_MESSAGESOCKETCOMPOSER_H

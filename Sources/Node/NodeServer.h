//
// Created by Kacper Harasim on 15.05.2016.
//

#ifndef TIN_NODESERVER_H
#define TIN_NODESERVER_H
#include "../Shared/Commands/Command.h"
#include <functional>
#include <memory>

class NodeServer {

 private:
  std::function<void(std::shared_ptr<Command>)> receivedMessageFunc;
 public:
  NodeServer(std::function<void(std::shared_ptr<Command>)> completionFunc) : receivedMessageFunc(completionFunc) {}
  void startReceiving();
};


#endif //TIN_NODESERVER_H

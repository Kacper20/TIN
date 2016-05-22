//
// Created by Rafal Rzeuski on 5/21/16.
//

#ifndef TIN_NODELISTENER_H
#define TIN_NODELISTENER_H

#include "../Shared/TCPSocket.h"
#include "../Shared/MessagesQueue.h"

class NodeListener {
  MessagesQueue<std::string>& q;
  TCPSocket& nodeSocket;

 public:
  NodeListener(TCPSocket& s, MessagesQueue<std::string>& qq) : nodeSocket(s), q(qq) {}
  void operator()();
};

#endif // TIN_NODELISTENER_H
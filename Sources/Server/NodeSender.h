//
// Created by Rafal Rzeuski on 5/21/16.
//

#ifndef TIN_NODESENDER_H
#define TIN_NODESENDER_H

#include "../Shared/MessagesQueue.h"
#include "../Shared/TCPSocket.h"

class NodeSender {
  MessagesQueue<std::string>& q;
  TCPSocket& nodeSocket;

 public:
  NodeSender(TCPSocket& s, MessagesQueue<std::string>& qq) : q(qq), nodeSocket(s) {}
  void operator()();
};

#endif // TIN_NODESENDER_H
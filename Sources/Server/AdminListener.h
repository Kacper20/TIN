//
// Created by Rafal Rzeuski on 5/21/16.
//

#ifndef TIN_ADMINLISTENER_H
#define TIN_ADMINLISTENER_H

#include "../Shared/Commands/Command.h"
#include "../Shared/MessagesQueue.h"
#include "../Shared/TCPSocket.h"

#include <memory>

class AdminListener {
  MessagesQueue<std::string>& q;
  TCPSocket*& adminSocket;

 public:
  AdminListener(TCPSocket*& ss, MessagesQueue<std::string>& qq) : q(qq), adminSocket(ss) {}
  void operator()();
  void connectToAdmin();
};

#endif // TIN_ADMINLISTENER_H
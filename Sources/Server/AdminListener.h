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

  // This is a reference to a pointer. When we call listen() and then receive a new socket descriptor,
  // we want it to point to that descriptor. Another thread uses the same TCPSocket, so we want the change to affest it as well
  TCPSocket*& adminSocket;

 public:
  AdminListener(TCPSocket*& s, MessagesQueue<std::string>& qq) : q(qq), adminSocket(s) {}
  void operator()();
  void connectToAdmin();
};

#endif // TIN_ADMINLISTENER_H
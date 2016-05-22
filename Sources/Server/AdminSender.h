//
// Created by Rafal Rzeuski on 5/21/16.
//

#ifndef TIN_ADMINSENDER_H
#define TIN_ADMINSENDER_H

#include "../Shared/MessagesQueue.h"
#include "../Shared/TCPSocket.h"

class AdminSender {
  MessagesQueue<std::string>& q;

  // For explanation why this is a reference to a pointer, refer to AdminListener.h
  TCPSocket*& adminSocket;

 public:
  AdminSender(TCPSocket*& s, MessagesQueue<std::string>& qq) : adminSocket(s), q(qq) {}
  void operator()();
};

#endif // TIN_ADMINSENDER_H
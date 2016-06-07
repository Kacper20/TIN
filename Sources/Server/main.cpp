//
// Created by Rafał Rzeuski on 09.05.16.
//
#include "../Shared/Commands/StartProcessCommand.h"
#include "Server.h"
#include "../Shared/TCPSocket.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  bool fake_admin = false;
  if(argc > 1 && argv[1] == "real_admin") {
    fake_admin = false;
  }
  cout << "fake_admin : " << fake_admin << endl;

  SocketAddress testA("127.0.0.1:40501");
  TCPSocket sock;
  if(sock.bind(testA) < 0) {
    perror("CHUJ : ");
    exit(-707);
  }

  Server s(fake_admin);
  s.run();
}
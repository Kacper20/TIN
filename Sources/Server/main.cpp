//
// Created by Rafał Rzeuski on 09.05.16.
//
#include "../Shared/Commands/StartProcessCommand.h"
#include "Server.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  bool fake_admin = true;
  if(argc > 1 && argv[1] == "real_admin") {
    fake_admin = false;
  }
  cout << "fake_admin : " << fake_admin << endl;
  Server s(fake_admin);
  s.run();
}
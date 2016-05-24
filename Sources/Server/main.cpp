//
// Created by Rafał Rzeuski on 09.05.16.
//
#include "../Shared/Commands/StartProcessCommand.h"
#include "Server.h"

#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  Server s;
  s.run();
}
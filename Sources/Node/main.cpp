#include <iostream>
#include "NodeNetworkLayer.h"
using namespace std;

int main() {

  cout << "Hello, World!" << endl;
  NodeNetworkLayer layer = NodeNetworkLayer();
  layer.startListeningOnRequests();
  return 0;
}
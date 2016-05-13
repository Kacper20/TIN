//
// Created by Rafał Rzeuski on 09.05.16.
//

#include <iostream>
#include "ServerNetworkLayer.h"
using namespace std;

int main(int argc, char* argv[]) {
    //TODO: a nice CheckParms() function
    if(argc < 2) {
        cout << "You need to specify node IP address!" << endl;
    }
    cout << "Yo, what is up, world?" << endl;
    ServerNetworkLayer networkLayer;
    // localhost for testing
    if(networkLayer.connectToNode("127.0.0.1:1666") != 0) {
        return -1;
    }
    if(networkLayer.sendScript("somescript.sh") != 0) {
        return -2;
    }
    return 0;
}
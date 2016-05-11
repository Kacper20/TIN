//
// Created by Rafał Rzeuski on 09.05.16.
//

#include <iostream>
#include "ServerNetworkLayer.h"
using namespace std;

int main(int argc, char* argv[]) {
    // CheckParms() ?
    cout << "Yo, what is up, world?" << endl;
    ServerNetworkLayer lay;
    lay.connectToNode();
}
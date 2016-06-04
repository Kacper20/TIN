//
// Created by Rafal Rzeuski on 5/16/16.
// Modified by Daria Danilenko on 20.05.2016
//

#include <thread>
#include "InputHandler.h"

struct InputHandlingTask {
    InputHandler handler;
    InputHandlingTask(InputHandler handler): handler(handler) {}
    void operator() () {
        handler.run();
    }
};

struct ReceiveMessagesTask{
    AdminNetworkLayer *layer;
    ReceiveMessagesTask(AdminNetworkLayer *layer): layer(layer) {}
    void operator() () {
        layer->receiveMessage();
    }
};


int main(int argc, char* argv[]) {
    AdminNetworkLayer *admin = new AdminNetworkLayer();
    InputHandler handler(admin);

    InputHandlingTask inputTask(handler);
    ReceiveMessagesTask receiveMessageTask(admin);
    std::thread inputThread(inputTask);
    std::thread messagesThread(receiveMessageTask);

    inputThread.join();
    messagesThread.join();
    delete(admin);
}

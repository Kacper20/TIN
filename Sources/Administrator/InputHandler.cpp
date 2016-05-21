//
// Created by daria on 21.05.16.
//

#include "InputHandler.h"
#include <iostream>
#include <cstring>

void InputHandler::run()
{
    std::cout << "Waiting for a command:\n";
    std::string command;
    std::string name;

    while ( name != "exit")
    {
        std::getline (std::cin,command);

        if ( command.find(" ") == std::string::npos )
            name = command;
        else name = command.substr(0,command.find_first_of(" "));

        if ( name == "help") {
        printHelp();
        }
        else if ( name == "connect") {
        handleConnect(command);
        }
        else if ( name == "disconnect") {
        handleDisconnect();
        }
        else if ( name == "send_process" ) {
        sendProcess(command);
        }
        else if (  name == "launch_process" ) {
        launchProcess(command);
        }
        else {
        std::cout << "Incorrect command.\n";
        printHelp();
        }
    }
    std::cout << "Exiting Administrator process. Goodbye.\n";
}


void InputHandler::printHelp()
{
    std::cout << "Available commands for administrator process:" << "\n";
    std::cout << "connect <server address:port> - Connects to server on the specified address." << "\n";
    std::cout << "send_process <name> <path to file> - Sends the file you choose to the server" << "\n";
    std::cout << "\t and saves it to the server with the name specified in 'name' argument" << "\n";
    std::cout << "launch_process <name> - Tells the server to start chosen process." << "\n"; // Needs improvement
    std::cout << "disconnect - Disconnects from the server." << "\n";
    std::cout << "help - Shows this message." << "\n";
    std::cout << "exit - Exits from the administrator process, closes connections." << "\n";
}

int InputHandler::checkAddress(std::string address_with_port)
{
    return 0;
}

void InputHandler::handleConnect(std::string full_command)
{
    if( full_command.length() <= strlen("connect"))
    {
        std::cout << "Invalid command. The correct call is: connect <server address:port>. \n";
        std::cout << "Please try again. \n";
        return;
    }

    std::string address_with_port = full_command.substr(full_command.find_first_of(" ")+1);
    int result = checkAddress(address_with_port);

    if(result == 0)
    {
        //TODO - start connection to server here
    }
    else
    {
        std::cout << "Invalid address. The correct way is for example: 111.111.111.111:20.\n";
        std::cout << "Please try again.\n";
    }
}

void InputHandler::handleDisconnect()
{

}

void InputHandler::sendProcess(std::string full_command)
{
    if( full_command.length() <= strlen("send_process"))
    {
        std::cout << "Invalid command. The correct call is: send_process <name> <path to file>. \n";
        std::cout << "Please try again. \n";
        return;
    }

    std::string process_name = full_command.substr(full_command.find_first_of(" ")+1);

    //TODO check if there is correct nr of arguments + check if file exists

    //TODO send process_name to server to save

}

void InputHandler::launchProcess(std::string full_command)
{
    if( full_command.length() <= strlen("launch_process"))
    {
        std::cout << "Invalid command. The correct call is: launch_process <name>. \n";
        std::cout << "Please try again. \n";
        return;
    }

    std::string process_name = full_command.substr(full_command.find_first_of(" ")+1);

    //TODO send process_name to server to launch
}

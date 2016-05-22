//
// Created by daria on 21.05.16.
//

#include "InputHandler.h"
#include <iostream>
#include <cstring>
using namespace std;

void InputHandler::run()
{
  cout << "Waiting for a command:\n";
  string command;
  string name;

  do
  {
    getline (cin,command);

    if ( command.find(" ") == string::npos ) {
      name = command;
    }
    else {
      name = command.substr(0,command.find_first_of(" "));
    }

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
  } while ( name != "exit");

  cout << "Exiting Administrator process. Goodbye.\n";
}


void InputHandler::printHelp()
{
  cout << "Available commands for administrator process:" << "\n";
  cout << "connect <server address:port> - Connects to server on the specified address." << "\n";
  cout << "send_process <name> <path to file> - Sends the file you choose to the server" << "\n";
  cout << "\t and saves it to the server with the name specified in 'name' argument" << "\n";
  cout << "launch_process <name> - Tells the server to start chosen process." << "\n"; // Needs improvement
  cout << "disconnect - Disconnects from the server." << "\n";
  cout << "help - Shows this message." << "\n";
  cout << "exit - Exits from the administrator process, closes connections." << "\n";
}

int InputHandler::checkAddress(const string& address_with_port)
{
  return 0;
}

void InputHandler::handleConnect(const string& full_command)
{
  if( full_command.length() <= strlen("connect")) {
    cout << "Invalid command. The correct call is: connect <server address:port>. \n";
    cout << "Please try again. \n";
    return;
  }

  string address_with_port = full_command.substr(full_command.find_first_of(" ")+1);
  int result = checkAddress(address_with_port);

  if(result == 0) {
    admin.connectToServer(address_with_port);
  }
  else
  {
    cout << "Invalid address. The correct way is for example: 111.111.111.111:20.\n";
    cout << "Please try again.\n";
  }
}

void InputHandler::handleDisconnect()
{
  admin.disconnectFromServer();
}

void InputHandler::sendProcess(const string& full_command)
{
  if( full_command.length() <= strlen("send_process")) {
    cout << "Invalid command. The correct call is: send_process <name> <path to file>. \n";
    cout << "Please try again. \n";
    return;
  }

  string process_name = full_command.substr(full_command.find_first_of(" ")+1);

  //TODO check if there is correct nr of arguments + check if file exists

  //TODO send process_name to server to save

}

void InputHandler::launchProcess(const string& full_command)
{
  if( full_command.length() <= strlen("launch_process")) {
    cout << "Invalid command. The correct call is: launch_process <name>. \n";
    cout << "Please try again. \n";
    return;
  }

  string process_name = full_command.substr(full_command.find_first_of(" ")+1);

  //TODO send process_name to server to launch
}

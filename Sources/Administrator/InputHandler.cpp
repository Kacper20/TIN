//
// Created by daria on 21.05.16.
//

#include "InputHandler.h"
#include "../Shared/Commands/StartProcessCommand.h"
#include "../Shared/Commands/LaunchProcessCommand.h"
#include <fstream>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>


using namespace std;

void InputHandler::run()
{
  cout << "Waiting for a command:\n";
  string command;
  string name;

  // get set of uuids from the file
  process_uuids = getUuidsFromFile();

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

  writeUuidsToFile(process_uuids);
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
  if( process_name.find_first_of(" ") == string::npos)
  {
      cout << "Invalid number of arguments. The correct call is: send_process <name> <path to file>. \n";
      cout << "Please try again. \n";
      return;
  }
  string process_path = process_name.substr(process_name.find_first_of(" ")+1);
  process_name = process_name.substr(0, process_name.length() - process_path.length()-1);
  fstream process_file(process_path, ios::in);
  if(!process_file.is_open())
  {
      cout << "File does not exist.  \nPlease try again. \n";
      return;
  }

  //getting unique uuid for process name for server to use - check if name is already in
  std::map<std::string,boost::uuids::uuid>::iterator it;
  it = process_uuids.find(process_name);
  boost::uuids::uuid u_to_send;

  if ( it == process_uuids.end() )
  {
    boost::uuids::name_generator gen(dns_namespace_uuid);
    boost::uuids::uuid u = gen(std::string(process_name));
    process_uuids.insert(std::pair<std::string,boost::uuids::uuid>(process_name, u));
    u_to_send = u;
  }
  else
  {
    u_to_send = it->second;
  }
  //loading process code
  string process_code;
  process_file.seekg(0, std::ios::end);
  process_code.reserve(process_file.tellg());
  process_file.seekg(0, std::ios::beg);
  process_code.assign((std::istreambuf_iterator<char>(process_file)), std::istreambuf_iterator<char>());
  process_file.close();
  StartProcessCommand command = StartProcessCommand(boost::uuids::to_string(u_to_send), process_code);
  Json::FastWriter fastWriter;
  std::string message = fastWriter.write(command.generateJSON());
  admin.sendMessage(message);

}

std::map<std::string, boost::uuids::uuid> InputHandler::getUuidsFromFile()
{
  std::map<std::string, boost::uuids::uuid> temp;
  string line, name;
  boost::uuids::uuid u;
  ifstream uuids_file ("uuids_file.txt"); //unsure where to get this file from :/

  if (uuids_file.is_open())
  {
    while ( getline(uuids_file,line) )
    {
      int index = line.find_first_of(" ");
      name = line.substr(0, index);
      string uuid_string = line.substr(index+1);
      u = boost::lexical_cast<boost::uuids::uuid>(uuid_string);
    }
    uuids_file.close();
  }
  else
    cout << "Unable to open file";

  return temp;
}

int InputHandler::writeUuidsToFile(std::map<std::string, boost::uuids::uuid> process_uuids)
{
  if (!process_uuids.empty())
  {
    std::map<std::string, boost::uuids::uuid>::iterator it;
    ofstream uuids_file ("uuids_file.txt"); //not sure where to put this file

    if (uuids_file.is_open())
    {
      for (it = process_uuids.begin(); it != process_uuids.end(); ++it)
      {
          uuids_file << it->first << " ";
          uuids_file << to_string(it->second) << "\n";
      }
      uuids_file.close();
    }
    else
    {
      cout << "Unable to open file with uuids.\n";
      return -1;
    }
  }

  return 0;
}

void InputHandler::launchProcess(const string& full_command)
{
  if( full_command.length() <= strlen("launch_process")) {
    cout << "Invalid command. The correct call is: launch_process <name>. \n";
    cout << "Please try again. \n";
    return;
  }
  string process_name = full_command.substr(full_command.find_first_of(" ")+1);

  std::map<std::string,boost::uuids::uuid>::iterator it;
  it = process_uuids.find(process_name);
  boost::uuids::uuid u_to_send;

  if ( it == process_uuids.end() )
  {
    boost::uuids::name_generator gen(dns_namespace_uuid);
    boost::uuids::uuid u = gen(std::string(process_name));
    process_uuids.insert(std::pair<std::string,boost::uuids::uuid>(process_name, u));
    u_to_send = u;
  }
  else
  {
    u_to_send = it->second;
  }

  LaunchProcessCommand command = LaunchProcessCommand(boost::uuids::to_string(u_to_send));
  Json::FastWriter fastWriter;
  std::string message = fastWriter.write(command.generateJSON());
  admin.sendMessage(message);
}

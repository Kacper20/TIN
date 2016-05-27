//
// Created by daria on 21.05.16.
//

#include "InputHandler.h"
#include "../Shared/Commands/StartProcessCommand.h"
#include "../Shared/Commands/LaunchProcessCommand.h"
#include "../Shared/Commands/DeleteProcessCommand.h"
#include "../Shared/Commands/StartProcessWithScheduleCommand.h"
#include "../Shared/Commands/RequestDataCommand.h"
#include <fstream>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>


using namespace std;

InputHandler::InputHandler(AdminNetworkLayer admin){
    this->admin = admin;
    string line, name;
    boost::uuids::uuid u;
    ifstream uuids_file ("uuids_file.txt");

    if (uuids_file.is_open())
    {
        while ( getline(uuids_file,line) )
        {
            int index = line.find_first_of(" ");
            name = line.substr(0, index);
            string uuid_string = line.substr(index+1);
            if(uuid_string[0] >= 33) {
                u = boost::lexical_cast<boost::uuids::uuid>(uuid_string);
                process_uuids.insert(std::pair<std::string, boost::uuids::uuid>(name, u));
            }
        }
        uuids_file.close();
    }
}

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
    else if ( name == "show_uploaded") {
        showUploaded();
    }
    else if ( name == "send_process" ) {
      sendProcess(command);
    }
    else if ( name == "send_schedule") {
        sendScheduledProcess(command);
    }
    else if (  name == "launch_process" ) {
      launchProcess(command);
    }
    else if ( name == "delete_process") {
      deleteProcess(command);
    }
    else if ( name == "request_data"){
        requestData(command);
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
  cout << "Available commands for administrator process:\n";
  cout << "connect <server address:port> - Connects to server on the specified address.\n";
  cout << "send_process <name> <path to file> - Sends the file you choose to the server\n";
  cout << "\t and saves it to the server with the name specified in 'name' argument\n";
  cout << "send_schedule <name> <path to file> <timestamp> [...] <timestamp> - Sends the file you choose\n";
  cout << "\t to the server and saves it to the server with name specified in 'name'\n";
  cout << "\t argument. Process is run in specified time (can be many timestamps).\n";
  cout << "\t Timestamps are seconds from 00:00.\n";
  cout << "launch_process <name> - Tells the server to start chosen process.n";
  cout << "request_data <name> <date> <timestamp> - Requesting data from server about specific process run.";
  cout << "delete_process <name> - Tells the server to delete chosen process.\n";
  cout << "show_uploaded - Shows processes uploaded to server.\n";
  cout << "disconnect - Disconnects from the server.\n";
  cout << "help - Shows this message.\n";
  cout << "exit - Exits from the administrator process, closes connections.\n";
}

int InputHandler::checkAddress(const string& address_with_port)
{
  return 0;
}

void InputHandler::handleConnect(const string& full_command)
{
  if( full_command.length() <= strlen("connect")) {
    cout << "Invalid command. The correct call is: connect <server address:port>.\n";
    cout << "Please try again.\n";
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
    cout << "Invalid command. The correct call is: send_process <name> <path to file>.\n";
    cout << "Please try again.\n";
    return;
  }

  string process_name = full_command.substr(full_command.find_first_of(" ") + 1);
  if( process_name.find_first_of(" ") == string::npos)
  {
      cout << "Invalid number of arguments. The correct call is: send_process <name> <path to file>.\n";
      cout << "Please try again.\n";
      return;
  }

  string process_path = process_name.substr(process_name.find_first_of(" ") + 1);

  //checking if file path ends with .sh
  if(process_path[process_path.length()-1] != 'h' || process_path[process_path.length()-2] != 's' || process_path[process_path.length()-3] != '.') {
      cout << "Invalid file. \nPlease try again.\n";
      return;
  }

  process_name = process_name.substr(0, process_name.length() - process_path.length()-1);
  fstream process_file(process_path, ios::in);

  if(!process_file.is_open())
  {
      cout << "File does not exist.\n";
      cout << "Please try again.\n";
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

void InputHandler::launchProcess(const string& full_command) {
  if (full_command.length() <= strlen("launch_process")) {
    cout << "Invalid command. The correct call is: launch_process <name>. \n";
    cout << "Please try again. \n";
    return;
  }
  string process_name = full_command.substr(full_command.find_first_of(" ") + 1);

  std::map<std::string, boost::uuids::uuid>::iterator it;
  it = process_uuids.find(process_name);
  boost::uuids::uuid u_to_send;

  if (it == process_uuids.end()) {
      std::cout<<"Process was not uploaded to server.\n";
      std::cout << "Please try again.\n";
      return;
  }
  else {
    u_to_send = it->second;
  }

  LaunchProcessCommand command = LaunchProcessCommand(boost::uuids::to_string(u_to_send));
  Json::FastWriter fastWriter;
  std::string message = fastWriter.write(command.generateJSON());

  admin.sendMessage(message);
}

void InputHandler::deleteProcess(const std::string& full_command) {
  if (full_command.length() <= strlen("delete_process")) {
    cout << "Invalid command. The correct call is: delete_process <name>. \n";
    cout << "Please try again. \n";
    return;
  }

  string process_name = full_command.substr(full_command.find_first_of(" ") + 1);

  std::map<std::string, boost::uuids::uuid>::iterator it;
  it = process_uuids.find(process_name);
  boost::uuids::uuid u_to_send;

  if (it == process_uuids.end()) {
    std::cout << "Process not found.\n";
    std::cout << "Please try again. \n";
  }
  else {
      std::cout<< "Deleting process. \n";
    process_uuids.erase(it);
    u_to_send = it->second;
  }

  DeleteProcessCommand command = DeleteProcessCommand(boost::uuids::to_string(u_to_send));
  Json::FastWriter fastWriter;
  std::string message = fastWriter.write(command.generateJSON());

  admin.sendMessage(message);
}

void InputHandler::showUploaded(){
    std::map<std::string, boost::uuids::uuid>::iterator it;
    std::cout << "Uploaded processes: \n";
    for(it = process_uuids.begin(); it != process_uuids.end(); ++it){
        std::cout << it->first << "\n";
    }
    std::cout << "\n";
}

void InputHandler::sendScheduledProcess(const std::string &full_command) {
    if (full_command.length() <= strlen("send_process")) {
        cout << "Invalid command. The correct call is: send_process <name> <path to file>.\n";
        cout << "Please try again.\n";
        return;
    }

    string process_name = full_command.substr(full_command.find_first_of(" ") + 1);
    if (process_name.find_first_of(" ") == string::npos) {
        cout << "Invalid number of arguments. The correct call is: send_process <name> <path to file>.\n";
        cout << "Please try again.\n";
        return;
    }

    string process_path = process_name.substr(process_name.find_first_of(" ") + 1);
    if (process_path.find_first_of(" ") == string::npos) {
        std::cout << "Invalid number of arguments. \nPlease try again.\n";
        return;
    }

    string process_timestamps = process_path.substr(process_path.find_first_of(" ") + 1);
    process_path = process_path.substr(0, process_path.length() - process_timestamps.length() - 1);
    //checking if file path ends with .sh
    if (process_path[process_path.length() - 1] != 'h' || process_path[process_path.length() - 2] != 's' ||
        process_path[process_path.length() - 3] != '.') {
        cout << "Invalid file. \nPlease try again. \n";
        return;
    }

    process_name = process_name.substr(0, process_name.length() - process_path.length() - 1);
    fstream process_file(process_path, ios::in);
    if (!process_file.is_open()) {
        cout << "File does not exist.  \n";
        cout << "Please try again. \n";
        return;
    }

    //loading process code
    string process_code;
    process_file.seekg(0, std::ios::end);
    process_code.reserve(process_file.tellg());
    process_file.seekg(0, std::ios::beg);
    process_code.assign((std::istreambuf_iterator<char>(process_file)), std::istreambuf_iterator<char>());
    process_file.close();

    //taking integers from string to vector
    vector<int> timestamps;
    int temp = 0;
    for (int i = 0; i < process_timestamps.length(); ++i) {
        if (process_timestamps[i] != ' ') {
            temp = temp * 10 + (process_timestamps[i] - '0');
        }
        else if (process_timestamps[i] == ' ') {
            timestamps.push_back(temp);
            temp = 0;
        }
        else {
            temp = 0;
        }
        if (i == process_timestamps.length() - 1 && process_timestamps[i] >= '0' && process_timestamps[i] <= '9') {
            timestamps.push_back(temp);
        }
    }
    if (timestamps.size() == 0) {
        std::cout << "Inserted invalid timestamps.\nPlease try again.\n";
        return;
    }

    //getting unique uuid for process name for server to use - check if name is already in
    std::map<std::string, boost::uuids::uuid>::iterator it;
    it = process_uuids.find(process_name);
    boost::uuids::uuid u_to_send;

    if (it == process_uuids.end()) {
        boost::uuids::name_generator gen(dns_namespace_uuid);
        boost::uuids::uuid u = gen(std::string(process_name));
        process_uuids.insert(std::pair<std::string, boost::uuids::uuid>(process_name, u));
        u_to_send = u;
    }
    else {
        u_to_send = it->second;
    }

    Schedule schedule(timestamps);

    StartProcessWithScheduleCommand command = StartProcessWithScheduleCommand(boost::uuids::to_string(u_to_send),
                                                                              process_code, schedule);
    Json::FastWriter fastWriter;
    std::string message = fastWriter.write(command.generateJSON());

    admin.sendMessage(message);
}

void InputHandler::requestData(const std::string &full_command){
    if( full_command.length() <= strlen("send_process")) {
        cout << "Invalid command. The correct call is: request_data <name> <path to file>. \n";
        cout << "Please try again. \n";
        return;
    }

    string process_name = full_command.substr(full_command.find_first_of(" ")+1);
    if( process_name.find_first_of(" ") == string::npos)
    {
        cout << "Invalid number of arguments. The correct call is: request_data <name> <date> <timestamp> . \n";
        cout << "Please try again. \n";
        return;
    }

    string date = process_name.substr(process_name.find_first_of(" ")+1);
    if( date.find_first_of(" ") == string::npos){
        cout << "Invalid number of arguments. The correct call is: request_data <name>  <date> <timestamp> . \n";
        cout << "Please try again. \n";
        return;
    }

    process_name = process_name.substr(0, process_name.length() - date.length()-1);
    string timestamp = date.substr(date.find_first_of(" ")+1);
    date = date.substr(0, date.length() - timestamp.length()-1);
    if(!isDate(date)){
        cout << "Invalid date - correct format is DD-MM-YYYY\n";
        cout << "Please try again.\n";
        return;
    }

    for(int i = 0; i < timestamp.length(); ++i){
        if(!isNumber(timestamp[i])) {
            cout << "Invalid timestamp.\n";
            cout << "Please try again.\n";
            return;
        }
    }

    boost::uuids::uuid u_to_send;
    boost::uuids::name_generator gen(dns_namespace_uuid);
    boost::uuids::uuid u = gen(std::string(process_name));
    process_uuids.insert(std::pair<std::string,boost::uuids::uuid>(process_name, u));
    u_to_send = u;

    RequestDataCommand command = RequestDataCommand(boost::uuids::to_string(u_to_send), date, timestamp);
    Json::FastWriter fastWriter;
    std::string message = fastWriter.write(command.generateJSON());

    admin.sendMessage(message);
    admin.receiveMessage();
}

int InputHandler::isDate(const std::string &date){
    for(int i = 0 ; i < 10; ++i){
        if(i == 2 || i == 5)
            ++i;

        if(!isNumber(date[i]))
            return 0;
    }

    if(date[2] != '-' || date[5]!='-')
        return 0;

    int temp = 10 * (date[0] - '0') + date[1] - '0';
    if(temp > 31)
        return 0;

    temp = 10 * (date[3] - '0') + date[4] - '0';
    if(temp > 12)
        return 0;

    return 1;
}

int InputHandler::isNumber(const char &c){
    if(c>='0' && c <='9')
        return 1;
    return 0;
}
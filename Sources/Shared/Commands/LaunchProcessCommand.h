//
// Created by dawid on 24.05.16.
//

#ifndef TIN_LAUNCHPROCESSCOMMAND_H
#define TIN_LAUNCHPROCESSCOMMAND_H
#include "Command.h"


//Command that is send, when user wants to run process in a one time way and immediately see the result.
//Response that is sent to the user is of class StartProcessResponse
class LaunchProcessCommand: public Command {
private:

public:
    std::string processId;
    LaunchProcessCommand (Json::Value json);
    LaunchProcessCommand (std::string processId): Command(CommandType::LAUNCH_PROCESS),
                                                                             processId(processId){};
    Json::Value generateJSON();
};


#endif //TIN_LAUNCHPROCESSCOMMAND_H

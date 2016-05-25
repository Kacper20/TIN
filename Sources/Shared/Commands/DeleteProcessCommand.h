//
// Created by dawid on 25.05.16.
//

#ifndef TIN_DELETEPROCESSCOMMAND_H
#define TIN_DELETEPROCESSCOMMAND_H

#include "Command.h"

class DeleteProcessCommand: public Command {

private:

public:
    std::string processId;
    DeleteProcessCommand (Json::Value json);
    DeleteProcessCommand (std::string processId): Command(CommandType::DELETE_PROCESS),
                                                  processId(processId){};
    Json::Value generateJSON();
};


#endif //TIN_DELETEPROCESSCOMMAND_H

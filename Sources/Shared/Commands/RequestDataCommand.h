//
// Created by dawid on 26.05.16.
//

#ifndef TIN_REQUESTDATACOMMAND_H
#define TIN_REQUESTDATACOMMAND_H
#include "Command.h"


class RequestDataCommand: public Command {

private:

public:
    std::string processId;
    std::string date;
    int timestamp;
    RequestDataCommand (Json::Value json);
    RequestDataCommand (std::string processId, std::string date, int timestamp): Command(CommandType::REQUEST_DATA),
                                                                             processId(processId), date(date), timestamp(timestamp) {}
    Json::Value generateJSON();
};


#endif //TIN_REQUESTDATACOMMAND_H

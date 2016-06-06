//
// Created by dawid on 06.06.16.
//

#include <iostream>
#include "ResponseDeserializer.h"
#include "../Shared/Responses/FailedResponse.h"
#include "../Shared/Responses/LaunchProcessResponse.h"
#include "../Shared/Responses/ProcessStatisticsResponse.h"
#include "../Shared/Responses/ScheduledProcessEndedResponse.h"
#include "../Shared/Responses/StartProcessResponse.h"
#include "../Shared/Commands/DeleteProcessCommand.h"


std::shared_ptr<Response> ResponseDeserializer::parseToResponse(std::string json){

    Json::Reader reader;
    Json::Value root;
    bool parsingSucceeded = reader.parse(json.c_str(), root);
    if (!parsingSucceeded) {
        //TODO: Create our own logger as singleton and run it here - error handle.
        std::cout << "Could not parse json" << std::endl;
        return nullptr;
    }
    const std::string type = root[JSONConstants::ResponseType].asString();
    if (type == descriptionForResponseType(ResponseType::START_NEW_PROCESS)) {
        std::shared_ptr<Response> deserializedResponse = std::make_shared<StartProcessResponse>(root);
        return deserializedResponse;
    }
    if (type == descriptionForResponseType(ResponseType::GET_STATISTICS_ABOUT_PROCESS)) {
        std::shared_ptr<Response> deserializedResponse = std::make_shared<ProcessStatisticsResponse>(root);
        return deserializedResponse;
    }
    if (type == descriptionForResponseType(ResponseType::LAUNCH_PROCESS)) {
        std::shared_ptr<Response> deserializedResponse = std::make_shared<LaunchProcessResponse>(root);
        return deserializedResponse;
    }
    if (type == descriptionForResponseType(ResponseType::SCHEDULED_PROCESS_ENDED)) {
        std::shared_ptr<Response> deserializedResponse = std::make_shared<ScheduledProcessEndedResponse>(root);
        return deserializedResponse;
    }
    return nullptr;
}
//
// Created by dawid on 06.06.16.
//

#ifndef TIN_RESPONSEDESERIALIZER_H
#define TIN_RESPONSEDESERIALIZER_H

#include "../Libraries/json/json.h"
#include <string>
#include "../Shared/Commands/Command.h"
#include "../Shared/Responses/Response.h"
#include <memory>

class ResponseDeserializer {
public:
    static std::shared_ptr<Response> parseToResponse(std::string json );
};


#endif //TIN_RESPONSEDESERIALIZER_H

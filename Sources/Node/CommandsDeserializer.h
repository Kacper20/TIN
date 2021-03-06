//
// Created by Kacper Harasim on 09.05.2016.
//

#ifndef TIN_COMMANDSRECOGNIZER_H
#define TIN_COMMANDSRECOGNIZER_H
#include "../Libraries/json/json.h"
#include <string>
#include "../Shared/Commands/Command.h"
#include <memory>

class CommandsDeserializer {
 public:
  static std::shared_ptr<Command> parseToCommand(std::string json );
};


#endif //TIN_COMMANDSRECOGNIZER_H

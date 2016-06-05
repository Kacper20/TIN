//
// Created by Kacper Harasim on 05.06.2016.
//

#ifndef TIN_PROCESSDONOTEXISTONNODE_H
#define TIN_PROCESSDONOTEXISTONNODE_H


#include <string>
#include "ErrorCodeMessageExceptionBase.h"

class ProcessDoNotExistOnNode: public ErrorCodeMessageExceptionBase {

 public:
  ProcessDoNotExistOnNode(std::string message, int errorCode);
};


#endif //TIN_PROCESSDONOTEXISTONNODE_H

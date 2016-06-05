//
// Created by Kacper Harasim on 05.06.2016.
//

#include <string>
#include "ErrorCodeMessageExceptionBase.h"

ErrorCodeMessageExceptionBase::ErrorCodeMessageExceptionBase(std::string message, int errorCode) : m_sMessage(message), m_iErrorCode(errorCode)
{

}

std::string ErrorCodeMessageExceptionBase::GetMessage()
{
  return this->m_sMessage;
}

int ErrorCodeMessageExceptionBase::GetErrorCode()
{
  return this->m_iErrorCode;
}
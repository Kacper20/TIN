//
// Created by Kacper Harasim on 05.06.2016.
//

#ifndef TIN_ERRORCODEMESSAGEEXCEPTIONBASE_H
#define TIN_ERRORCODEMESSAGEEXCEPTIONBASE_H


class ErrorCodeMessageExceptionBase : public std::exception
{
public:
    ErrorCodeMessageExceptionBase(std::string message, int errorCode);
    std::string GetMessage();
    int GetErrorCode();
protected:
    std::string m_sMessage;
    int m_iErrorCode;
};



#endif //TIN_ERRORCODEMESSAGEEXCEPTIONBASE_H

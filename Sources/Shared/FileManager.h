//
// Created by Kacper Harasim on 15.05.2016.
//

#ifndef TIN_FILEMANAGER_H
#define TIN_FILEMANAGER_H

#include <sys/stat.h>
#include <string>

class FileManager {

 public:
  static int createDirectoryAtPath(std::string path);
};


#endif //TIN_FILEMANAGER_H

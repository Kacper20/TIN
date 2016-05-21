//
// Created by Kacper Harasim on 15.05.2016.
//

#ifndef TIN_FILEMANAGER_H
#define TIN_FILEMANAGER_H

#include <sys/stat.h>
#include <string>

class FileManager {

 public:
  static int createDirectoryAtPath(const std::string& path);
  static void writeToFile(const std::string& path, const std::string& content);
  static std::string buildPath(const std::string& base, const std::string& subpath);
};


#endif //TIN_FILEMANAGER_H

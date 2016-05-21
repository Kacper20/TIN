//
// Created by Kacper Harasim on 15.05.2016.
//

#include <fstream>
#include "FileManager.h"

int FileManager::createDirectoryAtPath(const std::string& path) {
  return mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

void FileManager::writeToFile(const std::string &path, const std::string &content) {
  std::ofstream file(path);
  file << content;
  file.close();
}

std::string FileManager::buildPath(const std::string &base, const std::string &subpath) {
  return base + "/" + subpath;
}
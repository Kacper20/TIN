//
// Created by Kacper Harasim on 15.05.2016.
//

#include <fstream>
#include "FileManager.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <boost/uuid/uuid.hpp>

int FileManager::createDirectoryAtPath(const std::string& path) {
  return mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

void FileManager::writeToFile(const std::string &path, const std::string &content) {
  std::ofstream file(path);
  file << content;
  file.close();
}

std::string FileManager::readFromFile(const std::string &path) {
  std::ifstream ifs(path);
  std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
  return content;
}

std::string FileManager::buildPath(const std::string &base, const std::string &subpath) {
  return base + "/" + subpath;
}

int FileManager::deleteDirectoryAtPath(const std::string &path) {
  return rmdir(path.c_str());
}

std::string FileManager::homeDir() {
  const char *homedir;

  if ((homedir = getenv("HOME")) == NULL) {
    homedir = getpwuid(getuid())->pw_dir;
  }
  return std::string(homedir);
}
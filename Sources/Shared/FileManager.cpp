//
// Created by Kacper Harasim on 15.05.2016.
//

#include "FileManager.h"

int FileManager::createDirectoryAtPath(std::string path) {
  return mkdir("foo", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}
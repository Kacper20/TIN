//
// Created by Kacper Harasim on 15.05.2016.
//

#include <fstream>
#include "FileManager.h"
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <boost/uuid/uuid.hpp>
#include <fts.h>

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
  int ret = 0;
  FTS *ftsp = NULL;
  FTSENT *curr;

  // Cast needed (in C) because fts_open() takes a "char * const *", instead
  // of a "const char * const *", which is only allowed in C++. fts_open()
  // does not modify the argument.
  char *files[] = { (char *) path.c_str(), NULL };

  // FTS_NOCHDIR  - Avoid changing cwd, which could cause unexpected behavior
  //                in multithreaded programs
  // FTS_PHYSICAL - Don't follow symlinks. Prevents deletion of files outside
  //                of the specified directory
  // FTS_XDEV     - Don't cross filesystem boundaries
  ftsp = fts_open(files, FTS_NOCHDIR | FTS_PHYSICAL | FTS_XDEV, NULL);
  if (!ftsp) {
    fprintf(stderr, "%s: fts_open failed: %s\n", path.c_str(), strerror(errno));
    ret = -1;
    goto finish;
  }

  while ((curr = fts_read(ftsp))) {
    switch (curr->fts_info) {
      case FTS_NS:
      case FTS_DNR:
      case FTS_ERR:
        fprintf(stderr, "%s: fts_read error: %s\n",
                curr->fts_accpath, strerror(curr->fts_errno));
        break;

      case FTS_DC:
      case FTS_DOT:
      case FTS_NSOK:
        // Not reached unless FTS_LOGICAL, FTS_SEEDOT, or FTS_NOSTAT were
        // passed to fts_open()
        break;

      case FTS_D:
        // Do nothing. Need depth-first search, so directories are deleted
        // in FTS_DP
        break;

      case FTS_DP:
      case FTS_F:
      case FTS_SL:
      case FTS_SLNONE:
      case FTS_DEFAULT:
        if (remove(curr->fts_accpath) < 0) {
          fprintf(stderr, "%s: Failed to remove: %s\n",
                  curr->fts_path, strerror(errno));
          ret = -1;
        }
        break;
    }
  }

  finish:
  if (ftsp) {
    fts_close(ftsp);
  }

  return ret;
}

std::string FileManager::homeDir() {
  const char *homedir;

  if ((homedir = getenv("HOME")) == NULL) {
    homedir = getpwuid(getuid())->pw_dir;
  }
  return std::string(homedir);
}
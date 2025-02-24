// utilities
#include "utilities.h"

// c++
#include <algorithm>
#include <vector>
#include <filesystem>

using namespace std;

namespace utilities {


    string getFileFromPath(const std::string &path) {
        std::size_t lastSlashPos = path.find_last_of('/');
        if (lastSlashPos == std::string::npos) {
            // No slashes found, return the entire path
            return path;
        }
        return path.substr(lastSlashPos + 1);
    }

    string getDirFromPath(const std::string &path) {
        auto lastSlash = path.find_last_of('/');
        if (lastSlash == std::string::npos) return ".";
        return path.substr(0, lastSlash);
    }


    // use modern C++17 filesystem library instead of sys/stat.h
    bool directoryExists(const std::string &path) {
        return filesystem::is_directory(path);
    }

    // use modern C++17 filesystem library instead of dirent.h
    bool hasExtension(const std::string &filename, const std::vector <std::string> &extensions) {
        for (const auto &ext: extensions) {
            if (filename.size() >= ext.size() && filename.compare(filename.size() - ext.size(), ext.size(), ext) == 0) {
                return true;
            }
        }
        return false;
    }

    // use modern C++17 filesystem library instead of dirent.h
    vector <string> getListOfFilesInDirectory(const string &dirName, const vector <string> &extensions) {
        vector <string> files;
        for (const auto &entry: filesystem::directory_iterator(dirName)) {
            if (entry.is_regular_file() && hasExtension(entry.path(), extensions)) {
                files.push_back(entry.path());
            }
        }
        return files;
    }

    vector<string> getListOfSubDirectories(const string& dirName) {
        vector<string> subdirs;
        for (const auto &entry: filesystem::directory_iterator(dirName)) {
            if (entry.is_directory()) {
                subdirs.push_back(entry.path());
            }
        }
        return subdirs;
    }

}

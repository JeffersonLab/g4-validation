#ifndef  UTILITIES_H
#define  UTILITIES_H  1

// c++
#include <vector>
#include <string>
#include <map>


using std::string;
using std::vector;
using std::map;


namespace utilities {

    std::string getFileFromPath(const std::string &path);
    std::string getDirFromPath(const std::string &path);
    bool directoryExists(const std::string &path);
    bool hasExtension(const string& filename, const vector<string>& extensions);
    vector<string> getListOfFilesInDirectory(const string& dirName, const vector<string>& extensions);
    vector<string> getListOfSubDirectories(const string& dirName);

}

#endif

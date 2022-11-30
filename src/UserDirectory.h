/*
	UserDirectory.h
    
	@author Mohamed Salah Abdelfatah
	@version 1.0 30/11/2020
*/

#ifndef _UserDirectory_H_
#define _UserDirectory_H_

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <map>
#include <openssl/sha.h>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>

class UserDirectory
{
private:

    struct fileData
    {
        std::string fileName;
        std::string filePath;
        int fileType;
    };

    std::string directoryPath;
    std::vector<fileData> files;

public:

    UserDirectory() {}
    ~UserDirectory() {}

    bool setDirectoryPath(std::string directoryPath);
    std::string getDirectoryPath();
    std::vector<UserDirectory::fileData> getDirectoryFiles();
    std::map<std::string, std::string> getFilesHASH();
    std::string fileHASH(std::string file);
    std::string hexStr(const uint8_t* data, int len);
};


#endif // _UserDirectory_H_

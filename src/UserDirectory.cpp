/*
	UserDirectory.cpp
    
	@author Mohamed Salah Abdelfatah
	@version 1.0 30/11/2020
*/

#include "UserDirectory.h"
#include <dirent.h>

bool UserDirectory::setDirectoryPath(std::string dir)
{
    //std::cin >> directoryPath;
    
    directoryPath = dir;
    DIR* directory = opendir(directoryPath.c_str());

    //windows check if directory not exist
    if (directory == nullptr)
    {
      closedir(directory);
      return false;
    }
    else
    {
        //double check for linux & windows if path is directory
        struct dirent* file;
        file = readdir(directory);
        if (file != nullptr)
        {
            //if it's not a directory close the file and return
            if (file->d_type != DT_DIR)
            {
                closedir(directory);
                return false;
            }
        }
    }
  
  return true;
}

/*
getDirectoryPath()
Return the Directory Path
*/
std::string UserDirectory::getDirectoryPath()
{
  return directoryPath;
}

/*
getDirectoryFiles()
return a vector of files {filename, filepath, filetype}
*/
std::vector<UserDirectory::fileData> UserDirectory::getDirectoryFiles()
{
    DIR* directory = opendir(directoryPath.c_str());
    struct dirent* file;
    while ((file = readdir(directory)) != nullptr)
    {
        std::string filename(file->d_name);
        
        /* Exclude the . and .. files */
        if (filename != "." && filename != "..")
        {
            fileData newFile;
            newFile.fileName = filename;
            newFile.filePath = directoryPath + "/" + filename;
            newFile.fileType = file->d_type;
            
            /* Add the file struct to vector */
            files.push_back(newFile);
        }
    }
    closedir(directory);
    return files;
}

/*
getFilesHASH()
Return a map with key:filename value:hash of the file
*/
std::map<std::string, std::string> UserDirectory::getFilesHASH()
{
    std::map<std::string, std::string> filesHash;

    for (auto& file : files)
    {  
        if (file.fileType != DT_DIR)
        {
            filesHash[file.fileName] = fileHASH(file.filePath);
        }
    }

    return filesHash;
}

/*
fileHASH()
take the file path as input and Return HASH String
*/
std::string UserDirectory::fileHASH(std::string file)
{
    unsigned char output[32];

    std::ifstream fileStream(file, std::ios::in | std::ios::binary);

    if (!fileStream.is_open())
        exit(1);

    std::ifstream fileSize(file, std::ifstream::ate | std::ifstream::binary);
    size_t length = fileSize.tellg();
    fileSize.close();

    char* fileData = new char[length];

    fileStream.read(fileData, length);

    fileStream.close();

    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, fileData, length);
    SHA256_Final(output, &sha256);
  
  	//deallocate memory
    delete[] fileData;

    return hexStr(output, 32);
}

/*
hexStr()
Convert byteArray into hex string to be displayed on GUI.
*/
std::string UserDirectory::hexStr(const uint8_t* data, int len)
{
    std::stringstream stringStream;
    stringStream << std::hex;

    for (int i(0); i < len; ++i)
        stringStream << std::setw(2) << std::setfill('0') << (int)data[i];

    return stringStream.str();
}

# CPPND: Capstone Compare Folders GUI

This is my Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213).

The Compare Folders APP is a simple GUI Tool that compares the difference between two different Directories and shows the difference whether any files have been added, modified or deleted.

The user enters the two paths and then click on Action > Compare, The tool checks if the two paths are exist or not, if it's not exist it will alert the user. The Tool uses SHA-256 HASH Algorithm to compare the files inside each directory and then display the result.

## Screens

Main

![MainAPP](https://user-images.githubusercontent.com/19867149/204784443-fc2b03b9-ed10-4d2c-92ac-ebf1c4d32c70.PNG)

Alerts

![CheckFolders](https://user-images.githubusercontent.com/19867149/204784435-9acf9784-1e0f-4847-a785-6f180186b003.PNG)

Result

![ResultHash](https://user-images.githubusercontent.com/19867149/204784440-9b1f9790-6567-411b-afba-c3e797ec3161.PNG)

This Tool will help you check the integrity of files of two different versions of folders.

## Structure

```
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
```

## Dependencies for Running Locally
* cmake >= 3.7
* make >= 4.1 (Linux), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* wxWidgets >= 3.0
  * Linux: `sudo apt-get install libwxgtk3.0-gtk3-dev libwxgtk3.0-gtk3-0v5`. If you are facing unmet dependency issues, refer to the [official page](https://wiki.codelite.org/pmwiki.php/Main/WxWidgets30Binaries#toc2) for installing the unmet dependencies.
  * Installation instructions can be found [here](https://wiki.wxwidgets.org/Install). Some version numbers may need to be changed in instructions to install v3.0 or greater.
* OpenSSL check this link for install OpenSSL [here](https://github.com/openssl/openssl)
  * Linux: installation command `sudo apt-get install libssl-dev`
  * Windows: installation command `choco install openssl`

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./CompareFoldersGUI`.

## Rubric points are addressed

- The project code is clearly organized into functions.
  - UserDirectory.cpp
- The project reads data from an external file or writes data to a file as part of the necessary operation of the program.
  - UserDirectory.cpp line 86
- The project accepts input from a user as part of the necessary operation of the program.
  - Main.cpp line 72
- The project code is organized into classes with class attributes to hold the data, and class methods to perform tasks.
  - UserDirectory.cpp UserDirectory.h
- All class data members are explicitly specified as public, protected, or private.
 - UserDirectory.cpp UserDirectory.h
- At least one class that uses unmanaged dynamically allocated memory, along with any class that otherwise needs to modify state upon the termination of an object, uses a destructor.
  - UserDirectory.cpp line 107
- All class member functions document their effects, either through function names, comments, or formal documentation. Member functions do not change program state in undocumented ways.
  - UserDirectory.cpp

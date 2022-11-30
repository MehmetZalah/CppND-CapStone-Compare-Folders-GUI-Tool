cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall -lcrypto")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(CompareFoldersGUI)
link_libraries(ssl crypto)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_executable(CompareFoldersGUI src/main.cpp src/UserDirectory.cpp)
target_link_libraries(CompareFoldersGUI ${wxWidgets_LIBRARIES})
target_link_libraries(CompareFoldersGUI ssl)
target_include_directories(CompareFoldersGUI PRIVATE ${wxWidgets_INCLUDE_DIRS})
cmake_minimum_required(VERSION 2.6)
project(orgaDatos)
set(CMAKE_CXX_FLAGS "-std=c++0x")
add_executable(exe  src/argHandler/Args.cpp
                    src/argHandler/ArgHandler.cpp
                    src/main.cpp
                    src/filesManagers/BlockFileManager.cpp src/filesManagers/BlockFileManager.h
                    src/filesManagers/RegisterFileManager.cpp src/filesManagers/RegisterFileManager.h
                    src/filesManagers/FileManager.h
                    src/commandFactory/CommandFactory.cpp src/commandFactory/CommandFactory.h
                    src/commandFactory/Command.cpp src/commandFactory/Command.h
                    src/commandFactory/CreateCommand.cpp src/commandFactory/CreateCommand.h
                    src/filesStructure/FileHeader.cpp src/filesStructure/FileHeader.h)
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
                    src/filesStructure/FileHeader.cpp src/filesStructure/FileHeader.h src/commandFactory/InsertCommand.cpp src/commandFactory/InsertCommand.h src/filesManagers/FileHandler.cpp src/filesManagers/FileHandler.h src/filesStructure/Register.cpp src/filesStructure/Register.h src/filesStructure/Field/FieldFactory.cpp src/filesStructure/Field/FieldFactory.h src/filesStructure/Field/Field.cpp src/filesStructure/Field/Field.h src/filesStructure/Field/IntField.cpp src/filesStructure/Field/IntField.h src/filesStructure/Field/StringField.cpp src/filesStructure/Field/StringField.h src/filesStructure/Field/DateField.cpp src/filesStructure/Field/DateField.h)
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
                    src/filesStructure/FileHeader.cpp src/filesStructure/FileHeader.h src/commandFactory/InsertCommand.cpp src/commandFactory/InsertCommand.h src/filesStructure/Register.cpp src/filesStructure/Register.h src/filesStructure/Field/FieldFactory.cpp src/filesStructure/Field/FieldFactory.h src/filesStructure/Field/Field.cpp src/filesStructure/Field/Field.h src/filesStructure/Field/IntField.cpp src/filesStructure/Field/IntField.h src/filesStructure/Field/StringField.cpp src/filesStructure/Field/StringField.h src/filesStructure/Field/DateField.cpp src/filesStructure/Field/DateField.h src/filesManagers/FileManager.cpp src/filesStructure/Block.cpp src/filesStructure/Block.h src/filesStructure/OcupationMap.cpp src/filesStructure/OcupationMap.h src/filesStructure/FreeRegOffset.cpp src/filesStructure/FreeRegOffset.h src/commandFactory/DeleteCommand.cpp src/commandFactory/DeleteCommand.h src/commandFactory/SelectCommand.cpp src/commandFactory/SelectCommand.h src/commandFactory/ProyectionCommand.cpp src/commandFactory/ProyectionCommand.h src/commandFactory/MultiplyCommand.cpp src/commandFactory/MultiplyCommand.h src/commandFactory/UnionCommand.cpp src/commandFactory/UnionCommand.h src/commandFactory/CSVCommand.cpp src/commandFactory/CSVCommand.h)
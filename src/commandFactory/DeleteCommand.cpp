//
// Created by Jorge Galloni on 9/25/16.
//

#include <iostream>
#include "DeleteCommand.h"
#include "../argHandler/Args.h"
#include "../filesManagers/FileManager.h"

DeleteCommand::DeleteCommand(Args args) {
    this->rawRegister = args.getModifiers();
    this->fileManager = FileManager::getFileManager(args.getOutFile());
}

void DeleteCommand::execute() const {
    this->fileManager->openFile();
    this->fileManager->deleteReg(this->rawRegister);
    this->fileManager->closeFile();
    std::cout<<"Archivo cerrado con exito"<<std::endl;
}
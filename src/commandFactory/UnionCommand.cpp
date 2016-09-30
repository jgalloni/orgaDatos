//
// Created by Jorge Galloni on 9/28/16.
//

#include <iostream>
#include "UnionCommand.h"
#include "../filesManagers/BlockFileManager.h"
#include "../filesManagers/RegisterFileManager.h"

UnionCommand::UnionCommand(Args args) {
    this->fileManager = FileManager::getFileManager(args.getInFile());
    this->infileManager = FileManager::getFileManager(args.getModifiers());
    FileHeader * fileHeader= this->fileManager->cloneHeader();
    args.setOutType(this->fileManager->getType());
    if(args.getOutType()==FileType::bloque) {
        this->outFileManager = new BlockFileManager(fileHeader, args.getOutFile());
    }
    else if(args.getOutType()==FileType::registro) {
        this->outFileManager = new RegisterFileManager(fileHeader, args.getOutFile());
    }
}

void UnionCommand::execute() const {
    this->fileManager->openFile();
    this->infileManager->openFile();
    this->outFileManager->createFile();
    this->outFileManager->openFile();
    int id=0;
    while(!this->fileManager->end()){
        std::vector<Register> regs= this->fileManager->getNext(&id);
        this->outFileManager->insert(regs);
    }
    this->fileManager->closeFile();
    while(!this->infileManager->end()){
        std::vector<Register> regs= this->infileManager->getNext(&id);
        this->outFileManager->insert(regs);
    }
    this->infileManager->closeFile();
    this->outFileManager->closeFile();
    std::cout<<"Archivo cerrado con exito"<<std::endl;
}

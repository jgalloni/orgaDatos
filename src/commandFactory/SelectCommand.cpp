//
// Created by Jorge Galloni on 9/25/16.
//

#include <iostream>
#include <vector>
#include "SelectCommand.h"
#include "../filesManagers/BlockFileManager.h"
#include "../filesManagers/RegisterFileManager.h"
#include "../filesStructure/Register.h"

SelectCommand::SelectCommand(Args args) {
    this->condition = args.getModifiers();
    this->value = args.getModifiers2();
    this->fileManager = FileManager::getFileManager(args.getInFile());
    args.setOutType(this->fileManager->getType());
    FileHeader * fileHeader= new FileHeader(args);
    if(args.getOutType()==FileType::bloque) {
        this->outFileManager = new BlockFileManager(fileHeader, args.getOutFile());
    }
    else if(args.getOutType()==FileType::registro) {
        this->outFileManager = new RegisterFileManager(fileHeader, args.getOutFile());
    }
}

void SelectCommand::execute() const {
    this->fileManager->openFile();
    this->outFileManager->createFile();
    this->outFileManager->openFile();
    std::vector<Register> regs= this->fileManager->find(this->field,this->condition,this->value);
    this->outFileManager->insert(regs);
    this->fileManager->closeFile();
    this->outFileManager->closeFile();
    std::cout<<"Archivo cerrado con exito"<<std::endl;
}
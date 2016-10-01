//
// Created by Jorge Galloni on 9/28/16.
//

#include <iostream>
#include "MultiplyCommand.h"
#include "../filesManagers/BlockFileManager.h"
#include "../filesManagers/RegisterFileManager.h"

MultiplyCommand::MultiplyCommand(Args args) {
    this->fileManager = FileManager::getFileManager(args.getInFile());
    this->infileManager = FileManager::getFileManager(args.getModifiers());
    FileHeader * fileHeader= this->fileManager->cloneHeader();
    fileHeader->merge(infileManager->getHeader());
    std::cout<<fileHeader->toCSV()<<std::endl;
    args.setOutType(this->fileManager->getType());
    if(args.getOutType()==FileType::bloque) {
        this->outFileManager = new BlockFileManager(fileHeader, args.getOutFile());
    }
    else if(args.getOutType()==FileType::registro) {
        this->outFileManager = new RegisterFileManager(fileHeader, args.getOutFile());
    }
}

void MultiplyCommand::execute() const {
    this->fileManager->openFile();
    this->infileManager->openFile();
    this->outFileManager->createFile();
    std::cout<<this->outFileManager->getHeader()->toCSV()<<std::endl;
    this->outFileManager->openFile();
    int id=0;
    while(!this->fileManager->end()){
        std::vector<Register> regs= this->fileManager->getNext();
        while(!this->infileManager->end()) {
            std::vector<Register> regs2= this->infileManager->getNext();
            std::vector<Register> regsjoined=this->multiply(regs,regs2,&id);
            this->outFileManager->insert(regsjoined);

        }
        this->infileManager->reset();
    }
    this->fileManager->closeFile();
    this->infileManager->closeFile();
    this->outFileManager->closeFile();
    std::cout<<"Archivo cerrado con exito"<<std::endl;
}

std::vector<Register> MultiplyCommand::multiply(std::vector<Register> reg1, std::vector<Register> reg2,int *initiid) const {
    std::vector<Register>out;
    for (int i = 0; i < reg1.size(); ++i) {
        for (int j = 0; j < reg2.size(); ++j) {
            out.push_back(*(reg1[i].join(reg2[j],(*initiid))));
            (*initiid)++;
        }
    }
    return out;
}

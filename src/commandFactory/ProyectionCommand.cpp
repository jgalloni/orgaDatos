//
// Created by Jorge Galloni on 9/28/16.
//

#include <sstream>
#include "ProyectionCommand.h"
#include "../filesManagers/BlockFileManager.h"
#include "../filesManagers/RegisterFileManager.h"

ProyectionCommand::ProyectionCommand(Args args) {
    this->fields=args.getModifiers();
    this->fileManager= FileManager::getFileManager(args.getInFile());
    FileHeader * fileHeader= this->fileManager->cloneHeader(args.getModifiers());
    fileHeader->proyectFields(args.getModifiers());
    args.setOutType(this->fileManager->getType());
    if(args.getOutType()==FileType::bloque) {
        this->outFileManager = new BlockFileManager(fileHeader, args.getOutFile());
    }
    else if(args.getOutType()==FileType::registro) {
        this->outFileManager = new RegisterFileManager(fileHeader, args.getOutFile());
    }
}

void ProyectionCommand::execute() const {
    this->fileManager->openFile();
    this->outFileManager->createFile();
    this->outFileManager->openFile();
    std::stringstream ss(this->fields);
    std::string reg;
    std::vector<int> nlist;
    int newSize=0;
    while(std::getline(ss,reg,',')){
        nlist.push_back(this->fileManager->getFieldPosition(reg));
        newSize++;
    }
    while(!this->fileManager->end()){
        std::vector<Register> regs= this->fileManager->getNextAndProyect(nlist.data(),newSize);
        this->outFileManager->insert(regs);
    }
}
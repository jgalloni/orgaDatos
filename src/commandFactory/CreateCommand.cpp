//
// Created by Jorge Galloni on 9/19/16.
//

#include <iostream>

#include "CreateCommand.h"
#include "../filesManagers/BlockFileManager.h"
#include "../filesManagers/RegisterFileManager.h"

void CreateCommand::execute() const{
    this->fileManager->createFile();
}

CreateCommand::CreateCommand(Args args) {
    FileHeader * fileHeader= new FileHeader(args);
    if(args.getOutType()==FileType::bloque)
        this->fileManager= new BlockFileManager(fileHeader,args.getOutFile());
    else if(args.getOutType()==FileType::registro)
        this->fileManager= new RegisterFileManager(fileHeader,args.getOutFile());
    std::cout<<"Archivo cerrado con exito"<<std::endl;
}

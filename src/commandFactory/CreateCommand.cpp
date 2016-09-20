//
// Created by Jorge Galloni on 9/19/16.
//

#include <iostream>
#include "CreateCommand.h"

void CreateCommand::execute() const{
    std::cout<<"Creando archivo"<<this->fileName;
}

CreateCommand::CreateCommand(Args args) {
    this->fileHeader= new FileHeader(args);
    this->fileName = args.getOutFile();
}

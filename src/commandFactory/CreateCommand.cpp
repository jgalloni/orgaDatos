//
// Created by Jorge Galloni on 9/19/16.
//

#include <iostream>
#include <fstream>
#include "CreateCommand.h"

void CreateCommand::execute() const{
    std::cout<<"Creando archivo"<<this->fileName<<std::endl;
    std::ofstream out(this->fileName,std::ios::binary);
    if(!out.is_open()){
        std::cout<<"Error al crear el archivo"<<this->fileName<<std::endl;
        return;
    }
    std::cout<<"Header serializado"<<std::endl;
    out.write(this->fileHeader->Serialize(),512);
    std::cout<<"Mapa de ocupacion generado"<<std::endl;
    bool temp[512];
    for(int i=0;i<512;i++){
        temp[i]=false;
    }
    out.write((char*)temp,512);
    out.close();
    std::cout<<"Archivo creado"<<std::endl;
}

CreateCommand::CreateCommand(Args args) {
    this->fileHeader= new FileHeader(args);
    this->fileName = args.getOutFile();
}

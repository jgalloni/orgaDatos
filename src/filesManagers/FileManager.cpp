//
// Created by Jorge Galloni on 9/24/16.
//


#include <iostream>
#include "FileManager.h"
#include "BlockFileManager.h"
#include "RegisterFileManager.h"
#include <fstream>

void FileManager::createFile(){
    std::cout<<"Creando archivo: "<<this->fileName<<std::endl;
    std::ofstream out(this->fileName,std::ios::binary);
    if(!out.is_open()){
        std::cout<<"Error al crear el archivo: "<<this->fileName<<std::endl;
        return;
    }
    std::cout<<"Header serializado"<<std::endl;
    out.write(this->fileHeader->Serialize(),512);
    std::cout<<"Mapa de ocupacion generado"<<std::endl;
    if(this->fileHeader->getFileType()==FileType::bloque){
        OcupationMap oc(512*this->fileHeader->getBlockSize());
        out.write(oc.serialize(),512*this->fileHeader->getBlockSize()*sizeof(char));
    } else{
        FreeRegOffset fro;
        out.write(fro.serialize(),512);
    }
    out.close();
    std::cout<<"Archivo creado"<<std::endl;
}

void FileManager::openFile() {
    std::cout<<"abriendo archivo:"<<this->fileName<<std::endl;
    this->fstream= new std::fstream(this->fileName,std::ios::binary|std::ios::in|std::ios::out);

}

FileManager *FileManager::getFileManager(std::string name) {
    std::ifstream in(name,std::ios::binary);
    if(!in.is_open()){
        std::cout<<"Error al abrir el archivo: "<<name<<std::endl;
        return nullptr;
    }
    char temp[512];
    in.read(temp,512);
    std::cout<<"Cargando Header en memoria"<<std::endl;
    FileHeader * fh = new FileHeader(temp);
    std::cout<<"Header cargado en memoria"<<std::endl;
    in.close();
    if(fh->getFileType()==FileType::bloque){
        return new BlockFileManager(fh,name);
    } else if(fh->getFileType()==FileType::registro){
        return new RegisterFileManager(fh,name);
    }
    return nullptr;
}

void FileManager::closeFile() {
    this->fstream->close();
}



//
// Created by coco on 06/09/16.
//

#include <iostream>
#include <fstream>

#include "RegisterFileManager.h"
#include "../filesStructure/Register.h"


RegisterFileManager::RegisterFileManager(FileHeader *fileHeader, std::string fileName) {
    this->fileHeader=fileHeader;
    this->fileName=fileName;
}

RegisterFileManager::RegisterFileManager(std::string filename) {
    this->fileName=filename;
}

void RegisterFileManager::insert(std::string reg) const {
    if(this->fileHeader->getLastId()==0){
        Register registro(reg,this->fileHeader);
        this->ofstream->seekp(0, std::ios::end);
        int size=0;
        char * tmp = registro.serialize(&size);
        this->ofstream->write(reinterpret_cast<char*>(&size), sizeof(int));
        this->ofstream->write(tmp,size * sizeof(char));
    } else {
    }
}

void RegisterFileManager::openFile() {
    FileManager::openFile();
    ifstream->seekg(512);
    std::cout<<"Cargando Mapa de ocupacion en memoria"<<std::endl;
    char *tmp = (char *) malloc(sizeof(char) * 512);
    ifstream->read(tmp,sizeof(char) * 512);
    this->ocupationMap = new OcupationMap(tmp,sizeof(char) * 512);
}

//
// Created by coco on 06/09/16.
//

#include <iostream>
#include <fstream>

#include "BlockFileManager.h"
#include "../filesStructure/Register.h"
#include "../filesStructure/Block.h"

BlockFileManager::BlockFileManager(FileHeader * fileHeader,std::string fileName) {
    this->fileHeader=fileHeader;
    this->fileName=fileName;
}

BlockFileManager::BlockFileManager(std::string filename){
    this->fileName=filename;
}

void BlockFileManager::insert(std::string rawReg) const {
    if(this->fileHeader->getLastId()==0){
        std::cout<<"Insertando Registro en el primer bloque con id=0"<<std::endl;
        Register registro(rawReg,this->fileHeader);
        this->ofstream->seekp(ofstream->end);
        Block block(&registro,1);
        this->ofstream->write(block.serialize(fileHeader->getBlockSize()),fileHeader->getBlockSize()* sizeof(char)*512);
        std::cout<<"Registro insertado"<<std::endl;
    } else {
        std::cout<<"Buscando blocke para insertar"<<std::endl;
        bool cont=true;
        int mapSize=512*this->fileHeader->getBlockSize();
        while(cont){
            int blockToWrite = 512*this->ocupationMap->getNextFree();
            this->ifstream->seekg(sizeof(char)*(512+mapSize+blockToWrite));
            char *temp;
            ifstream->read(temp,this->fileHeader->getBlockSize());
            Block block(temp,*(this->fileHeader));
            temp=block.serialize(this->fileHeader->getBlockSize());
            if(temp!= nullptr) {
                ofstream->seekp(sizeof(char) * (512 + mapSize + blockToWrite));
                ofstream->write(temp, this->fileHeader->getBlockSize());
                if (block.getSerializedSize() > 512 * 0, 7 * this->fileHeader->getBlockSize()) {
                    this->ocupationMap->setFullBlock(blockToWrite);
                }
                cont = false;
                std::cout<<"se inserto en el bloque "<<blockToWrite<<std::endl;
            }else {
                std::cout<<"bloque "<<blockToWrite<<" lleno"<<std::endl;
            }
        }
    }
    this->fileHeader->incLastId();
    ofstream->seekp(0);
    std::cout<<"Actualizando header"<<std::endl;
    ofstream->write(this->fileHeader->Serialize(),512);
    std::cout<<"Actualizando Mapa de ocupacion"<<std::endl;
    ofstream->write(this->ocupationMap->serialize(),512*this->fileHeader->getBlockSize());
}

void BlockFileManager::openFile() {
    FileManager::openFile();
    ifstream->seekg(512);
    std::cout<<"Cargando Mapa de ocupacion en memoria"<<std::endl;
    char *tmp = (char *) malloc(sizeof(char) * this->fileHeader->getBlockSize() *512);
    ifstream->read(tmp,sizeof(char) * this->fileHeader->getBlockSize() *512);
    this->ocupationMap = new OcupationMap(tmp,sizeof(char) * this->fileHeader->getBlockSize() *512);
}



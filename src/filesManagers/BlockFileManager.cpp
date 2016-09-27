//
// Created by coco on 06/09/16.
//

#include <iostream>
#include <fstream>
#include <cstring>

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
    Register registro(rawReg,this->fileHeader);
    this->insert(registro);
}

void BlockFileManager::openFile() {
    FileManager::openFile();
    fstream->seekg(512);
    std::cout<<"Cargando Mapa de ocupacion en memoria"<<std::endl;
    char *tmp = (char *) malloc(sizeof(char) * this->fileHeader->getBlockSize() *512);
    fstream->read(tmp,sizeof(char) * this->fileHeader->getBlockSize() *512);
    this->ocupationMap = new OcupationMap(tmp,sizeof(char) * this->fileHeader->getBlockSize() *512);
}

void BlockFileManager::deleteReg(std::string rawReg) const {
    int seekposs=512+(512* this->fileHeader->getBlockSize());
    this->fstream->seekg(seekposs);
    char * tmp= (char *) malloc(512 * this->fileHeader->getBlockSize() * sizeof(char));
    while(this->fstream->eof()){
        this->fstream->read(tmp,512 * this->fileHeader->getBlockSize());
        Block bk(tmp,*this->fileHeader);
        int id=bk.find(rawReg);
        if(id!=-1){
            bk.remove(id);
            memcpy(tmp,bk.serialize(512* this->fileHeader->getBlockSize()),512* this->fileHeader->getBlockSize());
            this->ocupationMap->setNotFull(((seekposs-512)/this->fileHeader->getBlockSize())-1);
        }
        seekposs+=(512* this->fileHeader->getBlockSize());
        this->fstream->seekg(seekposs);
    }
}

FileType BlockFileManager::getType() const {
    return FileType::bloque;
}

std::vector<Register> BlockFileManager::find(std::string field,std::string condition, std::string value) const {
    std::vector<Register> res;
    int seekposs=512+(512* this->fileHeader->getBlockSize());
    this->fstream->seekg(seekposs);
    char * tmp= (char *) malloc(512 * this->fileHeader->getBlockSize() * sizeof(char));
    while (this->fstream->eof()){
        this->fstream->read(tmp,512 * this->fileHeader->getBlockSize());
        Block bk(tmp,*this->fileHeader);
        std::vector<Register> vec=bk.find(this->fileHeader->getFielPossition(field),condition,value);
        res.insert(res.end(), vec.begin(), vec.end());
    }
}

void BlockFileManager::insert(std::vector<Register> reg) const {
    for (int i = 0; i < reg.size(); ++i) {
        this->insert(reg.at(i));
    }
}

void BlockFileManager::insert(Register registro) const {
    if(this->fileHeader->getLastId()==0){
        std::cout<<"Insertando Registro en el primer bloque con id=0"<<std::endl;

        this->fstream->seekp(fstream->end);
        Block block(&registro,1);
        this->fstream->write(block.serialize(fileHeader->getBlockSize()),fileHeader->getBlockSize()* sizeof(char)*512);
        std::cout<<"Registro insertado"<<std::endl;
    } else {
        std::cout<<"Buscando bloque para insertar"<<std::endl;
        bool cont=true;
        int mapSize=512*this->fileHeader->getBlockSize();
        while(cont){
            int blockToWrite = 512*this->ocupationMap->getNextFree();
            this->fstream->seekg(sizeof(char)*(512+mapSize+blockToWrite));
            char *temp;
            fstream->read(temp,this->fileHeader->getBlockSize());
            Block block(temp,*(this->fileHeader));
            block.add(registro);
            temp=block.serialize(this->fileHeader->getBlockSize());
            if(temp!= nullptr) {
                fstream->seekp(sizeof(char) * (512 + mapSize + blockToWrite));
                fstream->write(temp, this->fileHeader->getBlockSize());
                if (block.getSerializedSize() > 512 * 0, 7 * this->fileHeader->getBlockSize()) {
                    this->ocupationMap->setFullBlock(((blockToWrite-512)/this->fileHeader->getBlockSize())-1);
                }
                cont = false;
                std::cout<<"se inserto en el bloque "<<((blockToWrite-512)/this->fileHeader->getBlockSize())-1<<std::endl;
            }else {
                std::cout<<"bloque "<<((blockToWrite-512)/this->fileHeader->getBlockSize())-1<<" lleno"<<std::endl;
            }
        }
    }
    this->fileHeader->incLastId();
    fstream->seekp(0);
    std::cout<<"Actualizando header"<<std::endl;
    fstream->write(this->fileHeader->Serialize(),512);
    std::cout<<"Actualizando Mapa de ocupacion"<<std::endl;
    fstream->write(this->ocupationMap->serialize(),512*this->fileHeader->getBlockSize());
}



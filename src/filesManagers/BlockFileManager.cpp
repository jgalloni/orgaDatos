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
    while(!this->fstream->eof()){
        this->fstream->read(tmp,512 * this->fileHeader->getBlockSize());
        Block bk(tmp,*this->fileHeader);
        if(bk.remove(rawReg)){
            this->fstream->seekg(seekposs);//vuelvo para atras
            memcpy(tmp,bk.serialize(512* this->fileHeader->getBlockSize()),512* this->fileHeader->getBlockSize());
            this->fstream->write(tmp,512* this->fileHeader->getBlockSize());
            this->ocupationMap->setNotFull(((seekposs-512)/this->fileHeader->getBlockSize()*512)-1);
        }
    }
    this->fstream->seekg(512);
    this->fstream->write(this->ocupationMap->serialize(),512);
}

FileType BlockFileManager::getType() const {
    return FileType::bloque;
}

void BlockFileManager::insert(std::vector<Register> reg) const {
    for (int i = 0; i < reg.size(); ++i) {
        this->insert(reg.at(i));
    }
}

void BlockFileManager::insert(Register registro) const {
    if(this->fileHeader->getLastId()==0){
        std::cout<<"Insertando Registro en el primer bloque con id=0"<<std::endl;

        this->fstream->seekp(1024);
        Block block(&registro,1);
        this->fstream->write(block.serialize(fileHeader->getBlockSize()),fileHeader->getBlockSize()* sizeof(char)*512);
        std::cout<<"Registro insertado"<<std::endl;
    } else {
        std::cout<<"Buscando bloque para insertar"<<std::endl;
        bool cont=true;
        int mapSize=512*this->fileHeader->getBlockSize();
        char *temp= (char *) malloc(512 * this->fileHeader->getBlockSize());
        while(cont){
            int blockToWrite = this->ocupationMap->getNextFree();
            this->fstream->clear();
            this->fstream->seekg(sizeof(char)*(512+mapSize+(blockToWrite*512)));
            fstream->read(temp,this->fileHeader->getBlockSize()*512);
            Block block(temp,*(this->fileHeader));
            if(fstream->eof()){
                block.clean();
            }
            block.add(registro);
            char * sblock=block.serialize(this->fileHeader->getBlockSize());
            if(sblock!= nullptr) {
                this->fstream->clear();
                this->fstream->seekp(sizeof(char)*(512+mapSize+(blockToWrite*512)));
                std::cout<<"posicion a escribir: "<<this->fstream->tellp()<<std::endl;
                fstream->write(sblock, this->fileHeader->getBlockSize()*512);
                if (block.getSerializedSize() > 512 * 0.7 * this->fileHeader->getBlockSize()) {
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
    fstream->seekp(0);
    std::cout<<"Actualizando header"<<std::endl;
    fstream->write(this->fileHeader->Serialize(),512);
    std::cout<<"Actualizando Mapa de ocupacion"<<std::endl;
    fstream->write(this->ocupationMap->serialize(),512*this->fileHeader->getBlockSize());
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

std::vector<Register> BlockFileManager::findNext(std::string field, std::string condition, std::string value) {
    std::vector<Register> res;
    if(this->lastPos==0) {
        this->lastPos= 512 + (512 * this->fileHeader->getBlockSize());
        this->fstream->seekg(this->lastPos);
    }
    char * tmp= (char *) malloc(512 * this->fileHeader->getBlockSize() * sizeof(char));
    bool cont=true;
    while (!this->fstream->eof() &&cont){
        this->fstream->read(tmp,512 * this->fileHeader->getBlockSize());
        this->lastPos+=512 * this->fileHeader->getBlockSize();
        Block bk(tmp,*this->fileHeader);
        res=bk.find(this->fileHeader->getFielPossition(field),condition,value);
        if(res.size()>0){
            std::cout<<"se econtraron "<<res.size()<<" registros en el bloque"<<std::endl;
            free(tmp);
            return res;
        }
    }
}

std::vector<Register> BlockFileManager::getNextAndProyect(int* fieldPos,int size) {
    std::vector<Register> res;
    if(this->lastPos==0) {
        this->lastPos= 512 + (512 * this->fileHeader->getBlockSize());
        this->fstream->seekg(this->lastPos);
    }
    char * tmp= (char *) malloc(512 * this->fileHeader->getBlockSize() * sizeof(char));
    this->fstream->read(tmp,512 * this->fileHeader->getBlockSize());
    this->lastPos+=512 * this->fileHeader->getBlockSize();
    Block bk(tmp,*this->fileHeader);
    res=bk.proyect(fieldPos,size);
//    for (int i = 0; i < 512 * this->fileHeader->getBlockSize(); ++i) {
//        free(&(tmp[i]));
//    }
    return res;
}

std::vector<Register> BlockFileManager::getNext(int *pInt) {
    std::vector<Register> res;
    if(this->lastPos==0) {
        this->lastPos= 512 + (512 * this->fileHeader->getBlockSize());
        this->fstream->seekg(this->lastPos);
    }
    char * tmp= (char *) malloc(512 * this->fileHeader->getBlockSize() * sizeof(char));
    this->fstream->read(tmp,512 * this->fileHeader->getBlockSize());
    this->lastPos+=512 * this->fileHeader->getBlockSize();
    Block bk(tmp,*this->fileHeader);
    bk.resetId(pInt);
    return bk.getRegisters();
}

std::vector<Register> BlockFileManager::getNext() {
    std::vector<Register> res;
    if(this->lastPos==0) {
        this->lastPos= 512 + (512 * this->fileHeader->getBlockSize());
        this->fstream->seekg(this->lastPos);
    }
    char * tmp= (char *) malloc(512 * this->fileHeader->getBlockSize() * sizeof(char));
    this->fstream->read(tmp,512 * this->fileHeader->getBlockSize());
    this->lastPos+=512 * this->fileHeader->getBlockSize();
    Block bk(tmp,*this->fileHeader);
    return bk.getRegisters();
}



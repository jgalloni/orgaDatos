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
    Register registro(reg,this->fileHeader);
    this->insert(registro);
}

void RegisterFileManager::openFile() {
    FileManager::openFile();
    std::cout<<"Cargando Mapa de ocupacion en memoria"<<std::endl;
    char tmp[512];
    this->fstream->seekg(512,std::ios::beg);
    std::cout<<this->fstream->tellg()<<std::endl;
    fstream->read(tmp,sizeof(char) * 512);
    this->freeRegOffset = new FreeRegOffset(tmp);
}

void RegisterFileManager::writeReg(int size, char* reg) const {
    this->fstream->write(reinterpret_cast<char*>(&size), sizeof(int));
    this->fstream->write(reg,size * sizeof(char));
    this->fileHeader->incLastId();
    this->fstream->seekp(0);
    this->fstream->write(this->fileHeader->Serialize(),512* sizeof(char));

}

void RegisterFileManager::deleteReg(std::string rawReg) const {
    this->fstream->seekg(1024 * sizeof(char));
    int pos=1024 * sizeof(char);
    while (fstream->eof()) {
        int size=0;
        this->fstream->read((char *) &size, sizeof(int));
        if(size<0){//saltea uno vacio
            pos += -size + sizeof(int);
            this->fstream->seekg(pos);
            continue;
        }else {
            pos += size + sizeof(int);
            if (size < 0) {
                this->fstream->seekg(pos);
            }
        }
        char * tmp= (char *) malloc(size * sizeof(char));
        this->fstream->read(tmp,size);
        Register reg(tmp,this->fileHeader);
        if(reg.cmp(rawReg)){
            this->freeRegOffset->setOcupedOffset(pos);
            this->fstream->seekp(pos);
            this->fstream->write(0, sizeof(int));
            this->fstream->seekp(512);
            this->fstream->write(freeRegOffset->serialize(),512);
        }
    }
}

FileType RegisterFileManager::getType() const {
    return FileType::registro;
}

std::vector<Register> RegisterFileManager::find(std::string field,std::string condition, std::string value) const {
    std::vector<Register> res;
    this->fstream->seekg(1024 * sizeof(char));
    int pos=1024 * sizeof(char);
    int fieldPos = this->fileHeader->getFielPossition(field);
    while (fstream->eof()) {
        int size=0;
        this->fstream->read((char *) &size, sizeof(int));
        if(size<0){//saltea uno vacio
            pos += -size + sizeof(int);
            this->fstream->seekg(pos);
            continue;
        }else {
            pos += size + sizeof(int);
            if (size < 0) {
                this->fstream->seekg(pos);
            }
        }
        char * tmp= (char *) malloc(size * sizeof(char));
        this->fstream->read(tmp,size);
        Register reg(tmp,this->fileHeader);
        if(reg.test(fieldPos,condition,value)){
           res.push_back(reg);
        }
    }
    return res;
}

void RegisterFileManager::insert(std::vector<Register> reg) const {
    for (int i = 0; i < reg.size(); ++i) {
        this->insert(reg.at(i));
    }
}

void RegisterFileManager::insert(Register registro) const {
    int size=0;
    char * tmp = registro.serialize(&size);
    if(this->fileHeader->getLastId()==0){
        this->fstream->seekp(1024);
        std::cout<<this->fstream->tellp()<<std::endl;
        this->writeReg(size, tmp);
        this->freeRegOffset->updateOcupedOffset(0,size+sizeof(int));
        this->fstream->write(this->freeRegOffset->serialize(),512* sizeof(char));
        return;
    } else {
        int seekOff=this->freeRegOffset->nextFreeReg();
        this->fstream->seekp(seekOff+1024);
        while (this->fstream->eof()){
            this->fstream->seekg(seekOff+1024);
            int sfree;
            this->fstream->read((char *) &sfree, sizeof(int));
            if(sfree>size){
                seekOff=this->freeRegOffset->nextFreeReg();
            }else{
                this->writeReg(size, tmp);
                this->freeRegOffset->deleteOcupedOffset(seekOff);
                this->fstream->write(this->freeRegOffset->serialize(),512* sizeof(char));
                return;
            }
            this->fstream->seekp(seekOff+1024);
        }
        this->writeReg(size, tmp);
        this->freeRegOffset->updateOcupedOffset(seekOff,seekOff+size+sizeof(int));
        this->fstream->write(this->freeRegOffset->serialize(),512* sizeof(char));
        return;
    }
}

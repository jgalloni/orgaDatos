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
    ifstream->seekg(512);
    std::cout<<"Cargando Mapa de ocupacion en memoria"<<std::endl;
    char *tmp = (char *) malloc(sizeof(char) * 512);
    ifstream->read(tmp,sizeof(char) * 512);
    this->freeRegOffset = new FreeRegOffset(tmp);
}

void RegisterFileManager::writeReg(int size, char* reg) const {
    this->ofstream->write(reinterpret_cast<char*>(&size), sizeof(int));
    this->ofstream->write(reg,size * sizeof(char));
    this->fileHeader->incLastId();
    this->ofstream->clear();
    this->ofstream->seekp(0);
    this->ofstream->write(this->fileHeader->Serialize(),512* sizeof(char));

}

void RegisterFileManager::deleteReg(std::string rawReg) const {
    this->ifstream->seekg(1024 * sizeof(char));
    int pos=1024 * sizeof(char);
    while (ifstream->eof()) {
        int size=0;
        this->ifstream->read((char *) &size, sizeof(int));
        if(size<0){//saltea uno vacio
            pos += -size + sizeof(int);
            this->ifstream->seekg(pos);
            continue;
        }else {
            pos += size + sizeof(int);
            if (size < 0) {
                this->ifstream->seekg(pos);
            }
        }
        char * tmp= (char *) malloc(size * sizeof(char));
        this->ifstream->read(tmp,size);
        Register reg(tmp,this->fileHeader);
        if(reg.cmp(rawReg)){
            this->freeRegOffset->setOcupedOffset(pos);
            this->ofstream->seekp(pos);
            this->ofstream->write(0, sizeof(int));
            this->ofstream->seekp(512);
            this->ofstream->write(freeRegOffset->serialize(),512);
        }
    }
}

FileType RegisterFileManager::getType() const {
    return FileType::registro;
}

std::vector<Register> RegisterFileManager::find(std::string field,std::string condition, std::string value) const {
    std::vector<Register> res;
    this->ifstream->seekg(1024 * sizeof(char));
    int pos=1024 * sizeof(char);
    int fieldPos = this->fileHeader->getFielPossition(field);
    while (ifstream->eof()) {
        int size=0;
        this->ifstream->read((char *) &size, sizeof(int));
        if(size<0){//saltea uno vacio
            pos += -size + sizeof(int);
            this->ifstream->seekg(pos);
            continue;
        }else {
            pos += size + sizeof(int);
            if (size < 0) {
                this->ifstream->seekg(pos);
            }
        }
        char * tmp= (char *) malloc(size * sizeof(char));
        this->ifstream->read(tmp,size);
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
        this->ofstream->clear();
        this->ofstream->seekp(0, std::ios::end);
        this->writeReg(size, tmp);
        this->freeRegOffset->updateOcupedOffset(0,size);
        this->ofstream->write(this->freeRegOffset->serialize(),512* sizeof(char));
        return;
    } else {
        int seekOff=this->freeRegOffset->nextFreeReg();
        this->ofstream->clear();
        this->ofstream->seekp(seekOff+1024);
        while (!this->ofstream->eof()){
            this->ifstream->clear();
            this->ifstream->seekg(seekOff+1024);
            int sfree;
            this->ifstream->read((char *) &sfree, sizeof(int));
            if(sfree>size){
                seekOff=this->freeRegOffset->nextFreeReg();
            }else{
                this->writeReg(size, tmp);
                this->freeRegOffset->deleteOcupedOffset(seekOff);
                this->ofstream->clear();
                this->ofstream->seekp(512);
                this->ofstream->write(this->freeRegOffset->serialize(),512* sizeof(char));
                return;
            }
            this->ofstream->clear();
            this->ofstream->seekp(seekOff+1024);
        }
        this->writeReg(size, tmp);
        this->freeRegOffset->updateOcupedOffset(seekOff,seekOff+size);
        this->ofstream->write(this->freeRegOffset->serialize(),512* sizeof(char));
        return;
    }
}

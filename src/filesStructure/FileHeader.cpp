//
// Created by coco on 11/09/16.
//

#include <sstream>
#include <vector>
#include <iostream>
#include <cstring>
#include "FileHeader.h"

FileHeader::FileHeader(std::string names,std::string types,std::string sizes,FileType type) {
    std::stringstream ss(names);
    std:: string reg;
    std::vector<std::string> nlist;
    while(std::getline(ss,reg,',')){
        nlist.push_back(reg);
    }
    this->name=nlist.data();

    std::stringstream ss1(sizes);
    std::vector<std::string> slist;
    while(std::getline(ss1,reg,',')){
        slist.push_back(reg);
    }
    //this->sizeField=slist.data();

    std::stringstream ss2(names);
    std::vector<std::string> tlist;
    while(std::getline(ss2,reg,',')){
        tlist.push_back(reg);
    }
    //this->tipe=tlist.data();
    this->fileType=type;

}

FileHeader::FileHeader(Args args) {
    this->lastId=0;
    this->numField=0;
    this->fileType=args.getOutType();
    this->blockSize=args.getBlockSize();


    //cargo los nombres de los registros
    std::stringstream ss(args.getModifiers());
    std::stringstream ss2(args.getModifiers2());
    std::string reg;
    std::vector<std::string> nlist;
    while(std::getline(ss,reg,',')){
        nlist.push_back(reg);
        //la cantidad
        this->numField++;
    }
    this->name= (std::string *) malloc(sizeof(std::string) * this->numField);
    for (int k = 0; k < this->numField; ++k) {
        this->name[k]=nlist[k];
    }

    this->type= (char *) malloc(sizeof(char) * this->numField);
    this->sizeField= (char *) malloc(sizeof(char) * this->numField);
    int j=0;
    while(std::getline(ss2,reg,',')){
        this->type[j]=reg.substr(0,1).c_str()[0];
        this->sizeField[j]=reg.substr(1).c_str()[0];
        j++;
    }
    std::cout<<"Registros:"<<std::endl;
    std::cout<<"Nombre,tipo,tamaño:"<<std::endl;
    for(int i=0;i<numField;i++){
        std::cout<<this->name[i]<<","<<this->type[i]<<","<<this->sizeField[i]<<std::endl;
    }

}

char* FileHeader::Serialize() {
    char * serial = (char *)malloc(512);// el header es fijo de 512 bytes
    char * out= serial;
    if(this->fileType==FileType::bloque) {
        memcpy(serial, &(this->fileType), sizeof(char));
        serial+=sizeof(char);
        memcpy(serial, &(this->blockSize), sizeof(int));
        serial+=sizeof(int);
    }else{
        memcpy(serial, &(this->fileType), sizeof(char));
        serial+=sizeof(char);
    }
    memcpy(serial, &(this->numField), sizeof(int));
    serial+=sizeof(int);
    for(int i=0;i<this->numField;i++){
        memcpy(serial,this->name[i].c_str(), sizeof(char)*this->name[i].length()+1);
        serial+=sizeof(char)*this->name[i].length()+1;
    }
    memcpy(serial,this->type, sizeof(char)*numField);
    serial+=sizeof(char)*numField;
    memcpy(serial,this->sizeField, sizeof(char)*numField);
    serial+=sizeof(char)*numField;
    memcpy(serial,&(this->lastId), sizeof(int));
    serial+=sizeof(int);
    int diff= 512-(serial-out);
    for(int i =0;i< diff;i++){
        serial[i]=0;
    }
    return out;
}

FileHeader::FileHeader(char * buff) {
    char temp[100];
    memcpy(&(this->fileType),buff, sizeof(char));
    buff+= sizeof(char);
    if(this->fileType==FileType::bloque){
        memcpy(&(this->blockSize), buff, sizeof(int));
        buff+=sizeof(int);
    }
    memcpy(&(this->numField),buff, sizeof(int));
    buff+=sizeof(int);
  //  memcpy(this->nullable,buff, sizeof(bool)*this->numField);
   // buff+=sizeof(bool)*numField;
    std::vector<std::string> vec;
    for(int i=0;i<this->numField;i++){
        int x=0;
        for(;*buff!='\0';buff++,x++){
            temp[x]=*buff;
        }
        buff++;
        vec.push_back(std::string(temp,x));
    }
    this->name= (std::string *) malloc(sizeof(std::string) * 2);
    for (int k = 0; k < this->numField; ++k) {
        this->name[k]=vec[k];
    }
    this->type = (char *)malloc(numField);
    for(int i=0;i<this->numField;i++,buff++){
        this->type[i]=*buff;
    }
    this->sizeField = (char *)malloc(numField);
    for(int i=0;i<this->numField;i++,buff++){
        this->sizeField[i]=*buff;
    }
    memcpy(&(this->lastId),buff, sizeof(int));
}

FileType FileHeader::getFileType() {
    return this->fileType;
}

int FileHeader::getBlockSize() {
    return this->blockSize;
}

int FileHeader::getLastId() {
    return this->lastId;
}

int FileHeader::getNumField() {
    return this->numField;
}

char *FileHeader::getType()  {
    return type;
}

void FileHeader::setType(char *type) {
    FileHeader::type = type;
}

std::string *FileHeader::getName()  {
    return name;
}

void FileHeader::setName(std::string *name) {
    FileHeader::name = name;
}

char *FileHeader::getSizeField()  {
    return sizeField;
}

void FileHeader::setSizeField(char *sizeField) {
    FileHeader::sizeField = sizeField;
}

void FileHeader::incLastId() {
    this->lastId++;
}

int FileHeader::getFielPossition(std::string fieldName) {
    for (int i = 0; i < this->numField; ++i) {
        if(!this->name[i].compare(fieldName)){
            return i;
        }
    }
}

FileHeader::FileHeader(FileHeader *fh) {
    this->blockSize=fh->blockSize;
    this->fileType=fh->fileType;
    this->lastId=0;//se setea en 0 para arrancar a copiar desde 0
    this->numField=fh->numField;
    this->name= (std::string *) malloc(sizeof(std::string) * this->numField);
    this->sizeField= (char *) malloc(sizeof(char) * this->numField);
    this->type= (char *) malloc(sizeof(char) * this->numField);
    for (int i = 0; i < this->numField; ++i) {
        this->name[i]=fh->name[i];
        this->sizeField[i]=fh->sizeField[i];
        this->type[i]= fh->type[i];
    }
}

void FileHeader::proyectFields(std::string fields) {
    std::stringstream ss(fields);
    std::string reg;
    std::vector<std::string> nlist;
    int newSize=0;
    while(std::getline(ss,reg,',')){
        nlist.push_back(reg);
        //la cantidad
        newSize++;
    }
    std::string * newName= (std::string *) malloc(sizeof(std::string) * newSize);
    std::string * newLenght= (std::string *) malloc(sizeof(std::string) * newSize);
    char * newTipe= (char *) malloc(sizeof(char) * newSize);

    for (int k = 0; k < newSize; ++k) {
        newName[k]=nlist[k];
        for (int i = 0; i < this->numField; ++i) {
            if(newName[k]==this->name[i]){
                newLenght[k]=this->sizeField[i];
                newTipe[k]=this->type[i];
            }
        }
    }
    this->name=newName;
    this->numField=newSize;
    this->type=newTipe;
    this->lastId=0;
}

void FileHeader::merge(FileHeader *pManager) {
    int newSize=this->numField+pManager->numField;
    std::string * newName= (std::string *) malloc(sizeof(std::string) * (newSize));
    char * newLenght= (char *) malloc(sizeof(char) * (newSize));
    char * newTipe= (char *) malloc(sizeof(char) * newSize);
    for (int i = 0; i < this->numField; ++i) {
        newName[i]=this->name[i];
        newLenght[i]=this->sizeField[i];
        newTipe[i]=this->type[i];
    }
    for (int i = 0; i < pManager->numField; ++i) {
        newName[i+this->numField]=pManager->name[i];
        newLenght[i+this->numField]=pManager->sizeField[i];
        newTipe[i+this->numField]=pManager->type[i];
    }
    this->name=newName;
    this->numField=newSize;
    this->type=newTipe;
    this->sizeField=newLenght;
    this->lastId=0;
}

std::string FileHeader::toCSV() {
    std::stringstream ss;
    ss<<"id,";
    for (int i = 0; i < this->numField; ++i) {
        ss<<this->name[i]<<'-'<<this->type[i]<<'|'<<this->sizeField[i]<<",";
    }
    std::string out=ss.str();
    return out.substr(0,out.size()-1);
}

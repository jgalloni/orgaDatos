//
// Created by coco on 11/09/16.
//

#include <sstream>
#include <vector>
#include <iostream>
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
    this->numField=0;
    this->fileType=args.getOutType();

    //cargo los nombres de los registros
    std::stringstream ss(args.getModifiers());
    std::stringstream ss2(args.getModifiers2());
    std::string reg;
    std::vector<std::string> nlist;
    std::vector< char> tlist;
    std::vector<std::string> slist;
    while(std::getline(ss,reg,',')){
        nlist.push_back(reg);
        //la cantidad
        this->numField++;
    }
    this->name=nlist.data();

    while(std::getline(ss2,reg,',')){
        tlist.push_back(reg.substr(0,1).c_str()[0]);
        slist.push_back(reg.substr(1));
    }
    this->type=tlist.data();
    this->sizeField=slist.data();
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
   // memcpy(serial, this->nullable, sizeof(bool)*this->numField);
  //  serial+=sizeof(bool)*numField;
    for(int i=0;i<this->numField;i++){
        memcpy(serial,this->name[i].c_str(), sizeof(char)*this->name[i].length()+1);
        serial+=sizeof(char)*this->name[i].length()+1;
    }
    memcpy(serial,this->type, sizeof(char)*numField);
    serial+=sizeof(char)*numField;
    for(int i=0;i<this->numField;i++){
        memcpy(serial,this->sizeField[i].c_str(), sizeof(char)*this->sizeField[i].length()+1);
        serial+=sizeof(char)*this->sizeField[i].length()+1;
    }
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
    this->name=vec.data();
    this->type = (char *)malloc(numField);
    for(int i=0;i<this->numField;i++,buff++){
        this->type[i]=*buff;
    }
    std::vector<std::string> vec2;
    for(int i=0;i<this->numField;i++){
        int x=0;
        for(;*buff!='\0';buff++,x++){
            temp[x]=*buff;
        }
        buff++;
        vec2.push_back(std::string(temp,x));
    }
    this->sizeField= vec2.data();
}
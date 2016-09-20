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
    this->fileType=args.getOutType();

    //cargo los nombres de los registros
    std::stringstream ss(args.getModifiers());
    std::stringstream ss2(args.getModifiers2());
    std::string reg;
    std::vector<std::string> nlist;
    std::vector<std::string> tlist;
    std::vector<std::string> slist;
    while(std::getline(ss,reg,',')){
        nlist.push_back(reg);
        //la cantidad
        this->numField++;
    }
    this->name=nlist.data();

    while(std::getline(ss2,reg,',')){
        tlist.push_back(reg.substr(0,1));
        slist.push_back(reg.substr(1,1));
    }
    this->type=tlist.data();
    this->sizeField=slist.data();
    std::cout<<"Registros:"<<std::endl;
    std::cout<<"Nombre,tipo,tamaño:"<<std::endl;
    for(int i=0;i<numField;i++){
        std::cout<<this->name[i]<<","<<this->type[i]<<","<<this->sizeField[i]<<std::endl;
    }
}

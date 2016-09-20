//
// Created by coco on 11/09/16.
//

#include <sstream>
#include <vector>
#include "FileHeader.h"

FileHeader::FileHeader(std::string names,std::string types,std::string sizes) {
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


}

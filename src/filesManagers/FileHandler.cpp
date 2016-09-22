//
// Created by Jorge Galloni on 9/21/16.
//

#include <ios>
#include <fstream>
#include <iostream>
#include "FileHandler.h"

FileHandler::FileHandler(std::string fileName) {
    this->fileName=fileName;
    this->ifstream=new std::ifstream(this->fileName,std::ios::binary);
    char temp[512];
    ifstream->read(temp,512);
    this->fileHeader = new FileHeader(temp);
}


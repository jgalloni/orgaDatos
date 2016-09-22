//
// Created by coco on 11/09/16.
//

#ifndef ORGADATOS_FILEHEADER_H
#define ORGADATOS_FILEHEADER_H

#include <string>
#include "../argHandler/Args.h"

class FileHeader {
private:
    char *type;//s u
    std::string *name;//s u
    bool *nullable; //s u
    std::string *sizeField;//s
    int numField; //s u
    FileType fileType; //s u
    int blockSize; //s u
public:
    FileHeader(std::string names,std::string types,std::string size,FileType type);
    FileHeader(Args args);
    FileHeader(char *);
    char * Serialize();
};


#endif //ORGADATOS_FILEHEADER_H

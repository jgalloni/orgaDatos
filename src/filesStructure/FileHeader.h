//
// Created by coco on 11/09/16.
//

#ifndef ORGADATOS_FILEHEADER_H
#define ORGADATOS_FILEHEADER_H

#include <string>
#include "../argHandler/Args.h"

class FileHeader {
private:
    std::string *type;
    std::string *name;
    bool *nullable;
    std::string *sizeField;
    int numField;
    FileType fileType;
    int blockSize;
public:
    FileHeader(std::string names,std::string types,std::string size,FileType type);
    FileHeader(Args args);
};


#endif //ORGADATOS_FILEHEADER_H

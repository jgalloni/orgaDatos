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
    char *sizeField;//s
    int numField; //s u
    FileType fileType; //s u
    int blockSize; //s u
    int lastId;
public:
    char *getType();

    void setType(char *type);

    std::string *getName() ;

    void setName(std::string *name);

    char*getSizeField() ;

    void setSizeField(char *sizeField);

public:
    FileHeader(std::string names,std::string types,std::string size,FileType type);
    FileHeader(Args args);
    FileHeader(char *);
    char * Serialize();
    FileType getFileType();
    int getBlockSize();

    int getLastId();
    int getNumField();

    void incLastId();
};


#endif //ORGADATOS_FILEHEADER_H

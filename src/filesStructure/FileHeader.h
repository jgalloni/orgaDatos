//
// Created by coco on 11/09/16.
//

#ifndef ORGADATOS_FILEHEADER_H

#include <string>
#define ORGADATOS_FILEHEADER_H


class FileHeader {
private:
    char tipe[];
    std::string name[];
    bool nullable[];
    int sizeField[];
    int numField;
public:
    FileHeader(std::string names,std::string types,std::string size;
};


#endif //ORGADATOS_FILEHEADER_H

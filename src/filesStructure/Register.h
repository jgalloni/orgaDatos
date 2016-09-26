//
// Created by Jorge Galloni on 9/22/16.
//

#ifndef ORGADATOS_REGISTER_H
#define ORGADATOS_REGISTER_H


#include <string>
#include "Field/Field.h"
#include "FileHeader.h"

class Register {
private:
    Field ** fields ;
    int fieldsNumber;
    int id;
public:
    Register(std::string * fields,char * type,char *sizeField,int numFields);
    char * serialize(int *size);

    Register(std::string rawReg, FileHeader *fHeader);
    Register(Field **, int size,int id);

    bool cmp(std::string rawReg);

    bool test(int fieldNum,std::string condition, std::string value);
};


#endif //ORGADATOS_REGISTER_H

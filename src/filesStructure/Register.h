//
// Created by Jorge Galloni on 9/22/16.
//

#ifndef ORGADATOS_REGISTER_H
#define ORGADATOS_REGISTER_H


#include <string>
#include "Field/Field.h"

class Register {
private:
    Field ** fields ;
    int fieldsNumber;
public:
    Register(std::string * fields,char * type,std::string *sizeField,int numFields);
    char * serialize(int *size);
};


#endif //ORGADATOS_REGISTER_H

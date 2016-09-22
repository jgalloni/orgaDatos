//
// Created by Jorge Galloni on 9/22/16.
//

#include <cstdlib>
#include "Register.h"
#include "Field/FieldFactory.h"

Register::Register(std::string *fieldsValue, char *type, std::string *sizeField, int numFields) {
    this->fieldsNumber=numFields;
    this->fields= (Field * *) malloc(sizeof(Field *) * numFields);
    for(int i=0;i<numFields;i++){
        fields[i]= FieldFactory::createField(type[i],sizeField[i],fieldsValue[i]);
    }

}

char *Register::serialize(int *size) {
    char * tmp = (char *) malloc(sizeof(char) * 512);
    char * out = tmp;
    for(int i = 0;i<this->fieldsNumber;i++){
        int tsize=0;
        memcpy(tmp,this->fields[i]->serialize(&tsize),tsize);
        *size+=tsize;
        tmp+=tsize;
    }
    return out;
}

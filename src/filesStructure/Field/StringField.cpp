//
// Created by Jorge Galloni on 9/22/16.
//

#include <cstdlib>
#include "StringField.h"

StringField::StringField(std::string value, char type) {
    this->value=value;
    this->type=type;
}

char *StringField::serialize(int * size) const {
    const char * temp = value.c_str();
    * size = value.length()*sizeof(char);
    if(!type.compare("D")){
        char * out = (char *) malloc(sizeof(char) * value.length()+1);
        memcpy(out,temp,value.length()+1);
        return out;
    }
    else{
        char * out = (char *) malloc((sizeof(char) * value.length()+1)+sizeof(int));
        memcpy(out,size,sizeof(int));
        memcpy(out+sizeof(int),temp,value.length());
        *size+=sizeof(int);
        return out;
    }
}

bool StringField::cmp(std::string value) const {
    return this->value==value;
}

bool StringField::test(std::string condition, std::string value) const {
    if(condition=="igual")
        return this->cmp(value);
    if(condition=="distinto")
        return !(this-cmp(value));
    return false;
}

bool StringField::grt(std::string) const {
    return true;
}

bool StringField::lower(std::string) const {
    return true;
}

bool StringField::grtOrEqu(std::string) const {
    return true;
}

bool StringField::loweOrEqu(std::string) const {
    return true;
}

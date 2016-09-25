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

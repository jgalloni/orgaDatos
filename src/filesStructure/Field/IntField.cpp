//
// Created by Jorge Galloni on 9/22/16.
//

#include <cstdlib>
#include "IntField.h"

IntField::IntField(std::string value, int size) {
    this->size=size;
    if(size==1){
        this->value1=atoi(value.c_str());
    } else if(size==2){
        this->value2=std::stoi(value);
    }else if(size==4){
        this->value4=std::stoi(value);
    }else if(size==8){
        this->value8=std::stol(value);
    }
}

char * IntField::serialize(int *size) const{
    char * out = (char *) malloc(this->size);
    if(this->size==1){
        memcpy(out,&value1, sizeof(char));
        *size=sizeof(char);
    } else if(this->size==2){
        memcpy(out,&value2, sizeof(short));
        *size=sizeof(short);
    }else if(this->size==4){
        memcpy(out,&value4, sizeof(int));
        *size=sizeof(int);
    }else if(this->size==8){
        memcpy(out,&value8, sizeof(long));
        *size=sizeof(long);
    }
    return out;

}

IntField::IntField(char value, int size) {
    this->size=size;
    this->value1=value;
}

IntField::IntField(short value, int size) {
    this->size=size;
    this->value2=value;
}

IntField::IntField(int value, int size) {
    this->size=size;
    this->value4=value;
}

IntField::IntField(long value, int size) {
    this->size=size;
    this->value8=value;
}

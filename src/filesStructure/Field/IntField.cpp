//
// Created by Jorge Galloni on 9/22/16.
//

#include <cstdlib>
#include <cstring>
#include <sstream>
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

bool IntField::cmp(std::string value) const {
    if(this->size==1){
        if(this->value1==std::stoi(value)) return true;
    } else if(this->size==2){
        if(this->value2==std::stoi(value)) return true;
    }else if(this->size==4){
        if(this->value4==std::stoi(value)) return true;
    }else if(this->size==8){
        if(this->value8==std::stol(value)) return true;
    }
    return false;
}

bool IntField::test(std::string condition, std::string value) const {
    if(condition=="igual")
        return this->cmp(value);
    if(condition=="distinto")
        return !(this-cmp(value));
    if(condition=="mayor")
        return this->grt(value);
    if(condition=="menor")
        return this->lower(value);
    if(condition=="mayorOIgual")
        return this->grtOrEqu(value);
    if(condition=="menorOIgual")
        return this->loweOrEqu(value);
}

bool IntField::grt( std::string value) const{
    if (this->size == 1) {
        return this->value1 > std::stoi(value);
    } else if (this->size == 2) {
        return this->value2 > std::stoi(value);
    } else if (this->size == 4) {
        return this->value4 > std::stoi(value);
    } else if (this->size == 8) {
        return this->value8 > std::stoi(value);
    }
    return false;
}

bool IntField::lower( std::string value) const{
    if (this->size == 1) {
        return this->value1 < std::stoi(value);
    } else if (this->size == 2) {
        return this->value2 < std::stoi(value);
    } else if (this->size == 4) {
        return this->value4 < std::stoi(value);
    } else if (this->size == 8) {
        return this->value8 < std::stoi(value);
    }
    return false;
}

bool IntField::grtOrEqu( std::string value) const{
    if (this->size == 1) {
        return this->value1 >= std::stoi(value);
    } else if (this->size == 2) {
        return this->value2 >= std::stoi(value);
    } else if (this->size == 4) {
        return this->value4 >= std::stoi(value);
    } else if (this->size == 8) {
        return this->value8 >= std::stoi(value);
    }
    return false;
}

bool IntField::loweOrEqu( std::string value) const{
    if (this->size == 1) {
        return this->value1 <= std::stoi(value);
    } else if (this->size == 2) {
        return this->value2 <= std::stoi(value);
    } else if (this->size == 4) {
        return this->value4 <= std::stoi(value);
    } else if (this->size == 8) {
        return this->value8 <= std::stoi(value);
    }
    return false;
}

std::string IntField::toString() {
    std::stringstream ss;
    if (this->size == 1) {
        int i=this->value1;
        ss << i;
        return ss.str();
    } else if (this->size == 2) {
        ss << this->value2;
        return ss.str();
    } else if (this->size == 4) {
        ss << this->value4;
        return ss.str();
    } else if (this->size == 8) {
        ss << this->value8;
        return ss.str();
    }
}

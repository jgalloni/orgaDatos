//
// Created by Jorge Galloni on 9/22/16.
//

#include <cstdlib>
#include <sstream>
#include <vector>
#include <cstring>
#include "Register.h"
#include "Field/FieldFactory.h"

Register::Register(std::string *fieldsValue, char *type, char *sizeField, int numFields) {
    this->fieldsNumber=numFields;
    this->fields= (Field * *) malloc(sizeof(Field *) * numFields);
    for(int i=0;i<numFields;i++){
        fields[i]= FieldFactory::createField(type[i],sizeField[i],fieldsValue[i]);
    }

}

char *Register::serialize(int *size) {
    char * tmp = (char *) malloc(sizeof(char) * 512);
    char * out = tmp;
    memcpy(tmp,&(this->id), sizeof(int));
    tmp+= sizeof(int);
    *size+=sizeof(int);
    for(int i = 0;i<this->fieldsNumber;i++){
        int tsize=0;
        char * regS=this->fields[i]->serialize(&tsize);
        memcpy(tmp,regS,tsize);
        *size+=tsize;
        tmp+=tsize;
    }
    return out;
}

Register::Register(std::string rawReg, FileHeader *fHeader) {
    this->fieldsNumber=fHeader->getNumField();
    this->fields= (Field * *) malloc(sizeof(Field *) * fieldsNumber);
    std::string *fieldsValue;
    std::string val;
    std::stringstream ss(rawReg);
    std::vector<std::string> list;
    while(std::getline(ss,val,',')){
        list.push_back(val);
    }
    fieldsValue=list.data();
    for(int i=0;i<fieldsNumber;i++){
        fields[i]= FieldFactory::createField(fHeader->getType()[i],fHeader->getSizeField()[i],fieldsValue[i]);
    }
    this->id=fHeader->getLastId();
}

Register::Register(Field ** f, int size, int id) {
    this->fields=f;
    this->fieldsNumber=size;
    this->id=id;

}

bool Register::cmp(std::string rawReg) {
    std::string val;
    std::stringstream ss(rawReg);
    std::vector<std::string> list;
    while(std::getline(ss,val,',')){
        list.push_back(val);
    }
    for (int i = 0; i < this->fieldsNumber; ++i) {
        if(!this->fields[i]->cmp(list.at(i))){
            return false;
        }
    }
    return true;
}

bool Register::test(int fieldNum,std::string condition, std::string value) {
    return this->fields[fieldNum]->test(condition,value);
}


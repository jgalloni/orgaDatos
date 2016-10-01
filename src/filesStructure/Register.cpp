//
// Created by Jorge Galloni on 9/22/16.
//

#include <cstdlib>
#include <sstream>
#include <vector>
#include <cstring>
#include <set>
#include "Register.h"
#include "Field/FieldFactory.h"
#include "Field/IntField.h"
#include "Field/DateField.h"
#include "Field/StringField.h"

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
    *size+=sizeof(int);
    tmp+=sizeof(int);
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

Register::Register(char *sReg, int size, FileHeader *fHeader) {
    memcpy(&(this->id), sReg, sizeof(int));
    sReg+=sizeof(int);
    std::vector<Field *> tmpFields;
    for(int j=0;j<fHeader->getNumField();j++){
        Field *field= (Field *) malloc(sizeof(Field*));
        switch (fHeader->getType()[j]){
            case 'i':
                if(fHeader->getSizeField()[j]=='1'){
                    char val;
                    memcpy(&val,sReg,sizeof(char));
                    IntField *fl= new IntField(val,1);
                    tmpFields.push_back(fl);
                    sReg+=sizeof(char);
                } else if (fHeader->getSizeField()[j]=='2'){
                    short val;
                    memcpy(&val,sReg,sizeof(short));
                    IntField *fl= new IntField(val,2);
                    tmpFields.push_back(fl);
                    sReg+=sizeof(short);
                } else if (fHeader->getSizeField()[j]=='4'){
                    int val;
                    memcpy(&val,sReg,sizeof(int));
                    IntField *fl= new IntField(val,4);
                    tmpFields.push_back(fl);
                    sReg+=sizeof(int);
                } else if (fHeader->getSizeField()[j]=='8'){
                    long val;
                    memcpy(&val,sReg,sizeof(long));
                    IntField *fl= new IntField(val,8);
                    tmpFields.push_back(fl);
                    sReg+=sizeof(long);
                }
                break;
            case 'd':
                if(fHeader->getSizeField()[j]=='t'){
                    char val[8];
                    memcpy(&val,sReg,sizeof(char)*15);
                    DateField *fl= new DateField(std::string(val,15),'t');
                    tmpFields.push_back(fl);
                    sReg+=sizeof(char)*15;
                }else {
                    char val[8];
                    memcpy(&val,sReg,sizeof(char)*8);
                    DateField *fl= new DateField(std::string(val,8),' ');
                    tmpFields.push_back(fl);
                    sReg+=sizeof(char)*15;
                }
                break;
            case 's':
                if(fHeader->getSizeField()[j]=='d'){
                    std::string tmp;
                    while(*sReg!='\0'){
                        tmp+=*sReg;
                        sReg++;
                    }
                    StringField *fl = new StringField(tmp,'d');
                    tmpFields.push_back(fl);
                }else{
                    int size;
                    memcpy(&size,sReg, sizeof(int));
                    sReg+=sizeof(int);
                    std::string tmp;
                    for(int lg=0;lg<size;lg++){
                        tmp+=*sReg;
                        sReg++;
                    }
                    StringField *fl = new StringField(tmp,' ');
                    tmpFields.push_back(fl);
                }
        }
    }
    this->fields= (Field * *) malloc(sizeof(Field*));
    fields[0]= (Field *) malloc(sizeof(Field)*tmpFields.size());
    for (int i = 0; i < tmpFields.size(); ++i) {
        fields[i]=tmpFields[i];
    }
    this->fieldsNumber=fHeader->getNumField();
}

void Register::proyect(int *fields,int size) {
    Field **tmpField= (Field * *) malloc(sizeof(Field*));
    tmpField[0]= (Field *) malloc(sizeof(Field)*size);
    for (int i = 0; i < size; i++) {
        tmpField[i]=this->fields[fields[i]];
    }
    this->fields=tmpField;
    this->fieldsNumber=size;
}

Register *Register::join(Register r,int id) {
    int newsize=(this->fieldsNumber+r.fieldsNumber);
    Field **tmpField= (Field * *) malloc(sizeof(Field*));
    tmpField[0]= (Field *) malloc(sizeof(Field)*newsize);
    for (int i = 0; i < this->fieldsNumber; i++) {
        tmpField[i]=this->fields[i];
    }
    for (int i = 0; i < r.fieldsNumber; i++) {
        tmpField[i+this->fieldsNumber]=r.fields[i];
    }
    return new Register(tmpField,newsize,id);
}

void Register::setId(int id) {
    this->id=id;
}

std::string Register::toCSV() {
    std::stringstream ss;
    std::string out="";
    ss<<this->id;
    ss<<',';
    for (int i = 0; i < this->fieldsNumber; i++) {
        ss<<this->fields[i]->toString();
        ss<<',';
    }
    out=ss.str();
    return out.substr(0,out.size()-1);
}





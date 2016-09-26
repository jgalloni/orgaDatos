//
// Created by Jorge Galloni on 9/24/16.
//

#include <vector>
#include <cstdlib>
#include "Block.h"
#include "Field/IntField.h"
#include "Field/DateField.h"
#include "Field/StringField.h"

char *Block::serialize(int size) {
    char *temp = (char *) malloc(size * sizeof(char)*512);
    char * out=temp;
    int total=0;
    temp+=sizeof(int);
    for(int i=0;i<this->regsNum;i++){
        int regSize=0;
        char * sReg = regs->serialize(&regSize);
        total+=regSize;
        if(total>(size*512)){
            return nullptr;
        }
        memcpy(temp,sReg,regSize*sizeof(char));
        temp+=regSize*sizeof(char);
    }
    int cero=0;
    for(int i=0;i<(size*512)-(total-sizeof(int));i++){
        memcpy(temp,&cero,sizeof(char));
    }
    memcpy(out,&total,sizeof(int));
    this->ocupation=total;
    return out;
}

Block::Block(Register *regs, int size) {
    this->regs= regs;
    this->regsNum=size;
}

Block::Block(char *sReg, FileHeader fh) {
    int oc;
    memcpy(&oc,sReg, sizeof(int));
    sReg+=sizeof(int);
    this->ocupation=oc;
    std::vector<Register> tmpreg;
    for(int i=sizeof(int);i<oc;){
        std::vector<Field *> tmpFields;
        int id;
        memcpy(&id,sReg, sizeof(int));
        sReg+=sizeof(int);
        for(int j=0;j<fh.getNumField();j++){
            switch (fh.getType()[j]){
                case 'i':
                    if(fh.getSizeField()[j]=='1'){
                        char val;
                        memcpy(&val,sReg,sizeof(char));
                        IntField *fl= new IntField(val,1);
                        tmpFields.push_back(fl);
                        sReg+=sizeof(char);
                        i+=sizeof(char);
                    } else if (fh.getSizeField()[j]=='2'){
                        short val;
                        memcpy(&val,sReg,sizeof(short));
                        IntField *fl= new IntField(val,2);
                        tmpFields.push_back(fl);
                        sReg+=sizeof(short);
                        i+=sizeof(short);
                    } else if (fh.getSizeField()[j]=='4'){
                        int val;
                        memcpy(&val,sReg,sizeof(int));
                        IntField *fl= new IntField(val,4);
                        tmpFields.push_back(fl);
                        sReg+=sizeof(int);
                        i+=sizeof(int);
                    } else if (fh.getSizeField()[j]=='8'){
                        long val;
                        memcpy(&val,sReg,sizeof(long));
                        IntField *fl= new IntField(val,8);
                        tmpFields.push_back(fl);
                        sReg+=sizeof(long);
                        i+=sizeof(long);
                    }
                case 'd':
                    if(fh.getSizeField()[j]=='t'){
                        char val[8];
                        memcpy(&val,sReg,sizeof(char)*15);
                        DateField *fl= new DateField(std::string(val,15),'t');
                        tmpFields.push_back(fl);
                        sReg+=sizeof(char)*15;
                        i+=sizeof(char)*15;
                    }else {
                        char val[8];
                        memcpy(&val,sReg,sizeof(char)*8);
                        DateField *fl= new DateField(std::string(val,8),' ');
                        tmpFields.push_back(fl);
                        sReg+=sizeof(char)*15;
                        i+=sizeof(char)*15;
                    }
                case 's':
                    if(fh.getSizeField()[j]=='d'){
                        std::string tmp;
                        while(*sReg!='\0'){
                            tmp+=*sReg;
                            sReg++;
                            i++;
                        }
                        StringField *fl = new StringField(tmp,'d');
                        tmpFields.push_back(fl);
                    }else{
                        int size;
                        memcpy(&size,sReg, sizeof(int));
                        sReg+=sizeof(int);
                        i+=sizeof(int);
                        std::string tmp;
                        for(int lg=0;lg<size;lg++){
                            tmp+=*sReg;
                            sReg++;
                            i++;
                        }
                        StringField *fl = new StringField(tmp,' ');
                        tmpFields.push_back(fl);
                    }
            }
        }
        tmpreg.push_back(Register(tmpFields.data(),tmpFields.size(),id));
    }
}

int Block::getSerializedSize() {
    return this->ocupation;
}

bool Block::find(std::string rawReg) {
    return false;
}

void Block::remove(int id) {

}

void Block::add(Register aRegister) {
    Register * tmp= (Register *) malloc(sizeof(Register)*this->regsNum + 1);
    for (int i = 0; i < this->regsNum; ++i) {
        tmp[i]=regs[i];
    }
    tmp[this->regsNum]=aRegister;
    free(this->regs);
    this->regs=tmp;
    this->regsNum++;
}


std::vector<Register> Block::find(int field, std::string condition, std::string value) {
    std::vector<Register> ret;
    for (int i = 0; i < this->regsNum; ++i) {
       if(this->regs[i].test(field,condition,value)){
           ret.push_back(this->regs[i]);
       }
    }
    return ret;
}

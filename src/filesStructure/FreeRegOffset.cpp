//
// Created by Jorge Galloni on 9/25/16.
//

#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <iostream>
#include "FreeRegOffset.h"

int FreeRegOffset::nextFreeReg() {
    this->currentFree++;
    if(this->currentFree>this->size){
        this->currentFree=0;
    }
    return this->freeRegs[0];
}

FreeRegOffset::FreeRegOffset() {
    this->currentFree=-1;
    this->size=1;
    this->freeRegs= (int *) malloc(sizeof(int));
    this->freeRegs[0]=0;
}

char *FreeRegOffset::serialize() {
    char *out = (char *) malloc(512 * sizeof(char));
    memcpy(out,&(this->size),sizeof(int));
    memcpy(out+sizeof(int),this->freeRegs,sizeof(int)*this->size);
    return out;
}

FreeRegOffset::FreeRegOffset(char *data) {
    memcpy(&this->size,data, sizeof(int));
    data+=sizeof(int);
    this->freeRegs= (int *) malloc(this->size * sizeof(int));
    memcpy(this->freeRegs,data,this->size * sizeof(int));
    this->currentFree=-1;
}

void FreeRegOffset::setOcupedOffset(int offset) {
    int *tmp = (int *) malloc((size + 1) * sizeof(int));
    memcpy(tmp, freeRegs, size*sizeof(int));
    this->freeRegs = tmp;
    this->freeRegs[size] = offset;
    this->size++;
    std::sort(this->freeRegs,this->freeRegs+this->size);
    std::cout<<"primer region libre: "<<this->freeRegs[0]<<std::endl;
}

void FreeRegOffset::updateOcupedOffset(int oldOff, int newOff) {
    for(int i=0;i<size;i++){
        if (this->freeRegs[i]==oldOff){
            this->freeRegs[i]=newOff;
            return;
        }
    }
    std::sort(this->freeRegs,this->freeRegs+this->size);
}

void FreeRegOffset::deleteOcupedOffset(int offset) {
    int *tmp = (int *) malloc((size - 1) * sizeof(int));
    for(int i=0,j=0;i<size;i++){
        if (this->freeRegs[i]!=offset){
            tmp[j]=this->freeRegs[i];
            j++;
        }
    }
    this->freeRegs=tmp;
    size--;
    std::sort(this->freeRegs,this->freeRegs+this->size);
}

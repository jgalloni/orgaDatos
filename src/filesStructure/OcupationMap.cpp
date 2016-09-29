//
// Created by Jorge Galloni on 9/24/16.
//

#include <cstdlib>
#include <exception>
#include "OcupationMap.h"

OcupationMap::OcupationMap(char *value, int size) {
    this->size=size;
    this->map= (bool *) malloc(sizeof(bool) * 8 * size);
    for(int i=0;i<size;i++){
        for (int j = 0; j < 8; ++j) {
            this->map[i+j]=((*value & 1)==1);
            *value=(*value)/2;
        }
        value++;
    }
    this->currentFree=-1;
}

int OcupationMap::getNextFree() {
    for (int i = this->currentFree+1; i < this->size*8; ++i) {
        if(map[i]==false){
            this->currentFree=i;
            return this->currentFree;
        }
    }
    throw std::exception();
}

char *OcupationMap::serialize() {
    char * out= (char *) malloc(sizeof(char) * this->size);
    for (int i = 0; i < this->size; i+=8) {
        char c = 0;
        for (int j=0; j < 8; ++j) {
            if (this->map[i + j]) {
                c |= 1 << j;
            }
        }
        out[i]=c;
    }
    return out;
}

OcupationMap::OcupationMap(int size) {
    this->size=size;
    this->map= (bool *) malloc(sizeof(bool) * 8 * size);
    for(int i=0;i<size;i++){
        for (int j = 0; j < 8; ++j) {
            this->map[i+j]=false;
        }
    }
    this->currentFree=-1;
}

void OcupationMap::setFullBlock(int i) {
    this->map[i]= true;

}

void OcupationMap::setNotFull(int blockNro) {
    this->map[blockNro]= false;

}



//
// Created by Jorge Galloni on 9/24/16.
//

#ifndef ORGADATOS_BLOCK_H
#define ORGADATOS_BLOCK_H


#include "Register.h"

class Block {
private:
    Register *regs;
    int regsNum;
    int ocupation=0;
public:
    Block(Register *sReg, int size);
    Block(char *sReg, FileHeader size);
    char *serialize(int size);

    int getSerializedSize();
};


#endif //ORGADATOS_BLOCK_H

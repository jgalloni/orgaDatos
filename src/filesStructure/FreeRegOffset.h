//
// Created by Jorge Galloni on 9/25/16.
//

#ifndef ORGADATOS_FREEREGOFFSET_H
#define ORGADATOS_FREEREGOFFSET_H


class FreeRegOffset {
private:
    int * freeRegs;
    int size;
    int currentFree;
public:
    FreeRegOffset();
    char* serialize();
    int nextFreeReg();

    FreeRegOffset(char *data);

    void setOcupedOffset(int offset);

    void updateOcupedOffset(int oldOff, int newOff);

    void deleteOcupedOffset(int offset);
};


#endif //ORGADATOS_FREEREGOFFSET_H

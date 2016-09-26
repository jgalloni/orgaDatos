//
// Created by Jorge Galloni on 9/24/16.
//

#ifndef ORGADATOS_OCUPATIONMAP_H
#define ORGADATOS_OCUPATIONMAP_H


class OcupationMap {
private:
    bool *map;
    int size;
    int currentFree=0;

public:
    OcupationMap(int size);
    OcupationMap(char *value, int size);
    int getNextFree();
    char *serialize();

    void setFullBlock(int i);

    void setNotFull(int blockNro);
};


#endif //ORGADATOS_OCUPATIONMAP_H

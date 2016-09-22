//
// Created by Jorge Galloni on 9/22/16.
//

#ifndef ORGADATOS_INTFIELD_H
#define ORGADATOS_INTFIELD_H


#include <string>
#include "Field.h"

class IntField: public Field {
private:
    char value1;
    short value2;
    int value4;
    long value8;
    int size;
public:
    IntField(std::string value, int size);
    char * serialize(int * size) const;
};


#endif //ORGADATOS_INTFIELD_H

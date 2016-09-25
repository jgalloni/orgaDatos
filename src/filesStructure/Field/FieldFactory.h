//
// Created by Jorge Galloni on 9/22/16.
//

#ifndef ORGADATOS_FIELDFACTORY_H
#define ORGADATOS_FIELDFACTORY_H


#include <string>
#include "Field.h"

class FieldFactory {
public:
    static Field * createField(char type, char sizeField,std::string fieldsValue);
};


#endif //ORGADATOS_FIELDFACTORY_H

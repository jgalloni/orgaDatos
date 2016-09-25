//
// Created by Jorge Galloni on 9/22/16.
//

#ifndef ORGADATOS_DATEFIELD_H
#define ORGADATOS_DATEFIELD_H


#include <string>
#include "Field.h"

class DateField : public Field {

private:
    const char *dia,*mes,*anio,*horas,*minutos,*segundos;
    char type;

public:
    DateField(std::string value, char type);
    char * serialize(int * size) const;
};


#endif //ORGADATOS_DATEFIELD_H

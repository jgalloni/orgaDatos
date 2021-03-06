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
    bool cmp(std::string value) const;
    bool test(std::string condition,std::string value) const;
    bool grt(std::string) const;
    bool lower (std::string) const;
    bool grtOrEqu(std::string) const;
    bool loweOrEqu(std::string) const;
    std::string toString();
};


#endif //ORGADATOS_DATEFIELD_H

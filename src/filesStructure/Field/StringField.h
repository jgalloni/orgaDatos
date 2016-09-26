//
// Created by Jorge Galloni on 9/22/16.
//

#ifndef ORGADATOS_STRINGFIELD_H
#define ORGADATOS_STRINGFIELD_H


#include <string>
#include "Field.h"

class StringField: public Field {
private:
    std::string value;
    std::string type;

public:
    StringField(std::string value, char type);
    char * serialize(int * size) const;
    bool cmp(std::string value) const;
    bool test(std::string condition,std::string value) const;
    bool grt(std::string) const;
    bool lower (std::string) const;
    bool grtOrEqu(std::string) const;
    bool loweOrEqu(std::string) const;
};


#endif //ORGADATOS_STRINGFIELD_H

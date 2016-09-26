//
// Created by Jorge Galloni on 9/22/16.
//

#ifndef ORGADATOS_FIELD_H
#define ORGADATOS_FIELD_H


#include <string>

class Field {
public:
    virtual char * serialize(int * size) const = 0;

    virtual bool cmp(std::string value) const=0;
    virtual bool test(std::string condition,std::string value) const=0;
    virtual bool grt(std::string) const=0;
    virtual bool lower (std::string) const=0;
    virtual bool grtOrEqu(std::string) const=0;
    virtual bool loweOrEqu(std::string) const=0;
};


#endif //ORGADATOS_FIELD_H

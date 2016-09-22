//
// Created by Jorge Galloni on 9/22/16.
//

#ifndef ORGADATOS_FIELD_H
#define ORGADATOS_FIELD_H


class Field {
public:
    virtual char * serialize(int * size) const = 0;
};


#endif //ORGADATOS_FIELD_H

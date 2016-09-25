//
// Created by Jorge Galloni on 9/22/16.
//

#include <cstdlib>
#include "DateField.h"

DateField::DateField(std::string value, char type) {
    this->type=type;
    this->anio=value.substr(0,4).c_str();
    this->mes=value.substr(4,2).c_str();
    this->dia=value.substr(6,2).c_str();
    if(type == 't'){
        this->horas=value.substr(9,2).c_str();
        this->minutos=value.substr(11,2).c_str();
        this->segundos=value.substr(13,2).c_str();
    }
}

char * DateField::serialize(int * size) const {
    char * data;
    if(type == 't'){
        data = (char *) malloc(sizeof(char) * 15);
        char * out=data;
        memcpy(data,anio,4);
        data+=4;
        memcpy(data,mes,2);
        data+=2;
        memcpy(data,dia,2);
        data+=2;

        *data = '-';
        data++;

        memcpy(data,horas,2);
        data+=2;
        memcpy(data,minutos,2);
        data+=2;
        memcpy(data,segundos,2);
        *size= 15;
        return out;

    }else{
        data = (char *) malloc(sizeof(char) * 8);
        char * out=data;
        memcpy(data,anio,4);
        data+=4;
        memcpy(data,mes,2);
        data+=2;
        memcpy(data,dia,2);
        *size= 8;
        return out;
    }
}

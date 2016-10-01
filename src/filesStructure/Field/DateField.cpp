//
// Created by Jorge Galloni on 9/22/16.
//

#include <cstdlib>
#include <sstream>
#include <cstring>
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

bool DateField::cmp(std::string value) const {
    if(value.substr(0,4)!=this->anio){
        return false;
    }
    if(value.substr(4,2)!=this->mes){
        return false;
    }
    if(value.substr(6,2)!=this->dia){
        return false;
    }
    if(this->type=='t'){
        return true;
    }
    if(value.substr(9,2)!=this->horas){
        return false;
    }
    if(value.substr(11,2)!=this->minutos){
        return false;
    }
    if(value.substr(13,2)!=this->segundos){
        return false;
    }
    return true;
}


bool DateField::test(std::string condition, std::string value) const {
    if(condition=="igual")
        return this->cmp(value);
    if(condition=="distinto")
        return !this-cmp(value);
    if(condition=="mayor")
        return this->grt(value);
    if(condition=="menor")
        return this->lower(value);
    if(condition=="mayorOIgual")
        return this->grtOrEqu(value);
    if(condition=="menorOIgual")
        return this->loweOrEqu(value);
}

bool DateField::grt(const std::string value) const{
    if (value.substr(0, 4) < this->anio) {
        return true;
    } else if (value.substr(0, 4) == this->anio) {
        if (value.substr(4, 2) < this->mes) {
            return true;
        } else if (value.substr(4, 2) == this->mes) {
            if (value.substr(6, 2) < this->dia) {
                return true;
            } else if (value.substr(6, 2) == this->dia && this->type == 't') {
                if (value.substr(9, 2) < this->horas) {
                    return true;
                } else if (value.substr(9, 2) == this->horas) {
                    if (value.substr(11, 2) < this->minutos) {
                        return true;
                    } else if (value.substr(11, 2) == this->minutos) {
                        if (value.substr(13, 2) < this->segundos) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}


bool DateField::lower(const std::string value) const{
    if (value.substr(0, 4) > this->anio) {
        return true;
    } else if (value.substr(0, 4) == this->anio) {
        if (value.substr(4, 2) > this->mes) {
            return true;
        } else if (value.substr(4, 2) == this->mes) {
            if (value.substr(6, 2) > this->dia) {
                return true;
            } else if (value.substr(6, 2) == this->dia && this->type == 't') {
                if (value.substr(9, 2) > this->horas) {
                    return true;
                } else if (value.substr(9, 2) == this->horas) {
                    if (value.substr(11, 2) > this->minutos) {
                        return true;
                    } else if (value.substr(11, 2) == this->minutos) {
                        if (value.substr(13, 2) > this->segundos) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool DateField::grtOrEqu(const std::string value) const{
    if (value.substr(0, 4) < this->anio) {
        return true;
    } else if (value.substr(0, 4) == this->anio) {
        if (value.substr(4, 2) < this->mes) {
            return true;
        } else if (value.substr(4, 2) == this->mes) {
            if (value.substr(6, 2) < this->dia) {
                return true;
            } else if (value.substr(6, 2) == this->dia && this->type == 't') {
                if (value.substr(9, 2) < this->horas) {
                    return true;
                } else if (value.substr(9, 2) == this->horas) {
                    if (value.substr(11, 2) < this->minutos) {
                        return true;
                    } else if (value.substr(11, 2) == this->minutos) {
                        if (value.substr(13, 2) <= this->segundos) {
                            return true;
                        }
                    }
                }
            } else if (value.substr(6, 2) == this->dia && this->type != 't') {
                return true;
            }
        }
    }
    return false;
}

bool DateField::loweOrEqu(const std::string value) const{
    if (value.substr(0, 4) > this->anio) {
        return true;
    } else if (value.substr(0, 4) == this->anio) {
        if (value.substr(4, 2) > this->mes) {
            return true;
        } else if (value.substr(4, 2) == this->mes) {
            if (value.substr(6, 2) > this->dia) {
                return true;
            } else if (value.substr(6, 2) == this->dia && this->type == 't') {
                if (value.substr(9, 2) > this->horas) {
                    return true;
                } else if (value.substr(9, 2) == this->horas) {
                    if (value.substr(11, 2) > this->minutos) {
                        return true;
                    } else if (value.substr(11, 2) == this->minutos) {
                        if (value.substr(13, 2) >= this->segundos) {
                            return true;
                        }
                    }
                }
            } else if (value.substr(6, 2) == this->dia && this->type != 't') {
                return true;
            }
        }
    }
    return false;
}

std::string DateField::toString() {
    std::stringstream ss;
    ss<<this->anio<<'/'<<this->mes<<'/'<<this->dia;
    if(this->type=='t'){
        ss<<'/'<<this->horas<<this->minutos<<this->segundos;
    }
    return ss.str();
}

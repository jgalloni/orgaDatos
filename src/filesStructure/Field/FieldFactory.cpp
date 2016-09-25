//
// Created by Jorge Galloni on 9/22/16.
//

#include "FieldFactory.h"
#include "IntField.h"
#include "StringField.h"
#include "DateField.h"

Field *FieldFactory::createField(char type, char sizeField, std::string fieldValue) {
    switch (type){
        case 'i':
            return new IntField(fieldValue,sizeField-48);
        case 's':
            return new StringField(fieldValue,sizeField);
        case 'd':
            return new DateField(fieldValue,sizeField);
    }
    return nullptr;
}

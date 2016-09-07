#include "Args.h"


void Args::setInFile(char * inFile) {
    this->inFile = inFile;
}

void Args::setOutFile(char * outFile) {
    this->outFile = outFile;
}

void Args::setModifiers(char * modifiers) {
    this->modifiers = modifiers;
}

void Args::setInType(FileType inType) {
    this->inType = inType;
}

void Args::setOutType(FileType outType) {
    this->outType = outType;
}

void Args::setMethod(Methods method) {
    this->method = method;
}

std::string Args::getInFile() {
    return this->inFile;
}

std::string Args::getOutFile() {
    return this->outFile;
}

Methods Args::getMethod() {
    return this->method;
}

std::string Args::getModifiers() {
    return this->modifiers;
}

FileType Args::getInType() {
    return this->inType;
}

FileType Args::getOutType() {
    return this->outType;
}

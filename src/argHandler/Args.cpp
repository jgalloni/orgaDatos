#include "Args.h"


void Args::setInFile(const char * inFile) {
    this->inFile = inFile;
}

void Args::setOutFile(const char * outFile) {
    this->outFile = outFile;
}

void Args::setModifiers(const char * modifiers) {
    this->modifiers = modifiers;
}

void Args::setModifiers2(const char * modifiers) {
    this->modifiers2 = modifiers;
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

std::string Args::getModifiers2() {
    return this->modifiers2;
}

int Args::getBlockSize() {
    return this->blockSize;
}

void Args::setBlockSize(const char * blocksize) {
    this->blockSize=std::stoi(std::string(blocksize),0);
};

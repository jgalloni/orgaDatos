//
// Created by coco on 06/09/16.
//

#ifndef ORGADATOS_REGISTERFILEMANAGER_H
#define ORGADATOS_REGISTERFILEMANAGER_H

#include "FileManager.h"

class RegisterFileManager : public FileManager{

public:
    RegisterFileManager(FileHeader *fileHeader, std::string fileName);
    RegisterFileManager(std::string filename);
    void insert(std::string reg) const;
    void openFile();

    void writeReg(int size, char *reg) const;

    void deleteReg(std::string rawReg) const;
    virtual FileType getType() const;
    std::vector<Register> find(std::string field,std::string condition, std::string value) const;
    void insert(std::vector<Register> reg) const;
    void insert(Register reg) const;
    std::vector<Register> findNext(std::string field, std::string condition, std::string value);
    std::vector<Register> getNextAndProyect(int *,int);
    std::vector<Register> getNext();
};


#endif //ORGADATOS_REGISTERFILEMANAGER_H

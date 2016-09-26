//
// Created by coco on 06/09/16.
//

#ifndef ORGADATOS_FILEMANAGER_H
#define ORGADATOS_FILEMANAGER_H


#include <vector>
#include "../filesStructure/FileHeader.h"
#include "../filesStructure/OcupationMap.h"
#include "../filesStructure/FreeRegOffset.h"
#include "../filesStructure/Register.h"

class FileManager {
protected:
    FileHeader * fileHeader;
    std::string fileName;
    std::ifstream * ifstream;
    OcupationMap * ocupationMap;
    FreeRegOffset * freeRegOffset;
    std::ofstream *ofstream;
public:
    void createFile();
    virtual void openFile();
    //CRUD de registros
    void removeRegister();
    void updateRegister();
    void deleteRegister();
    virtual void insert(std::string reg) const=0;
    virtual void insert(Register reg) const=0;
    virtual void insert(std::vector<Register> reg) const=0;

    void getRegister(int id);//TODO:cambiar por un tipo mas generico
    static FileManager* getFileManager(std::string name);
    void closeFile();

    virtual void deleteReg(std::string rawReg) const=0;
    virtual FileType getType() const=0;
    virtual std::vector<Register> find(std::string field,std::string condition, std::string value) const=0;
};

#endif //ORGADATOS_FILEMANAGER_H

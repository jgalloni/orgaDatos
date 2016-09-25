//
// Created by coco on 06/09/16.
//

#ifndef ORGADATOS_FILEMANAGER_H
#define ORGADATOS_FILEMANAGER_H


#include "../filesStructure/FileHeader.h"
#include "../filesStructure/OcupationMap.h"

class FileManager {
protected:
    FileHeader * fileHeader;
    std::string fileName;
    std::ifstream * ifstream;
    OcupationMap * ocupationMap;
    std::ofstream *ofstream;
public:
    void createFile();
    virtual void openFile();
    //CRUD de registros
    void removeRegister();
    void updateRegister();
    void deleteRegister();
    virtual void insert(std::string reg) const=0;

    void getRegister(int id);//TODO:cambiar por un tipo mas generico
    static FileManager* getFileManager(std::string name);
    void closeFile();
};

#endif //ORGADATOS_FILEMANAGER_H

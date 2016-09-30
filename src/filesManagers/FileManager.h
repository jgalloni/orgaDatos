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

class FileHeader;
class Register;

class FileManager {
protected:
    FileHeader * fileHeader;
    std::string fileName;
    std::fstream * fstream;
    OcupationMap * ocupationMap;
    FreeRegOffset * freeRegOffset;
    int lastPos=0;
public:
    void createFile();
    virtual void openFile();
    virtual void insert(std::string reg) const=0;
    virtual void insert(Register reg) const=0;
    virtual void insert(std::vector<Register> reg) const=0;

    static FileManager* getFileManager(std::string name);
    void closeFile();

    virtual void deleteReg(std::string rawReg) const=0;
    virtual FileType getType() const=0;
    virtual std::vector<Register> find(std::string field,std::string condition, std::string value) const=0;

    virtual std::vector<Register> findNext(std::string field, std::string condition, std::string value)=0;

    bool end();

    FileHeader *cloneHeader();

    FileHeader *cloneHeader(std::string fields);

    virtual std::vector<Register> getNextAndProyect(int *,int)=0;

    const int &getFieldPosition(std::string);

    FileHeader *getHeader();

    void reset();

    virtual std::vector<Register> getNext(int *pInt)=0;
};

#endif //ORGADATOS_FILEMANAGER_H

#ifndef ORGADATOS_BLOCKFILEMANAGER_H
#define ORGADATOS_BLOCKFILEMANAGER_H

#include "FileManager.h"
#include "../filesStructure/FileHeader.h"


class BlockFileManager : public FileManager{
public:
    BlockFileManager(FileHeader * fileHeader,std::string filename);
    BlockFileManager(std::string filename);
    void insert(std::string reg) const;
    void openFile();
    void deleteReg(std::string rawReg) const;
    virtual FileType getType() const;
    std::vector<Register> find(std::string field,std::string condition, std::string value) const;
    void insert(std::vector<Register> reg) const;
    void insert(Register registro) const;
    std::vector<Register> findNext(std::string field, std::string condition, std::string value);
    std::vector<Register> getNextAndProyect(int *,int);
    std::vector<Register> getNext(int *pInt);
};


#endif //ORGADATOS_BLOQUEDFILEMANAGER_H

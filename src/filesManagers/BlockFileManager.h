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
};


#endif //ORGADATOS_BLOQUEDFILEMANAGER_H

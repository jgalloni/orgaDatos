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
};


#endif //ORGADATOS_REGISTERFILEMANAGER_H

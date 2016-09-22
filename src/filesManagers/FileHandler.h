//
// Created by Jorge Galloni on 9/21/16.
//

#ifndef ORGADATOS_FILEHANDLER_H
#define ORGADATOS_FILEHANDLER_H


#include <string>
#include "../argHandler/Args.h"
#include "../filesStructure/FileHeader.h"

class FileHandler {
private:
    std::string fileName;
    std::ifstream * ifstream;
    std::ofstream * ofstream;
    FileHeader * fileHeader;
public:
    FileHandler(std::string fileName);
};


#endif //ORGADATOS_FILEHANDLER_H

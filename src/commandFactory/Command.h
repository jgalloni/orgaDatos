//
// Created by Jorge Galloni on 9/19/16.
//

#ifndef ORGADATOS_COMMAND_H
#define ORGADATOS_COMMAND_H


#include <string>
#include "../filesManagers/FileManager.h"

class Command {
protected:
    std::string  fileName;
    FileManager * fileManager;
public:
    virtual void execute() const =0;
};


#endif //ORGADATOS_COMMAND_H

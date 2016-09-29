//
// Created by Jorge Galloni on 9/28/16.
//

#ifndef ORGADATOS_UNIONCOMMAND_H
#define ORGADATOS_UNIONCOMMAND_H


#include "../argHandler/Args.h"
#include "../filesManagers/FileManager.h"
#include "Command.h"

class UnionCommand :public Command{
public:
    UnionCommand(Args args);
private:
    void execute() const;
    FileManager * outFileManager;
    FileManager * infileManager;
};


#endif //ORGADATOS_UNIONCOMMAND_H

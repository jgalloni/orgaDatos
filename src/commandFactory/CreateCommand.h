//
// Created by Jorge Galloni on 9/19/16.
//

#ifndef ORGADATOS_CREATECOMMAND_H
#define ORGADATOS_CREATECOMMAND_H


#include "Command.h"
#include "../argHandler/Args.h"
#include "../filesStructure/FileHeader.h"
#include "../filesManagers/FileManager.h"

class CreateCommand : public virtual Command {

public:
    CreateCommand(Args args);
    void execute() const;

};


#endif //ORGADATOS_CREATECOMMAND_H

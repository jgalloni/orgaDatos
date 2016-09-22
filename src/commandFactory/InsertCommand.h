//
// Created by Jorge Galloni on 9/21/16.
//

#ifndef ORGADATOS_INSERTCOMMAND_H
#define ORGADATOS_INSERTCOMMAND_H

#include "Command.h"
#include "../argHandler/Args.h"
#include "../filesStructure/FileHeader.h"
#include "../filesManagers/FileHandler.h"
#include "../filesStructure/Register.h"

class InsertCommand : public virtual Command {

private:
    FileHandler * fileHandler;
    Register * regist;
    std::string rawRegister;

public:
    InsertCommand(Args args);
    void execute() const;

};


#endif //ORGADATOS_INSERTCOMMAND_H

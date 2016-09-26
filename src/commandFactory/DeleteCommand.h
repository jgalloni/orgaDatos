//
// Created by Jorge Galloni on 9/25/16.
//

#ifndef ORGADATOS_DELETECOMMAND_H
#define ORGADATOS_DELETECOMMAND_H


#include "../argHandler/Args.h"
#include "Command.h"

class DeleteCommand: public Command {
private:
    std::string rawRegister;
public:
    DeleteCommand(Args args);

    void execute() const;
};


#endif //ORGADATOS_DELETECOMMAND_H

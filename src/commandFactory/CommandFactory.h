//
// Created by Jorge Galloni on 9/19/16.
//

#ifndef ORGADATOS_COMMANDFACTORY_H
#define ORGADATOS_COMMANDFACTORY_H

#include "../argHandler/Args.h"
#include "Command.h"

class CommandFactory {
public:
    static Command * getCommand(Args args);
};


#endif //ORGADATOS_COMMANDFACTORY_H

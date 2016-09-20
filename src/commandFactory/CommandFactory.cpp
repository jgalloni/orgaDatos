//
// Created by Jorge Galloni on 9/19/16.
//

#include "CommandFactory.h"
#include "CreateCommand.h"

Command * CommandFactory::getCommand(Args args) {
    if(args.getMethod()==Methods::create) {
        return new CreateCommand(args);
    }
    throw std::exception();
}

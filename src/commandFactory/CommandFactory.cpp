//
// Created by Jorge Galloni on 9/19/16.
//

#include "CommandFactory.h"
#include "CreateCommand.h"
#include "InsertCommand.h"

Command * CommandFactory::getCommand(Args args) {
    if(args.getMethod()==Methods::create) {
        return new CreateCommand(args);
    }else if(args.getMethod()==Methods::insert){
        return new InsertCommand(args);
    }
    throw std::exception();
}

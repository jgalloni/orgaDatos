//
// Created by Jorge Galloni on 9/19/16.
//

#include "CommandFactory.h"
#include "CreateCommand.h"
#include "InsertCommand.h"
#include "DeleteCommand.h"
#include "SelectCommand.h"
#include "ProyectionCommand.h"
#include "UnionCommand.h"

Command * CommandFactory::getCommand(Args args) {
    if(args.getMethod()==Methods::create) {
        return new CreateCommand(args);
    }else if(args.getMethod()==Methods::insert){
        return new InsertCommand(args);
    }else if(args.getMethod()==Methods::deleteReg){
        return new DeleteCommand(args);
    } else if(args.getMethod()==Methods::select){
        return new SelectCommand(args);
    } else if(args.getMethod()==Methods::proy){
        return new ProyectionCommand(args);
    } else if(args.getMethod()==Methods::uni) {
        return new UnionCommand(args);
    }
    throw std::exception();
}

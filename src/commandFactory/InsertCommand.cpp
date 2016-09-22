//
// Created by Jorge Galloni on 9/21/16.
//

#include "InsertCommand.h"

InsertCommand::InsertCommand(Args args) {
    this->fileHandler= new FileHandler(args.getOutFile());
    this->rawRegister = args.getModifiers();
}

void InsertCommand::execute() const {
}

//
// Created by Jorge Galloni on 9/28/16.
//

#ifndef ORGADATOS_MULTIPLYCOMMAND_H
#define ORGADATOS_MULTIPLYCOMMAND_H


#include "../argHandler/Args.h"
#include "Command.h"

class MultiplyCommand: public Command {
public:
    MultiplyCommand(Args args);
private:
    void execute() const;
    FileManager * outFileManager;
    FileManager * infileManager;

    std::vector<Register> multiply(std::vector<Register> reg1, std::vector<Register> reg2,int*) const;
};


#endif //ORGADATOS_MULTIPLYCOMMAND_H

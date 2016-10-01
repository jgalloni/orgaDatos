//
// Created by Jorge Galloni on 9/30/16.
//

#ifndef ORGADATOS_CSVCOMMAND_H
#define ORGADATOS_CSVCOMMAND_H


#include "Command.h"

class CSVCommand : public Command{
public:
    CSVCommand(Args args);

private:
    std::ofstream * outfile;

    void execute() const;

};


#endif //ORGADATOS_CSVCOMMAND_H

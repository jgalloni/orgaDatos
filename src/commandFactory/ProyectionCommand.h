//
// Created by Jorge Galloni on 9/28/16.
//

#ifndef ORGADATOS_PROYECTIONCOMMAND_H
#define ORGADATOS_PROYECTIONCOMMAND_H


#include "Command.h"

class ProyectionCommand: public Command {
private:
    FileManager * outFileManager;

    void execute() const;

    std::string fields;
public:
    ProyectionCommand(Args args);

};


#endif //ORGADATOS_PROYECTIONCOMMAND_H

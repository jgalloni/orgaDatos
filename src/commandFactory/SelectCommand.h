//
// Created by Jorge Galloni on 9/25/16.
//

#ifndef ORGADATOS_SELECTCOMMAND_H
#define ORGADATOS_SELECTCOMMAND_H


#include "Command.h"

class SelectCommand : public Command{
public:
    SelectCommand(Args args);

private:
    std::string condition;
    std::string value;
    FileManager * outFileManager;

    void execute() const;

    std::string field;
};


#endif //ORGADATOS_SELECTCOMMAND_H

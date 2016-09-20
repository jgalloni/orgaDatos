#include <iostream>
#include "argHandler/argHandler.h"
#include "commandFactory/CommandFactory.h"

int main(int argc, char const *argv[])
{
	Args * args =ArgHandler::parseArgs(argc,argv);
	Command * command=CommandFactory::getCommand(*args);
    command->execute();
    return 0;
}
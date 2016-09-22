#include "Args.h"
#include <cstring>
#include <iostream>


class ArgHandler
{
public:
	static Args * parseArgs(int argc,const char *argv[]);

private:
	static Args * createArgFiller(int argc,const char *argv[]);
	static Args * insertArgFiller(int argc,const char *argv[]);

};
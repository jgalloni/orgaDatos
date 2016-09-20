#include "Args.h"
#include <cstring>
#include <iostream>


class ArgHandler
{
public:
	static Args * parseArgs(int argc,const char *argv[]);
};
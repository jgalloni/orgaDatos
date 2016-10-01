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

    static Args *deleteArgFiller(int argc, const char **argv);

    static Args *selectArgFiller(int argc, const char **argv);

    static Args *proyectArgFiller(int argc, const char **argv);

    static Args *unionArgFiller(int argc, const char **argv);

    static Args *multiplyArgFiller(int argc, const char **argv);

    static Args *csvArgFiller(int argc, const char **argv);
};
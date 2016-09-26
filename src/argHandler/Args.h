#ifndef ARGS_H
#define ARGS_H

#include <string>

enum class Methods {
	create,
    select,
    proy,
    prodCart,
    uni,
    dif,
    intersec,
    join,
    div,
    grup,
	insert,
	deleteReg
};
enum class FileType{
    bloque=0,
    registro
};

class Args
{
private:
	std::string inFile;
	std::string  outFile;
	Methods method;
	std::string  modifiers;
	std::string modifiers2;
	FileType inType;
	FileType outType;
	int blockSize;
public:
	std::string  getInFile();
	std::string  getOutFile();
	Methods getMethod();
	std::string  getModifiers();
	FileType getInType();
	FileType getOutType();
	std::string getModifiers2();
	int getBlockSize();

	void setInFile(const char *);
	void setOutFile(const char *);
	void setMethod(Methods);
	void setModifiers(const char *);
	void setInType(FileType);
	void setOutType(FileType);
	void setModifiers2(const char *);
	void setBlockSize(const char *);
};

#endif
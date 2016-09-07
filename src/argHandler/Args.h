#include <string>

enum class Methods {
    select,
    proy,
    prodCart,
    uni,
    dif,
    intersec,
    join,
    div,
    grup
};
enum class FileType{
    bloque,
    registro
};

class Args
{
private:
	std::string inFile;
	std::string  outFile;
	Methods method;
	std::string  modifiers;
	FileType inType;
	FileType outType;
public:
	std::string  getInFile();
	std::string  getOutFile();
	Methods getMethod();
	std::string  getModifiers();
	FileType getInType();
	FileType getOutType();

	void setInFile(char *);
	void setOutFile(char *);
	void setMethod(Methods);
	void setModifiers(char *);
	void setInType(FileType);
	void setOutType(FileType);
};
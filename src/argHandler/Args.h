enum Methods {
  select,
  proy,
  prodCart,
  union,
  dif,
  intersec,
  join,
  div,
  grup
};
enum FileTipe{
	bloque,
	registro
}

class Args
{
private:
	string inFile;
	string outFile;
	Methods methods;
	string modifiers;
	FileTipe inFile;
	FileTipe outFile;
public:
	string getInFile();
	string getOutFile();
	Methods getMethods();
	string getModifiers();
	FileTipe getInFile();
	FileTipe getOutFile();

	void setInFile(char *);
	void setOutFile(char *);
	void setMethods(Methods);
	void setModifiers(char *);
	void setInFile(FileTipe);
	void setOutFile(FileTipe);
}
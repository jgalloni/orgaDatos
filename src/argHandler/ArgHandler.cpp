#include "argHandler.h"

Args * ArgHandler::parseArgs(int argc,const char *argv[]){

	if(argc<2) {
		std::cout<<std::endl<<"No se envio ningun parametro, consulte el manual de la app"<<std::endl;
		throw std::exception();
	}
	std::string command = std::string(argv[1]);
	if(!command.compare("crear")) {
		return ArgHandler::createArgFiller(argc,argv);
	}else if(!command.compare("insertar")){
		return ArgHandler::insertArgFiller(argc,argv);
	}

}

Args * ArgHandler::createArgFiller(int argc,const char *argv[]){
	Args * args= new Args();
	if(argc!=7 && argc!=6){
		std::cout<<"Cantidad de parametros para crear archivo incorrecta, consulte el manual de la app"<<std::endl;
		throw std::exception();
	}
	args->setMethod(Methods::create);
	std::cout<<"Metodo: crear archivo"<<std::endl;
	args->setOutFile(argv[2]);
	std::cout<<"Nombre archivo: "<<args->getOutFile()<<std::endl;
	if(!strcmp(argv[3],"b")) {
		args->setOutType(FileType::bloque);
		std::cout<<"Tipo archivo: bloque"<<std::endl;
		args->setBlockSize(argv[4]);
		std::cout<<"Tamaño del bloque: "<<args->getBlockSize()<<std::endl;
		args->setModifiers(argv[5]);
		std::cout<<"Nombre de los registros: "<<args->getModifiers()<<std::endl;
		args->setModifiers2(argv[6]);
		std::cout<<"Tipo y tamaño de los registros: "<<args->getModifiers2()<<std::endl;
	}
	else if (!strcmp(argv[3],"r")) {
		args->setOutType(FileType::registro);
		std::cout<<"Tipo archivo: registro"<<std::endl;
		args->setModifiers(argv[4]);
		std::cout<<"Nombre de los registros: "<<args->getModifiers()<<std::endl;
		args->setModifiers2(argv[5]);
		std::cout<<"Tipo y tamaño de los registros: "<<args->getModifiers2()<<std::endl;
	}
	else {
		std::cout << "Error al detectar el tipo de archivo"<<std::endl;
		throw std::exception();
	}
	return args;
}

Args * ArgHandler::insertArgFiller(int argc,const char *argv[]){
	Args * args= new Args();
	if(argc!=4){
		std::cout<<"Cantidad de parametros para insertar archivo incorrecta, consulte el manual de la app"<<std::endl;
		throw std::exception();
	}
	args->setMethod(Methods::insert);
	std::cout<<"Metodo: insertar registro"<<std::endl;
	args->setOutFile(argv[2]);
	std::cout<<"Nombre archivo: "<<args->getOutFile()<<std::endl;
	args->setModifiers(argv[3]);
	std::cout<<"Registro a insertar de los registros: "<<args->getModifiers()<<std::endl;
	return args;
}